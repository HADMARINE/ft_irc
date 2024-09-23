/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:51:40 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/23 16:02:18 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_irc.hpp"

namespace irc {

	Ircserv::Ircserv() : _password("password"), _isServerShut(NULL) {
		// TODO : implement this
	}

	// Explanations on README
	Ircserv::Ircserv(t_irc_exec_conf & conf) : _password(conf.password), _isServerShut(conf.isServerShut), _time(conf.time) {
		struct pollfd servPoll;
		struct sockaddr_in  serv_addr;
    addrinfo *addrinfo;

		memset(&_addrinfoHints, 0, sizeof(_addrinfoHints));
		_addrinfoHints.ai_family = AF_INET;
		_addrinfoHints.ai_socktype = SOCK_STREAM;
		_addrinfoHints.ai_flags = AI_PASSIVE;

		if (getaddrinfo(NULL, conf.portStr.c_str(), &_addrinfoHints, &addrinfo) < 0)
			throw std::runtime_error("addrinfo init failed");

		_serverSock = socket(addrinfo->ai_family, addrinfo->ai_socktype, 0);
		if (_serverSock == -1)
			throw std::runtime_error("socket failed");

		bzero((char*) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(atoi(conf.portStr.c_str()));

		int optvalue = 1; // enables the re-use of a port if the IP address is different
		if (setsockopt(_serverSock, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue)) < 0)
		  throw std::runtime_error("Failed to set socket options");

		if (fcntl(_serverSock, F_SETFL, O_NONBLOCK))
			throw std::runtime_error("Failed to put the socket on NON_BLOCK");

		if (bind(_serverSock, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
			throw std::runtime_error("Failed to bind socket");

		if (listen(_serverSock, IRC_LISTEN_BACKLOG) < 0)
			throw std::runtime_error("Failed to listen socket");

		servPoll.fd = _serverSock;
		servPoll.events = POLLIN;
		servPoll.revents = 0;
		_pfds.push_back(servPoll);
		freeaddrinfo(addrinfo);
    this->_hostname = conf.hostname;
	}

  Ircserv & Ircserv::operator=(const Ircserv & rhs) {
    if (this == &rhs) {
      return *this;
    }
      this->_password = rhs._password;
      this->_isServerShut = rhs._isServerShut;
      this->_serverSock = rhs._serverSock;
      this->_pfds = rhs._pfds;
      this->_users = rhs._users;
      this->_channels = rhs._channels;
      this->_operators = rhs._operators;
    return *this;
  }

  Ircserv::~Ircserv() {
      std::cout << "Server shutting down..." << std::endl;
  }

	void  Ircserv::clientConnect() {
    int                fd;
    struct pollfd      pfd;
    struct sockaddr_in addr;
    socklen_t          size;

    size = sizeof(addr);
    fd = accept(_serverSock, (sockaddr *)&addr, &size);
    if (fd < 0)
      throw std::runtime_error("Failed to accept connection");

    User user(fd);
    user.setHostname("localhost");
    this->_users.push_back(user);

    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pfds.push_back(pfd);
    this->motd(fd);
    this->clientMessage(fd);
	}


	void  Ircserv::clientDisconnect(int fd) {
    for (std::vector<pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); it++)
    {
      if (it->fd == fd)
      {
      _pfds.erase(it);
      close(fd);
      DCMD(std::cout << "Client " << fd << " disconnected" << std::endl);
      break;
      }
    }
	}

	void  Ircserv::clientMessage(int fd) {
    char messageBuff[512]; // Following ircserv standard
    memset(messageBuff, 0, sizeof(messageBuff));

    if (recv(fd, messageBuff, sizeof(messageBuff) - 1, 0) <= 0) {
      clientDisconnect(fd);
      return;
    }
    std::vector<ACommand *> commmands;
    try {
      int CRLFPos = getCRLFPos(messageBuff, sizeof(messageBuff) / sizeof(char)); // check crlf position
      if (CRLFPos < 0 || CRLFPos >= 512) {
        throw MessageBufferLimitExceeded();
      }

      std::string messageStr(messageBuff);

      commmands = this->parseCommandStr(messageStr);

      int commandReturnCode;
      for (std::vector<ACommand *>::iterator it = commmands.begin(); it != commmands.end(); it++) {
        commandReturnCode = (*it)->resolve(this, this->findUserByFdSafe(fd));
        if (commandReturnCode != 0) {
            throw std::runtime_error("Some error while command execution occured"); // TODO : precise error
        }
      }

      for (std::vector<ACommand *>::iterator it = commmands.begin(); it != commmands.end(); it++) {
        delete *it;
      }
    } catch (IrcSpecificResponse & e) {
      this->sendToSpecificDestination(this->formatResponse(e), this->findUserByFdSafe(fd));
      for (std::vector<ACommand *>::iterator it = commmands.begin(); it != commmands.end(); it++) {
        delete *it;
      }
      DCMD(std::cerr << "Client " << fd << " : Application Error : " << e.getMessage() << std::endl);
    } catch (std::exception & e) {
      for (std::vector<ACommand *>::iterator it = commmands.begin(); it != commmands.end(); it++) {
        delete *it;
      }
      DCMD(std::cerr << "Client " << fd << " : System Error : " << e.what() << std::endl);
    }
	}

	void Ircserv::bindLoop() {
		DCMD(std::cout << "Loop binded" << std::endl);

		while (!*this->_isServerShut) {
			if ((poll(_pfds.begin().base(), _pfds.size(), -1) < 0) && !*this->_isServerShut)
			throw std::runtime_error("Failed to use poll");
			for (std::vector<pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); it++)
			{
			if ((it->revents & POLLIN) == POLLIN)
			{
				if (it->fd == _serverSock)
					clientConnect();
				else
					clientMessage(it->fd);
				break;
			}
			}
		}
	}

	static ACommand * getCommandFromDict(std::string cmd) {
    DCMD(std::cout << "CMD : " << cmd << std::endl);
    if (cmd == "PASS") {
    	return new CommandPASS();
    } else if (cmd == "USER") {
    	return new CommandUSER();
    } else if (cmd == "JOIN") {
    	return new CommandJOIN();
    } else if (cmd == "NICK") {
    	return new CommandNICK();
    } else if (cmd == "KICK") {
    	return new CommandKICK();
    } else if (cmd == "QUIT") {
    	return new CommandQUIT();
    } else if (cmd == "TOPIC"){
      return new CommandTOPIC();
    } else if (cmd == "MODE"){
      return new CommandMODE();
    } else if (cmd == "CAP") {
    	return NULL;
    } else if (cmd == "PING") {
    	return NULL;
    } else if (cmd == "WHOIS") {
    	return NULL;
    } else if (cmd == "INVITE"){
      return new CommandINVITE();
    } else if (cmd == "PRIVMSG") {
      
      return new CommandPRIVMSG();
    }
 		throw UnknownCommand(cmd);
	}

	std::vector<ACommand *> Ircserv::parseCommandStr(std::string & str) {
		std::vector<std::string> cmdLines = split(str, "\r\n");


    // Remove invalid lists
    std::vector<std::vector<std::string>::iterator> vIt;
    for (std::vector<std::string>::iterator it = cmdLines.begin(); it != cmdLines.end(); it++) {
      if (it->empty()) {
        vIt.push_back(it);
        continue;
      }
      if (strcmp(it->c_str(), "\n") == 0) {
        vIt.push_back(it);
        continue;
      }
    }

    for (std::vector<std::vector<std::string>::iterator>::iterator it = vIt.begin(); it != vIt.end(); it++) {
      cmdLines.erase(*it);
    }

		std::vector<ACommand *> cmdList;

    try  {
      std::string cmdStr;
      std::vector<std::string> params;
      ACommand *cmd;

      while (!cmdLines.empty()) {
        cmdStr = cmdLines.front();
        cmdLines.erase(cmdLines.begin());
        if (cmdStr.empty()) // TODO : Verify this case when empty line.. (space allowed ?)
          continue;

        params = split(cmdStr, " ");

        // Remove invalid parameters - empty
        std::vector<std::vector<std::string>::iterator> vIt;
        for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++) {
          if (it->empty()) {
            vIt.push_back(it);
            continue;
          }
        }

        for (std::vector<std::vector<std::string>::iterator>::iterator it = vIt.begin(); it != vIt.end(); it++) {
          params.erase(*it);
        }

        cmd = getCommandFromDict(params.front());
        if (cmd)
        {
          cmdList.push_back(cmd);
          params.erase(params.begin());
          cmd->setParams(params);
        }
      }
    } catch (IrcSpecificResponse & e) {
      for (std::vector<ACommand *>::iterator it = cmdList.begin(); it != cmdList.end(); it++) {
        delete *it;
      }
      throw e;
    } catch (std::exception & e) {
      for (std::vector<ACommand *>::iterator it = cmdList.begin(); it != cmdList.end(); it++) {
        delete *it;
      }
      throw e;
    }
		return cmdList;
	}

	int Ircserv::readFromConfigFile(char *filename)
	{
		std::ifstream				data;
		std::string					buffer;
		std::vector<std::string>	operators;

		data.open((filename));
		if (!data)
			return (0);
		while (getline(data, buffer)) {
			operators.push_back(buffer);
		}
		data.close();

		std::vector<std::string>::iterator it;
		for (it = operators.begin(); it != operators.end(); it++)
		{
			std::string	line = *it;
			t_server_op	op;

			int len = line.size() - (line.size() - line.find_first_of(' '));

			op.name.insert(0, line, 0, len);
			op.host.insert(0, line, len + 1, line.find_last_of(' ') - len - 1);
			op.password.insert(0, line, line.find_last_of(' ') + 1, line.size() - 1);

			_operators.push_back(op);
		}
	// for (std::vector<t_server_op>::iterator itOp = _operators.begin(); itOp != _operators.end(); itOp++)
	// {
	// 	std::cout << itOp->name << std::endl;  // Accès aux noms de chaque opérateur
	// }
	return (1);
	}

  User * Ircserv::findUserByFd(int fd) {
    User * foundUser = NULL;

    for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
      if ((*it).getSocketfd() == fd)
        foundUser = it.base();
    }

    return foundUser;
  }

	User * Ircserv::findUserByFdSafe(int fd) {
    User * foundUser = NULL;

    for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
      if ((*it).getSocketfd() == fd)
        foundUser = it.base();
    }

    if (foundUser == NULL) {
      throw UserNotFound();
    }
    return foundUser;
  }

  User * Ircserv::findUserByNick(std::string & nick) {
    User * foundUser = NULL;

    for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
      if ((*it).getNickname() == nick)
        foundUser = it.base();
    }

    return foundUser;
  }

  std::string Ircserv::findNickbyUser(User *user)
  {
    for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
      if (user == it.base()){
        const std::string nick = (*it).getNickname();
        return (nick);}
    }
    return "";
  }

  User * Ircserv::findUserByNickSafe(std::string & nick) {
    User * foundUser = NULL;

    for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
      if ((*it).getNickname() == nick)
        foundUser = it.base();
    }

    if (foundUser == NULL) {
      throw NoSuchNick(nick);
    }

    return foundUser;
  }

  Channel * Ircserv::findChannelByName(std::string & name) {
    Channel * foundChannel = NULL;

    for (std::vector<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
      if ((*it).getName() == name)
        foundChannel = it.base();
    }

    return foundChannel;
  }

  Channel * Ircserv::findChannelByNameSafe(std::string & name) {
    Channel * foundChannel = NULL;

    for (std::vector<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
      if ((*it).getName() == name)
        foundChannel = it.base();
    }

    if (foundChannel == NULL) {
      throw NoSuchChannel();
    }

    return foundChannel;
  }


  void Ircserv::sendToAll(std::string & message) {
    for (std::vector<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
      this->sendToSpecificDestination(message, &(*it));
    }
  }

  void Ircserv::sendToSpecificDestination(const std::string & message, User * user) {
    std::string newMesage = message + "\r\n";
    if (send(user->getSocketfd(), newMesage.c_str(), newMesage.size(), 0) < 0) {
      throw std::runtime_error("Failed to send message");
    }
  }

  void Ircserv::sendToSpecificDestination(const std::string & message, std::vector<User *> users) {
    for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
      this->sendToSpecificDestination(message, (*it));
    }
  }

  void Ircserv::sendToSpecificDestination(const std::string & message, Channel * channel) {
    this->sendToSpecificDestination(message, channel->getUsers());
  }

  void Ircserv::removeUser(User * user) {
    for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
      if (it.base() == user) {
        this->_users.erase(it);
        break;
      }
    }

    for (std::vector<struct pollfd>::iterator it = this->_pfds.begin(); it != this->_pfds.end(); it++) {
      if (it->fd == user->getSocketfd()) {
        this->_pfds.erase(it);
        break;
      }
    }
  }

  void Ircserv::disconnectUser(User * user) {
    this->clientDisconnect(user->getSocketfd());
    this->removeUser(user);
  }

  std::string Ircserv::formatResponse(std::string message) {
    return message;
  }

  std::string Ircserv::formatResponse(IrcSpecificResponse message) {
    std::stringstream ss;
    ss << ": ";
    if (message.getNumeric() != 0) {
      std::ostringstream oss;
      oss << std::setfill('0') << std::setw(3) << message.getNumeric();
      ss << oss.str() << " ";
    }
    ss << message.getMessage();
    std::cout << ss.str() << std::endl;
    return ss.str();
  }

  std::string Ircserv::formatResponse(User * origin, std::string message) {
    std::stringstream ss;
    ss << ":" << origin->getClientInfo() << " " << message;
    return ss.str();
  }

  void Ircserv::sendAnnouncementToChannel(const std::string & message, Channel * channel) {
    std::string newMessage = ":" + this->getHostname() + " PRIVMSG #" + channel->getName() + ": " + message + "\r\n";
    this->sendToSpecificDestination(newMessage, channel);
  }

  void Ircserv::addChannel(Channel channel) {
    this->_channels.push_back(channel);
  }

  void	Ircserv::motd(int userfd) // en cours
  {
    User *user = this->findUserByFdSafe(userfd);
    std::string str = " :- [ft_irc] Message of the day - ";
    this->sendToSpecificDestination(str, user);

    std::ifstream motd_file("Motd.txt");
    if (motd_file.is_open())
    {
      std::string line;
      while (getline(motd_file, line)){
        str = " :" + line;
        this->sendToSpecificDestination(str, user);;}
      motd_file.close();
    }
    else
    {
      std::cerr << "Error: could not open motd file" << std::endl;
      str =  ":No MOTD file found";
      this->sendToSpecificDestination(str, user);
      return ;
    }
    str = " :- End of MOTD command -";
    this->sendToSpecificDestination(str, user);
  }

}
