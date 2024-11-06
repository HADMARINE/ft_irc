/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:09:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/06 11:11:22 by root             ###   ########.fr       */
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
            server->sendToSpecificDestination(server->formatResponse(user->getNickname() + " JOIN :#" + newChannel.getName()), user);
			      server->sendToSpecificDestination(server->formatResponse(RPLNamReply(user, &newChannel)), user);
			      server->sendToSpecificDestination(server->formatResponse(RPLEndOfNames(user, &newChannel)), user);
            return (0);
        }
		// ADD LOOP TO JOIN MULTIPLE CHANNELS WHEN MULTIPLE ARGS
		std::string password = channel->getPassword();
		if (channel->getUsers().size() == channel->getUserLimit()) {
			throw ChannelIsFull(user, channel);
		}
		if (channel->isInviteOnly() && !channel->isInvitedUser(user)) {
		    throw InviteOnlyChan(user, channel);
		}

        if (channel->isPasswordRequired() == true)
        {
            if (_params.size() != 2) {
                throw BadKey(user, channel);
            }
            std::string joinpass = this->_params.at(1);
            std::cout << joinpass << std::endl;
            if (password != joinpass) {
                throw BadKey(user, channel);
            }
        }
		  channel->addUser(user);
      server->sendToSpecificDestination(server->formatResponse(user->getNickname() + " JOIN :#" + channel->getName()), user);
      if (channel->getTopic() != "")
        server->sendToSpecificDestination(server->formatResponse(RPLTopic(user, channel)), user);
		  server->sendToSpecificDestination(server->formatResponse(RPLNamReply(user, channel)), user);
		  server->sendToSpecificDestination(server->formatResponse(RPLEndOfNames(user, channel)), user);
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
