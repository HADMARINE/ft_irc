/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:32:24 by bfaisy            #+#    #+#             */
/*   Updated: 2024/11/27 16:35:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandTOPIC::resolve(Ircserv *server, User *user) {

		Channel *channel;
		std::string ss;
		std::string channelName = this->_params.at(0);
		channel = server->findChannelByNameSafe(channelName);
		if (channel->isTopicRestricted() == true && !channel->isOperator(user)) {
			throw ChanOprivIsNeeded(user, channel);
		}
		if (this->_params.size() == 1) {
			std::string currentTopic = channel->getTopic();
			if (currentTopic == "")
				server->sendToSpecificDestination(server->formatResponse(RPLNoTopic(user, channel)), channel);
			else
				server->sendToSpecificDestination(server->formatResponse(RPLTopic(user, channel)), channel);
			return 0;
		}
		std::string newTopic = this->_params.at(1).substr(1);
		channel->setTopic(newTopic);
		server->sendToSpecificDestination(server->formatResponse(RPLTopic(user, channel)), channel);
		return 0;
	}


	// 1 ~ 2 params
    std::vector<std::string> CommandTOPIC::setParamsMiddleware(std::vector<std::string> params) {
        if (params.size() == 0) {
            throw NeedMoreParams();
        }
		if (params.at(0)[0] != '#') {
			throw UnknownCommand();
		}
		params.at(0) = params.at(0).substr(1);
        return params;
    }
}
