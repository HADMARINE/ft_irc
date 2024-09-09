/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:32:24 by bfaisy            #+#    #+#             */
/*   Updated: 2024/09/09 18:12:27 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandTOPIC::resolve(Ircserv *server, User *user) {
		Channel *channel;
		std::string ss;

		std::string channelName = this->_params.at(0);
		channel = server->findChannelByNameSafe(channelName);

		if (this->_params.size() == 2) {
			std::string currentTopic = channel->getTopic();
			ss = "Current topic for channel " + channelName + ": " + currentTopic;
			server->sendToSpecificDestination(ss, channel);
			return 0;
		}

		if (!channel->isOperator(user)) {
			throw NoPrivileges();
		}

		std::string newTopic = this->_params.at(2);

		channel->setTopic(newTopic);
		ss ="The topic for channel " + channelName + " has been changed to: " + newTopic;

		server->sendToSpecificDestination(ss, channel);

		return 0;
	}


    std::vector<std::string> CommandTOPIC::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() < 2) {
            throw TooManyParameters("1", params.size());
        }
        return params;
    }
}