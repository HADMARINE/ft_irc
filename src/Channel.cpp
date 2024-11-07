/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:50 by enorie            #+#    #+#             */
/*   Updated: 2024/11/07 14:37:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	Channel::Channel(std::string name) : _name(name), _topic(""), _channelPassword(""), _userLimit(-1), _onInvite(false), _topicRestriction(false), _isPasswordRequired(false), _isUserLimit(false){}
	Channel & Channel::operator=(const Channel &cpy) {
		if (this == &cpy) {
			return *this;
		}
		_name = cpy._name;
		_topic = cpy._topic;
		_channelPassword = cpy._channelPassword;
		_users = cpy._users;
		_operators = cpy._operators;
		_invitedUsers = cpy._invitedUsers;
		_userLimit = cpy._userLimit;
		_onInvite = cpy._onInvite;
		_topicRestriction = cpy._topicRestriction;
		_isPasswordRequired = cpy._isPasswordRequired;
		_isUserLimit = cpy._isUserLimit;
		return *this;
	}
	Channel::~Channel() {};

	const std::string & Channel::getName() const { return (_name); }
	const std::string & Channel::getTopic() const { return (_topic); }
	const std::string & Channel::getPassword() const { return (_channelPassword); }
	unsigned int		Channel::getUserLimit() { return (_userLimit); }
	bool				Channel::isInviteOnly() { return (_onInvite); }
	bool				Channel::isTopicRestricted() { return (_topicRestriction); }
	bool				Channel::isUserLimit() { return (_isUserLimit); }
	std::vector<User *>	Channel::getUsers() const { return (_users); }
	std::vector<User *>	Channel::getOperators() const { return (_operators); }
	std::vector<User *>	Channel::getInvitedUsers() const { return (_invitedUsers); }
	void				Channel::setPasswordRequired(bool cond) {_isPasswordRequired = cond;}
	bool				Channel::isPasswordRequired() {return _isPasswordRequired ;}
	void				Channel::setName(std::string & name) { _name = name; }
	void				Channel::setTopic(std::string & topic) { _topic = topic; }
	void				Channel::setPassword(std::string & password) { _channelPassword = password; }
	void				Channel::setUserLimit(int limit) { _userLimit = limit; }
	void				Channel::changeUserLimit(bool cond) {_isUserLimit = cond;}
	void				Channel::changeInviteOnly(bool cond)
	{
		_onInvite = cond;
	}
	void				Channel::changeTopicRestrict(bool cond)
	{
		_topicRestriction = cond;
	}

	void				Channel::addOperator(User * user)
	{
		std::vector<User *>::iterator it;
		if (this->isOperator(user)) {
			throw UserAlreadyOperator(user->getNickname(), this->getName());
		}
		if (!this->isUserInChannel(user)) {
			throw UserNotInChannel(user->getNickname(), this->getName());
		}
		_operators.push_back(user);
	}

	void	Channel::addUser(User * user)
	{
		if (this->isUserInChannel(user)) {
			throw UserOnChannel(user->getNickname(), this->getName());
		}
		_users.push_back(user);
	}

	void	Channel::removeOperator(User * user) {
		std::vector<User *>::iterator it;
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if ((*it) == user)
			{
				_operators.erase(it);
				return ;
			}
		}
	}

	bool	Channel::isOperator(User * user)
	{
		std::vector<User *>::iterator it;
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if ((*it) == user)
				return (true);
		}
		return (false);
	}

	bool	Channel::isUserInChannel(const User * user)
	{
		std::vector<User *>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if ((*it) == user)
				return (true);
		}
		return (false);
	}

	void	Channel::removeUser(User * user)
	{
		std::vector<User *>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if ((*it) == user)
			{
				_users.erase(it);
				return ;
			}
		}
		throw UserNotInChannel(user->getNickname(), this->getName());
	}

	bool Channel::isInvitedUser(User * user) {
		if (!_invitedUsers.empty()){
			for (std::vector<User *>::iterator it = _invitedUsers.begin(); it != _users.end(); it++) {
				if ((*it) == user) {
					return true;
				}
		}}
		return false;
	}

	void Channel::inviteUser(User * user) {
		if (this->isInvitedUser(user)) {
			throw UserAlreadyInvited(user->getNickname(), this->getName());
		}
		_invitedUsers.push_back(user);

	}
}
