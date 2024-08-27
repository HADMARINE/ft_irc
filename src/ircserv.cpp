/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:51:40 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 22:37:03 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {

Ircserv::Ircserv() : _password("password"), _isServerShut(NULL) {
    // TODO : implement this
}

// Explanations on README
Ircserv::Ircserv(t_irc_exec_conf & conf) : _password(conf.password), _isServerShut(conf.isServerShut) {
    int res;
    
    memset(&_addrinfoHints, 0, sizeof(_addrinfoHints));
    _addrinfoHints.ai_family = AF_INET;
    _addrinfoHints.ai_socktype = SOCK_STREAM;
    _addrinfoHints.ai_flags = AI_PASSIVE;

    res = getaddrinfo(NULL, conf.portStr.c_str(), &_addrinfoHints, &_addrinfo);

    if (res < 0)
        throw std::runtime_error("addrinfo init failed");
    
    // _addrinfo.sin_addr.s_addr = INADDR_ANY;
    // _addrinfo.sin_family = AF_INET;
    // _addrinfo. = htons(conf.port);
    
    _serverSock = socket(_addrinfo->ai_family, _addrinfo->ai_socktype, _addrinfo->ai_protocol);

    if (_serverSock == -1)
        throw std::runtime_error("socket failed");

    // TODO : Check if we have to do this kind of thing...
	// int optvalue = 1; // enables the re-use of a port if the IP address is different
	// if (setsockopt(_server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue)) == FAILURE)
	// {
	// 	std::cerr << RED << "[Server] Impossible to reuse" << RESET << std::endl;
	// 	return (FAILURE);
	// }

    res = bind(_serverSock, _addrinfo->ai_addr, _addrinfo->ai_addrlen);

    if (res != 0)
        throw std::runtime_error("Failed to bind socket");

    res = listen(_serverSock, IRC_LISTEN_BACKLOG);

    if (res != 0)
        throw std::runtime_error("Failed to listen socket");

    freeaddrinfo(_addrinfo);
}

void Ircserv::bindLoop() {
    std::cout << "Loop bining...";
    std::cout << "Success!" << std::endl;

    std::vector<pollfd> recvPollfds;
    while (!*this->_isServerShut) {
        // Work !!!
        std::vector<pollfd> newPollfds;

        ;
    }
}

Ircserv::~Ircserv() {
    std::cout << "Server shutting down..." << std::endl;
}

}
