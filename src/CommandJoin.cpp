/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:09:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/25 15:20:32 by bfaisy           ###   ########.fr       */
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
			server->sendToSpecificDestination(server->formatResponse(RPLNamReply(user, &newChannel)), user);
			server->sendToSpecificDestination(server->formatResponse(RPLEndOfNames(user, &newChannel)), user);
			server->sendToSpecificDestination(server->formatResponse(RPLNoTopic(user, &newChannel)), user);
			// server->sendToSpecificDestination(server->formatResponse(user, "JOIN #" + newChannel.getName()), &newChannel);
            return (0);
        }
		// ADD LOOP TO JOIN MULTIPLE CHANNELS WHEN MULTIPLE ARGS
		std::string password = channel->getPassword();
		if (channel->getUsers().size() == channel->getUserLimit()) {
            server->sendToSpecificDestination(server->formatResponse(ChannelIsFull(channel->getName())), user);
			throw ChannelIsFull(channel->getName());
		}
		if (channel->isInviteOnly() && !channel->isInvitedUser(user)) {
            server->sendToSpecificDestination(server->formatResponse(InviteOnlyChan(channel->getName())), user);
		    throw InviteOnlyChan();
		}

        if (channel->isPasswordRequired() == true)
        {
            if (_params.size() != 2) {
                server->sendToSpecificDestination(server->formatResponse(BadKey(channel->getName())), user);
                throw BadKey(channel->getName());
            }
            std::string joinpass = this->_params.at(1);
            std::cout << joinpass << std::endl;
            if (password != joinpass) {
                server->sendToSpecificDestination(server->formatResponse(BadKey(channel->getName())), user);
                throw BadKey(channel->getName());
            }
        }
		channel->addUser(user);
		server->sendToSpecificDestination(server->formatResponse(RPLNamReply(user, channel)), user);
		server->sendToSpecificDestination(server->formatResponse(RPLEndOfNames(user, channel)), user);
		if (channel->getTopic() == "")
			server->sendToSpecificDestination(server->formatResponse(RPLNoTopic(user, channel)), user);
		else
			server->sendToSpecificDestination(server->formatResponse(RPLTopic(user, channel)), user);
        std::vector<User *> users = channel->getUsers();
        for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
            if (*it == user) {
                users.erase(it);
                break;
            }
        }
		server->sendToSpecificDestination(server->formatResponse(user, "JOIN #" + channel->getName()), users);
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
