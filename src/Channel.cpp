/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:50 by enorie            #+#    #+#             */
/*   Updated: 2024/09/05 18:26:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

namespace irc {
	Channel::Channel(std::string name) { _name = name; }
	Channel::~Channel() {};

	std::string			Channel::getName() { return (_name); }
	std::string			Channel::getTopic() { return (_topic); }
	std::string			Channel::getPassword() { return (_channelPassword); }
	int					Channel::getUserLimit() { return (_userLimit); }
	bool				Channel::isInvitOnly() { return (_onInvite); }
	bool				Channel::isTopicRestricted() { return (_topicRestriction); }
	std::vector<User &>	Channel::getUsers() const { return (_users); }
	std::vector<User &>	Channel::getOperators() const { return (_operators); }
	std::vector<User &>	Channel::getInvitedUsers() const { return (_invitedUsers); }

	void				Channel::setName(std::string name) { _name = name; }
	void				Channel::setTopic(std::string topic) { _topic = topic; }
	void				Channel::setPassword(std::string password) { _channelPassword = password; }
	void				Channel::setUserLimit(int limit) { _userLimit = limit; }
	void				Channel::changeInvitOnly()
	{
		if (_onInvite == true)
			_onInvite = false;
		else
			_onInvite = true;
	}
	void				Channel::changeTopicRestrict()
	{
		if (_topicRestriction == true)
			_topicRestriction = false;
		else
			_topicRestriction = true;
	}
	void				Channel::addOperators(User& user)
	{
		if (_operators)
		_operators.push_back(user);
	}
}
