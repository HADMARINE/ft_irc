/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:50 by enorie            #+#    #+#             */
/*   Updated: 2024/09/09 18:02:20 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	Channel::Channel(std::string name) { _name = name; }
	Channel::~Channel() {};

	const std::string & Channel::getName() const { return (_name); }
	const std::string & Channel::getTopic() const { return (_topic); }
	const std::string & Channel::getPassword() const { return (_channelPassword); }
	int					Channel::getUserLimit() { return (_userLimit); }
	bool				Channel::isInviteOnly() { return (_onInvite); }
	bool				Channel::isTopicRestricted() { return (_topicRestriction); }
	std::vector<User *>	Channel::getUsers() const { return (_users); }
	std::vector<User *>	Channel::getOperators() const { return (_operators); }
	std::vector<User *>	Channel::getInvitedUsers() const { return (_invitedUsers); }

	void				Channel::setName(std::string & name) { _name = name; }
	void				Channel::setTopic(std::string & topic) { _topic = topic; }
	void				Channel::setPassword(std::string & password) { _channelPassword = password; }
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

	void				Channel::addOperator(User * user)
	{
		std::vector<User *>::iterator it;
		if (this->isOperator(user)) {
			throw UserAlreadyOperator(user->getNickname(), this->getName());
		}
		if (!isUserInChannel(user)) {
			throw UserNotInChannel(user->getNickname(), this->getName());
		}
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if ((*it)->getNickname() == user->getNickname())
			{
				_operators.push_back(user);
				return ;
			}
		}
	}

	void	Channel::addUser(User * user)
	{
		if (this->isUserInChannel(user)) {
			throw UserOnChannel(user->getNickname(), this->getName());
		}
		_users.push_back(user);
	}

	bool	Channel::isOperator(User * user)
	{
		std::vector<User *>::iterator it;
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if ((*it)->getNickname() == user->getNickname())
				return (true);
		}
		return (false);
	}

	bool	Channel::isUserInChannel(const User * user)
	{
		std::vector<User *>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if ((*it)->getNickname() == user->getNickname())
				return (true);
		}
		return (false);
	}

	void	Channel::removeUser(User * user)
	{
		std::string	userNotInChannel = "User is not in the channel";
		std::string	kickMessage = "You've been kicked from the channel";
		std::vector<User *>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if ((*it)->getNickname() == user->getNickname())
			{
				throw UserNotInChannel(user->getNickname(), this->getName());
				_users.erase(it);
				return ;
			}
		}
	}
}
