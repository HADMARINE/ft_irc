/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:05:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/11 18:10:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    // 001
        RPLWelcome::RPLWelcome(const std::string & nick) {
            this->setCode("RPL_WELCOME");
            this->setNumeric(1);
            this->setMessage(":Welcome to the Internet Relay Network " + nick);
        }

    // 002
        RPLYourHost::RPLYourHost() {
            this->setCode("RPL_YOURHOST");
            this->setNumeric(2);
            this->setMessage(":Your host is <servername>, running version <ver>");
        }

    // 003
        RPLCreated::RPLCreated() {
            this->setCode("RPL_CREATED");
            this->setNumeric(3);
            this->setMessage(":This server was created <date>");
        }

    // 004
        RPLMyInfo::RPLMyInfo() {
            this->setCode("RPL_MYINFO");
            this->setNumeric(4);
            this->setMessage("<servername> <version> <available user modes> <available channel modes>");
        }

    // 005
        RPLIsupport::RPLIsupport() {
            this->setCode("RPL_ISUPPORT");
            this->setNumeric(5);
            this->setMessage(":are supported by this server");
        }

    // 251
        RPLLUserClient::RPLLUserClient() {
            this->setCode("RPL_LUSERCLIENT");
            this->setNumeric(251);
            this->setMessage(":There are <integer> users and <integer> services on <integer> servers");
        }
}
