/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:38:42 by root              #+#    #+#             */
/*   Updated: 2024/11/29 12:46:57 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandUSER::resolve(Ircserv * serv, User * user) {
        if (user->getPendingpassword() != serv->getPassword()) {
            serv->sendToSpecificDestination(":" + user->getHostname() + " 464 " + user->getNickname() + " :Password incorrect", user);
            serv->sendToSpecificDestination(":" + user->getHostname() + " ERROR :registration failed", user);
            serv->disconnectUser(user);
            return (1);
        }
        
        user->setRealname(_params.at(3));
        user->setUsername(_params.at(0));
        if (user->getNickname().empty()) {
            // throw NoNicknameGiven();
            return 0;
        }

        serv->motd(user);
        user->setIsRegistered(true);
        std::time_t t = std::time(0);
        serv->sendToSpecificDestination(serv->formatResponse(RPLWelcome(user)), user);
        serv->sendToSpecificDestination(serv->formatResponse(RPLYourHost(user, serv->getHostname(), "Yv2")), user);
        serv->sendToSpecificDestination(serv->formatResponse(RPLCreated(user, &t)), user);
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
