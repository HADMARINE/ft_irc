/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:51:40 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 20:37:38 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {

Ircserv::Ircserv() {
    
}

Ircserv::Ircserv(t_irc_exec_conf & conf) {
    _addrinfo.ai_family = AF_INET;
    _addrinfo.ai_socktype = SOCK_STREAM;
    _addrinfo.ai_flags = AI_PASSIVE;
    _addrinfo.sin_addr.s_addr = INADDR_ANY;
    _addrinfo.sin_family = AF_INET;
    _addrinfo.sin_port = htons(conf.port);
    _password = conf.password;

    int res;

    this->_serverSock = socket(_addrinfo.ai_family, _addrinfo.ai_addr);

    res = bind(this->_serverSock, (struct sockaddr*)&this->_addrinfo, sizeof(this->_serverAddr));

    if (res != 0)
        throw std::runtime_error("Failed to bind socket");

    res = listen(this->_serverSock, IRC_LISTEN_BACKLOG);

    if (res != 0)
        throw std::runtime_error("Failed to listen socket");

    
    
}

Ircserv::~Ircserv() {
    std::cout << "Server shutting down..." << std::endl;
}

}
