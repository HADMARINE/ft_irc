/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:51:40 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:47:54 by lhojoon          ###   ########.fr       */
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
  char messageBuff[1024];

  size = sizeof(addr);
  fd = accept(_serverSock, (sockaddr *)&addr, &size);
  if (fd < 0)
    throw std::runtime_error("Failed to accept connection");
  memset(messageBuff, 0, sizeof(messageBuff));

  ssize_t bytesReceived = recv(fd, messageBuff, sizeof(messageBuff) - 1, 0);

  if (bytesReceived <= 0)
  {
      clientDisconnect(fd);
      return ;
  }
  else {
    std::string messageStr(messageBuff);
    try {
      std::vector<ACommand *> commands = this->parseCommandStr(messageStr);
      int commandReturnCode;
      for (std::vector<ACommand *>::iterator it = commands.begin(); it != commands.end(); ++it) {
        commandReturnCode = (*it)->resolve(*this); // use this instance for initial connection
        if (commandReturnCode != 0)
          throw std::runtime_error("Some error while command execution occured"); // TODO : precise error
      }
    } catch (EIrcException & e) {
      // TODO : send error to client
      (void)e;
    } catch (IrcSpecificException & e) {
      (void)e;
    } catch (std::exception & e) {
      throw e; // pass any error which is not mine...
    }
  }

  pfd.fd = fd;
  pfd.events = POLLIN;
  pfd.revents = 0;
  _pfds.push_back(pfd);
  std::cout << "Client " << fd << " connected" << std::endl;
}


void  Ircserv::clientDisconnect(int fd) {
  for (std::vector<pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); it++)
  {
    if (it->fd == fd)
    {
      _pfds.erase(it);
      close(fd);
      std::cout << "Client " << fd << " disconnected" << std::endl;
      break;
    }
  }
}

void  Ircserv::clientMessage(int fd) {
  char messageBuff[1024];
  memset(messageBuff, 0, sizeof(messageBuff));

  if (recv(fd, messageBuff, sizeof(messageBuff) - 1, 0) <= 0) {
    clientDisconnect(fd);
    return;
  }
  std::string messageStr(messageBuff);
  try {
    std::vector<ACommand *> commmands = this->parseCommandStr(messageStr);
    int commandReturnCode;
    
    for (std::vector<ACommand *>::iterator it = commmands.begin(); it != commmands.end(); ++it) {
      commandReturnCode = (*it)->resolve(*this);
      if (commandReturnCode != 0)
        throw std::runtime_error("Some error while command execution occured"); // TODO : precise error
    }
  } catch (EIrcException & e) {
    // TODO : send error to client
    (void)e;
  } catch (IrcSpecificException & e) {
    (void)e;
  } catch (std::exception & e) {
    throw e;
  }

}

void Ircserv::bindLoop() {
    std::cout << "Loop bining...";
    std::cout << "Success!" << std::endl;

    while (!*this->_isServerShut) {
        if ((poll(_pfds.begin().base(),_pfds.size(), -1) < 0) && !*this->_isServerShut)
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
	(void)cmd;
	return NULL;
}

std::vector<ACommand *> Ircserv::parseCommandStr(std::string & str) {
    std::vector<std::string> cmdLines = split(str, "\r\n");
    std::string cmdStr;
    
    std::vector<std::string> params;
    ACommand *cmd;
	std::vector<ACommand *> cmdList;
    
    while (!cmdLines.empty()) {
        cmdStr = cmdLines.front();
        cmdLines.erase(cmdLines.begin());
        if (cmdStr.empty()) // TODO : Verify this case when empty line.. (space allowed ?)
            continue;

        params = split(cmdStr, " ");
		
        cmd = getCommandFromDict(params.front());
        params.erase(params.begin());
		
        cmd->setParams(params);
		
        cmdList.push_back(cmd);
    }
    return cmdList;
}

Ircserv::~Ircserv() {
    std::cout << "Server shutting down..." << std::endl;
}

}