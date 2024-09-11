/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponses.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:05:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/11 15:07:08 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    // 001
    class RPLWelcome : public IrcSpecificResponse {
    public:
        RPLWelcome(const std::string & nick) {
            this->setCode("RPL_WELCOME");
            this->setNumeric(1);
            this->setMessage(":Welcome to the Internet Relay Network <nick>!<user>@<host>");
        }
    };

    // 002
    class RPLYourHost : public IrcSpecificResponse {
    public:
        YourHost() {
            this->setCode("RPL_YOURHOST");
            this->setNumeric(2);
            this->setMessage(":Your host is <servername>, running version <ver>");
        }
    };

    // 003
    class RPLCreated : public IrcSpecificResponse {
    public:
        Created() {
            this->setCode("RPL_CREATED");
            this->setNumeric(3);
            this->setMessage(":This server was created <date>");
        }
    };

    // 004
    class MyInfo : public IrcSpecificResponse {
    public:
        MyInfo() {
            this->setCode("RPL_MYINFO");
            this->setNumeric(4);
            this->setMessage("<servername> <version> <available user modes> <available channel modes>");
        }
    };

    // 005
    class Isupport : public IrcSpecificResponse {
    public:
        Isupport() {
            this->setCode("RPL_ISUPPORT");
            this->setNumeric(5);
            this->setMessage(":are supported by this server");
        }
    };

    // 251
    class LUserClient : public IrcSpecificResponse {
    public:
        LUserClient() {
            this->setCode("RPL_LUSERCLIENT");
            this->setNumeric(251);
            this->setMessage(":There are <integer> users and <integer> services on <integer> servers");
        }
    };
}