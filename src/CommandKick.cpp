/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/29 12:41:23 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandKICK::resolve(Ircserv * server, User * user) {
        std::string channelName = this->_params.at(0);
        std::string targetUserNickname = this->_params.at(1);
        
        std::stringstream ss;
        for (std::vector<std::string>::iterator it = _params.begin() + 2; it != _params.end(); it++) {
                ss << *it << " ";
        }
        std::string comment = ss.str().substr(0, ss.str().length() - 1);
        std::string msg;
        Channel *channel;
        std::string nick;

        std::cout << channelName<<  targetUserNickname << std::endl;
        channel = server->findChannelByNameSafe(channelName);
        User *targetUser = server->findUserByNick(targetUserNickname);
		if (!targetUser) {
		server->sendToSpecificDestination(":" + user->getNickname() + "!" + user->getRealname() + "@" + user->getHostname() + " 401 " + user->getNickname() + " " + targetUserNickname, user);
		  return (0);
		}
        if (!channel->isOperator(user)) {
            throw ChanOprivIsNeeded(user, channel);
        }
        if (!channel->isUserInChannel(targetUser)) {
          server->sendToSpecificDestination(":" + user->getNickname() + "!" + user->getRealname() + "@" + user->getHostname() + " 441 " + targetUserNickname + " :They aren't on that channel.", user);
		  return (0);
        }
        nick = server->findNickbyUser(user);
        channel->removeUser(targetUser);
        msg = "KICK #" + channelName + " " + targetUser->getNickname() + " :" + comment;
        msg = server->formatResponse(user, msg);
        server->sendToSpecificDestination(msg, channel);
        server->sendToSpecificDestination(msg, targetUser);

        return 0;
    }

    std::vector<std::string> CommandKICK::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() < 3) {
            throw TooManyParameters("3", params.size());
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
