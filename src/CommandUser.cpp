/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:38:42 by root              #+#    #+#             */
/*   Updated: 2024/09/12 16:41:43 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandUSER::resolve(Ircserv * serv, User * user) {
       std::cout << user->getNickname() << user->getPendingpassword() << std::endl;
        if (user->getPendingpassword() != serv->getPassword())
            throw PasswordMisMatch();
        if (user->getNickname().empty())
            throw NoNicknameGiven();
        user->setRealname(_params.at(3));
		user->setUsername(_params.at(0));
        user->setIsRegistered(true);
        serv->sendToSpecificDestination(serv->formatResponse(RPLWelcome(user)), user);
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
