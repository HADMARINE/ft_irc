/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:09:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/12 19:19:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


namespace irc {
    int CommandJOIN::resolve(Ircserv * server, User * user) {
        std::string channelName = this->_params.at(0);
        channelName = channelName.substr(1);
        Channel *channel;
        std::string msg;

        channel = server->findChannelByName(channelName);
        if (!channel)
        {
            Channel newChannel(channelName);
            newChannel.addUser(user);
            newChannel.addOperator(user);
            server->addChannel(newChannel);
            msg = "You created the " + channelName + " channel\n";
            server->sendToSpecificDestination(msg, &newChannel);
            return (0);
        }
		// ADD LOOP TO JOIN MULTIPLE CHANNELS WHEN MULTIPLE ARGS
		std::string password = channel->getPassword();
			if (channel->getUsers().size() == channel->getUserLimit()) {
			throw ChannelFull();
		}
		if (channel->isInviteOnly() && !channel->isInvitedUser(user)) {
		throw InviteOnlyChan();
		}
		if (password != "" && password != this->_params.at(1)) {
		throw PasswordMisMatch();
		}
		channel->addUser(user);
		server->sendToSpecificDestination(": " + user->getUsername() + " JOIN " + channel->getName(), user);
		server->sendToSpecificDestination(server->formatResponse(RPLTopic(user, channel)), user);
		server->sendToSpecificDestination(server->formatResponse(RPLNamReply(user, channel)), user);
		server->sendToSpecificDestination(server->formatResponse(RPLEndOfNames(user, channel)), user);
		msg = user->getNickname() + " has joined the channel\n";
		server->sendToSpecificDestination(msg, channel);
		msg = channel->getTopic();
		server->sendToSpecificDestination(msg, user);
		return 0;
    }

    std::vector<std::string> CommandJOIN::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() > 2) {
            throw TooManyParameters("1-2", params.size());
        }
        return params;
    }
}
