/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:06:27 by bfaisy            #+#    #+#             */
/*   Updated: 2024/09/17 15:47:07 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandMODE::resolve(Ircserv * server, User * user)
	{
		Channel *channel;
		std::string ss;

		std::string channelName = this->_params.at(0);
		std::string option = this->_params.at(1);
		
		channel = server->findChannelByNameSafe(channelName);
		if (!channel->isOperator(user)) {
			throw NoPrivileges();  
		}
		if (option == "+i")
			return (server->sendToSpecificDestination(":" + user->getNickname() + " MODE #" + channelName + " +i" , channel) ,channel->changeInviteOnly(true), 0);
		if (option == "-i")
			return (channel->changeInviteOnly(false), 0);
		if (option == "+t")
			return (channel->changeTopicRestrict(true), 0);
		if (option == "-t")
			return (channel->changeTopicRestrict(false), 0);
		if (option == "+k")
		{
			std::string password = this->_params.at(2);
			return (channel->setPasswordRequired(true), channel->setPassword(password), 0);
		}
		if (option == "-k")
			return (channel->setPasswordRequired(false), 0);
		if (option == "+o")
		{
			std::string user = this->_params.at(2);
			User *userop;
			userop = server->findUserByNickSafe(user);
			return (channel->addOperator(userop), 0);
		}
		if (option == "-o")
		{
			std::string user = this->_params.at(2);
			User *userop;
			userop = server->findUserByNickSafe(user);
			return (channel->removeOperator(userop), 0);
		}
		if (option == "+l")
		{
			std::string nbr = this->_params.at(2);
			return (channel->isUserLimit(true), channel->setUserLimit(std::atoi((nbr.c_str()))), 0);
		}
		if (option == "-l")
			return (channel->isUserLimit(false), 0);
		return 0;
	}

    std::vector<std::string> CommandMODE::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() < 2) {
            throw TooManyParameters("3", params.size());
        }
        return params;
    }
}
