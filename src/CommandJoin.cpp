/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:09:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/29 13:32:45 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


namespace irc {
    int CommandJOIN::resolve(Ircserv * server, User * user) {
        std::string channelName;
        Channel *channel;
        std::string msg;
        size_t pos = 1;
		size_t pos1;
		std::string joinpass;

		while (pos != std::string::npos) {
			if (_params.size() == 2)
				std::cout << _params.at(0) << " : " << _params.at(1) << std::endl;
			else
				std::cout << _params.at(0) << std::endl;
			pos = _params.at(0).find(",");
			if (pos != std::string::npos)
				channelName = _params.at(0).substr(1, pos - 1);
			else
				channelName = _params.at(0).substr(1);
			if (this->checkNickValidity(channelName) == false) {
				
			}
			channel = server->findChannelByName(channelName);
			if (!channel) {
				Channel newChannel(channelName);
				newChannel.addUser(user);
				newChannel.addOperator(user);
				if (_params.size() == 2) {
					pos1 = _params.at(1).find(",");
					if (pos1 == std::string::npos && _params.at(1) != "")
						joinpass = _params.at(1);
					else if (pos1 != std::string::npos && _params.at(1) != "")
						joinpass = _params.at(1).substr(0, pos1);
					std::cout << joinpass << std::endl;
					newChannel.setPassword(joinpass);
					newChannel.setPasswordRequired(true);
					_params.at(1).erase(0, pos1 + 1);
				}
				server->addChannel(newChannel);
				server->sendToSpecificDestination(":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " JOIN #" + channelName, user);
				server->sendToSpecificDestination(server->formatResponse(RPLNamReply(user, &newChannel)), user);
				server->sendToSpecificDestination(server->formatResponse(RPLEndOfNames(user, &newChannel)), user);
			}
			else {
				std::string password = channel->getPassword();
				if (channel->isUserLimit() == true && channel->getUsers().size() == channel->getUserLimit())
					throw ChannelIsFull(user, channel);
				if (channel->isInviteOnly() && !channel->isInvitedUser(user))
					throw InviteOnlyChan(user, channel);
				if (channel->isPasswordRequired() == true)
				{
					if (_params.size() != 2)
						throw BadKey(user, channel);
					pos1 = _params.at(1).find(",");
					if (pos1 == std::string::npos)
						joinpass = _params.at(1);
					else
						joinpass = _params.at(1).substr(0, pos1);
					std::cout << "PASS " << password << " " << joinpass << std::endl;
					if (password != joinpass)
						throw BadKey(user, channel);
					_params.at(1).erase(0, pos1 + 1);
				}
				channel->addUser(user);
				server->sendToSpecificDestination(":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " JOIN #" + channel->getName(), user);
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
				server->sendToSpecificDestination(":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " JOIN #" + channel->getName(), users);
			}
			_params.at(0).erase(0, pos + 1);
		}
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

	bool CommandJOIN::checkNickValidity(const std::string & nick) {
        if (nick.find_first_of(" ,*?!@") != std::string::npos) {
            return false;
        }
        if (nick.find_first_of("$:") == 0) {
            return false;
        }
        if (nick.find_first_of(".") != std::string::npos) {
            return false;
        }
        return true;
    }
}
