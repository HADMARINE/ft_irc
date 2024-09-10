/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:06:27 by bfaisy            #+#    #+#             */
/*   Updated: 2024/09/10 09:43:04 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandMODE::resolve(Ircserv * server, User * user)
	{
		Channel *channel;
		std::string ss;

		std::string channelName = this->_params.at(0);

		if (!channel->isOperator(user)) {
			throw NoPrivileges();  
		}
	}

	std::vector<std::string> CommandMODE::setParamsMiddleware(std::vector<std::string> params)
	{
		if (params.empty()) {
			throw NeedMoreParams();
		}
		if (params.size() != 2) {
			throw TooManyParameters("2", params.size());
		}
		return params;
	}
}