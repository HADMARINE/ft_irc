/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:09:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/11 19:02:16 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


namespace irc {
    int CommandJOIN::resolve(Ircserv * server, User * user) {
        std::string channelName = this->_params.at(0);
        Channel *channel;
        std::string msg;

        channel = server->findChannelByName(channelName);
        if (!channel)
        {
          Channel newChannel(channelName);
          newChannel.addUser(user);
          newChannel.addOperator(user);
          server->getChannels().push_back(newChannel);
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
