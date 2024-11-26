/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:06:27 by bfaisy            #+#    #+#             */
/*   Updated: 2024/11/26 10:45:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandMODE::resolve(Ircserv * server, User * user)
	{
		Channel *channel;
		std::string ss;

		if (server->findUserByNick(this->_params.at(0)))
		  return (0);
		std::string channelName = this->_params.at(0).substr(1);
		channel = server->findChannelByNameSafe(channelName);
		if (this->_params.size() == 1)
		{
			server->sendToSpecificDestination(server->formatResponse(RPLChannelModeIs(user, channel)), user);
			return 0;
		}
		std::string option = this->_params.at(1);
		if (!channel->isOperator(user)) {
			throw NoPrivileges(user);
		}
		if (option == "+i")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " +i" , channel) ,channel->changeInviteOnly(true), 0);
		if (option == "-i")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " -i" , channel) ,channel->changeInviteOnly(false), 0);
		if (option == "+t")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " +t" , channel) ,channel->changeTopicRestrict(true), 0);
		if (option == "-t")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " -t" , channel) ,channel->changeTopicRestrict(false), 0);
		if (option == "+k")
		{
			std::string password = this->_params.at(2);
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " +k" , channel) ,channel->setPasswordRequired(true), channel->setPassword(password), 0);
		}
		if (option == "-k")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " -k" , channel) ,channel->setPasswordRequired(false), 0);
		if (option == "+o")
		{
			std::string user1 = this->_params.at(2);
			User *userop;
			userop = server->findUserByNickSafe(user1);
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " +o" , channel) ,channel->addOperator(userop), 0);
		}
		if (option == "-o")
		{
			std::string user1 = this->_params.at(2);
			User *userop;
			userop = server->findUserByNickSafe(user1);
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " -o" , channel) ,channel->removeOperator(userop), 0);
		}
		if (option == "+l")
		{
			std::string nbr = this->_params.at(2);
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " +l" , channel) ,channel->changeUserLimit(true), channel->setUserLimit(std::atoi((nbr.c_str()))), 0);
		}
		if (option == "-l")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " -l" , channel) ,channel->changeUserLimit(false), 0);
		return 0;
	}

    std::vector<std::string> CommandMODE::setParamsMiddleware(std::vector<std::string> params) {
        if (params.size() < 1) {
            throw NeedMoreParams();
        }
        if (params.size() > 3) {
            throw TooManyParameters("2-3", params.size());
        }

        return params;
    }
}
