/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:38:42 by root              #+#    #+#             */
/*   Updated: 2024/11/07 20:56:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandUSER::resolve(Ircserv * serv, User * user) {
        if (user->getPendingpassword() != serv->getPassword()) {
            throw PasswordMisMatch(user->getNickname());
        }
        if (user->getNickname().empty()) {
            serv->disconnectUser(user);
            throw NoNicknameGiven();
        }
        // serv->sendToSpecificDestination("motd", (user)); // use this
        serv->motd(user);
        user->setRealname(_params.at(3));
		    user->setUsername(_params.at(0));
        user->setIsRegistered(true);
        std::time_t t = std::time(0);
        serv->sendToSpecificDestination(serv->formatResponse(RPLWelcome(user)), user);
        serv->sendToSpecificDestination(serv->formatResponse(RPLYourHost(user, serv->getHostname(), "Yv2")), user);
        serv->sendToSpecificDestination(serv->formatResponse(RPLCreated(user, &t)), user);
        serv->sendToSpecificDestination(serv->formatResponse(RPLMyInfo(user)), user);
        serv->sendToSpecificDestination(serv->formatResponse(RPLIsupport(user)), user);
        std::cout << user->getHostname() << " " << user->getNickname() << " " << user->getRealname() << " " << user->getUsername() << std::endl;
        return 0;
    }
    std::vector<std::string> CommandUSER::setParamsMiddleware(std::vector<std::string> params) {
        if (params.size() < 4) {
            throw NeedMoreParams();
        }
        if (params.size() > 5 ) {
            throw TooManyParameters("4", params.size());
        }
        return params;
    }
}
