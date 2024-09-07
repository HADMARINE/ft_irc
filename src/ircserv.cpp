/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:51:40 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/07 17:16:39 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {

	Ircserv::Ircserv() : _password("password"), _isServerShut(NULL) {
		// TODO : implement this
	}

	// Explanations on README
	Ircserv::Ircserv(t_irc_exec_conf & conf) : _password(conf.password), _isServerShut(conf.isServerShut) {
		struct pollfd servPoll;
		struct sockaddr_in  serv_addr;

		memset(&_addrinfoHints, 0, sizeof(_addrinfoHints));
		_addrinfoHints.ai_family = AF_INET;
		_addrinfoHints.ai_socktype = SOCK_STREAM;
		_addrinfoHints.ai_flags = AI_PASSIVE;

		if (getaddrinfo(NULL, conf.portStr.c_str(), &_addrinfoHints, &_addrinfo) < 0)
			throw std::runtime_error("addrinfo init failed");

		_serverSock = socket(_addrinfo->ai_family, _addrinfo->ai_socktype, 0);
		if (_serverSock == -1)
			throw std::runtime_error("socket failed");

		bzero((char*) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(atoi(conf.portStr.c_str()));

		// TODO : Check if we have to do this kind of thing...
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
		freeaddrinfo(_addrinfo);
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
    this->_users.push_back(user);

    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pfds.push_back(pfd);

    this->clientMessage(fd);
    
    DCMD(std::cout << "Client " << fd << " connected" << std::endl);
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
        commandReturnCode = (*it)->resolve(this, this->findUserByFd(fd));
        if (commandReturnCode != 0) {
            throw std::runtime_error("Some error while command execution occured"); // TODO : precise error
        }
      }
      
      for (std::vector<ACommand *>::iterator it = commmands.begin(); it != commmands.end(); it++) {
        delete *it;  
      }
    } catch (IrcSpecificException & e) {
      // TODO : send error to client
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
		// TODO : Emit error when undefined command
		if (cmd == "PASS") {
      return new CommandPASS();
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
        cmdList.push_back(cmd);

        params.erase(params.begin());

        cmd->setParams(params);
      }
    } catch (IrcSpecificException & e) {
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
	return (1);
	}

	User * Ircserv::findUserByFd(int fd) {
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

  Ircserv::~Ircserv() {
      std::cout << "Server shutting down..." << std::endl;
  }

}
