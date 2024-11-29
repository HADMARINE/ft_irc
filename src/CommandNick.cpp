/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/29 13:32:41 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/*

TODO : Verify nickname rules
Nickname rules :

They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('*', 0x2A), question mark ('?', 0x3F), exclamation mark ('!', 0x21), at sign ('@', 0x40).
They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A).
They MUST NOT start with a character listed as a channel type, channel membership prefix, or prefix listed in the IRCv3 multi-prefix Extension.
They SHOULD NOT contain any dot character ('.', 0x2E).

*/
namespace irc {
    int CommandNICK::resolve(Ircserv * server, User * user) {
        if (user->getIsRegistered()) {
            if (server->findUserByNick(this->_params.at(0))) {
                // server->sendToSpecificDestination(":" + user->getHostname() + " ERROR :registration failed", user);
                server->sendToSpecificDestination(server->formatResponse(NicknameInUse(this->_params.at(0), this->_params.at(0))), user);
                // server->sendToSpecificDestination(":" + user->getHostname() + " 433 " + this->_params.at(0) + " " + this->_params.at(0) + " :Nickname is already in use", user);
                // server->disconnectUser(user);
                server->sendToSpecificDestination(":" + this->_params.at(0) + "!@" + user->getHostname() + " NICK " + this->_params.at(0), user);
                return 0;
            }
            std::string msg = ":" + user->getClientInfo() + " NICK " + this->_params.at(0);
            server->sendToAllServer(msg);
            user->setNickname(this->_params.at(0));
            return 0;
        }


        if (user->getPendingpassword() != server->getPassword()) {
            server->sendToSpecificDestination(":" + user->getHostname() + " ERROR :registration failed", user);
            PasswordMisMatch e(user->getNickname());
            e.setDisconnectAfterEmit(true);
            throw e;
        }
		if (user->getNickname() != "" && server->findUserByNick(this->_params.at(0))) {
			server->sendToSpecificDestination(":" + user->getHostname() + " 433 * " + _params.at(0) + " :Nickname is already in use", user);
			return 0;
		}
        std::stringstream ss;
        if (server->findUserByNick(this->_params.at(0))) {
            server->sendToSpecificDestination(server->formatResponse(NicknameInUse(this->_params.at(0), this->_params.at(0))), user);
            server->sendToSpecificDestination(":" + this->_params.at(0) + "!@" + user->getHostname() + " NICK " + this->_params.at(0), user);
			return 0;
        }
        server->sendToSpecificDestination(":" + this->_params.at(0) + "!@" + user->getHostname() + " NICK " + this->_params.at(0), user);
        user->setNickname(this->_params.at(0));

        if (user->getRealname().empty()) {
            return 0;
        }

        user->setIsRegistered(true);
        std::time_t t = std::time(0);
        server->sendToSpecificDestination(server->formatResponse(RPLWelcome(user)), user);
        server->sendToSpecificDestination(server->formatResponse(RPLYourHost(user, server->getHostname(), "Yv2")), user);
        server->sendToSpecificDestination(server->formatResponse(RPLCreated(user, &t)), user);
        server->motd(user);
        std::cout << user->getHostname() << " " << user->getNickname() << " " << user->getRealname() << " " << user->getUsername() << std::endl;

        return 0;
    }

    std::vector<std::string> CommandNICK::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NoNicknameGiven();
        }
        if (params.size() != 1) {
            throw TooManyParameters("1", params.size());
        }
        if (!checkNickValidity(params.at(0))) {
            throw ErroneusNickName(params.at(0));
        }
        return params;
    }

    bool CommandNICK::checkNickValidity(const std::string & nick) {
        if (nick.find_first_of(" ,*?!@") != std::string::npos) {
            return false;
        }
        if (nick.find_first_of("$:") == 0) {
            return false;
        }
        if (nick.find_first_of(".") != std::string::npos) {
            return false;
        }
        return true;
    }
}
