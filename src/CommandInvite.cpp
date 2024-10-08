/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:24:01 by bfaisy            #+#    #+#             */
/*   Updated: 2024/09/17 14:33:40 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_irc.hpp"

namespace irc {
	int CommandINVITE::resolve(Ircserv *server, User *operatorUser) {
		std::string targetUserNickname = this->_params.at(0);
		std::string channelName = this->_params.at(1);
		std::cout << channelName << std::endl;
		std::string msg;
		Channel *channel;

		User *targetUser = server->findUserByNickSafe(targetUserNickname);
		channel = server->findChannelByNameSafe(channelName);
		if (!channel->isOperator(operatorUser)) {
			throw NoPrivileges();
		}
			msg = ":" + operatorUser->getNickname() + " INVITE " + targetUserNickname + " #" + channelName;
			server->sendToSpecificDestination(msg, targetUser);
			channel->inviteUser(targetUser);

		return 0;
	}


    std::vector<std::string> CommandINVITE::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 2) {
            throw TooManyParameters("2", params.size());
        }
        return params;
    }
}
