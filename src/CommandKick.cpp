/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/15 17:14:19 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandKICK::resolve(Ircserv * server, User * user) {
        std::string channelName = this->_params.at(0);
        std::string targetUserNickname = this->_params.at(2);
        std::string comment = this->_params.at(3);
        std::string msg;
        Channel *channel ;
        std::string nick;
        
        std::cout << channelName<<  targetUserNickname << std::endl;
        channel = server->findChannelByNameSafe(channelName);
        User *targetUser = server->findUserByNickSafe(targetUserNickname);
        if (!channel->isOperator(user)) {
            throw NoPrivileges();
        }
        if (!channel->isUserInChannel(targetUser)) {
            throw UserNotInChannel(targetUser->getNickname(), channel->getName()); 
        }
        nick = server->findNickbyUser(user);
        channel->removeUser(targetUser);
        msg = nick + "KICK #" + channelName + " " + targetUserNickname + " :" + comment + "\r\n";
        server->sendToSpecificDestination(msg, channel);

        return 0;
    }

    std::vector<std::string> CommandKICK::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() < 2) {
            throw TooManyParameters("3 or 4", params.size());
        }
        if (params.at(0)[0] != '#') {
			throw UnknownCommand();
		}
		params.at(0) = params.at(0).substr(1);
        if (params.at(2)[0] != ':') {
			throw UnknownCommand();
		}
		params.at(2) = params.at(2).substr(1);
        return params;
    }
}