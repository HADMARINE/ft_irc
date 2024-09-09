/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:24:01 by bfaisy            #+#    #+#             */
/*   Updated: 2024/09/09 18:09:25 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandINVITE::resolve(Ircserv *server, User *operatorUser) {

		std::string channelName = this->_params.at(0);
		std::string targetUserNickname = this->_params.at(1);
		std::string msg;
		Channel *channel;

		User *targetUser = server->findUserByNick(targetUserNickname);

		if (!channel->isOperator(operatorUser)) {
			throw NotOperatorException();
		}
		if (!targetUser) {
			throw UserNotFoundException(); 
		}
		server->inviteUserToChannel(channelName, targetUser); // en dev
		msg = "You have been invited to join the channel: " + channelName;
		server->sendToSpecificDestination(msg, targetUser);

		return 0;
	}

    std::vector<std::string> CommandINVITE::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 3) {
            throw TooManyParameters("3", params.size());
        }
        return params;
    }
}
