/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:50 by enorie            #+#    #+#             */
/*   Updated: 2024/09/05 16:15:17 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

namespace irc {
	Channel::Channel(std::string name) { _name = name; }

	Channel::~Channel() {};
	
	std::string	Channel::getName() { return (_name); }

	std::string	Channel::getTopic() { return (_topic); }

	std::string	Channel::getPassword() { return (_channelPassword); }

	bool		Channel::isLimit()
	{
		if (_userLimit < 0)
			return (false);
		return (true);
	}
	
	bool		Channel::isInvites() { return (_onInvite); }
	bool		Channel::isTopicRestricted() { return (_topicRestricted); }
}