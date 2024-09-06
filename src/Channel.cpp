/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:50 by enorie            #+#    #+#             */
/*   Updated: 2024/09/06 13:24:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"

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
	bool				Channel::isUserInChannel(User& user)
	{
		std::vector<User &>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if (it->getNickname() == user.getNickname())
				return (true);
			it++;
		}
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if (it->getNickname() == user.getNickname())
				return (true);
			it++;
		}
		return (false);
	}
	void				Channel::addOperators(User& user, int fd)
	{
		std::string	alreadyOppError = "User is already an operator";
		std::string	userNotChannelError = "User is not in the channel";
		std::vector<User &>::iterator it;
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if (it->getNickname() == user.getNickname())
			{
				if (send(fd, alreadyOppError.c_str(), alreadyOppError.size(), 0))
					 throw std::runtime_error("Failed to send error message");
				return ;
			}
			it++;
		}
		if (isUserInChannel(user) == false)
		{
			if (send(fd, userNotChannelError.c_str(), userNotChannelError.size(), 0))
					 throw std::runtime_error("Failed to send error message");
			return ;
		}
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if (it->getNickname() == user.getNickname())
			{
				_users.erase(it);
				_operators.push_back(user);
				return ;
			}
			it++;
		}
	}
	void	Channel::joinUser(User& user, int fd)
	{
		std::string	userAlreadyInChannel = "User is already in the channel";
		if (isUserInChannel(user))
		{
			if (send(fd, userAlreadyInChannel.c_str(), userAlreadyInChannel.size(), 0))
					 throw std::runtime_error("Failed to send error message");
			return ;
		}
		_users.push_back(user);
	}
	void	Channel::kickUser(User& user, int fd)
	{
		std::string	userNotInChannel = "User is not in the channel";
		std::string	kickMessage = "You've been kicked from the channel";
		std::vector<User &>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if (it->getNickname() == user.getNickname())
			{
				if (send(fd, kickMessage.c_str(), kickMessage.size(), 0))
					 throw std::runtime_error("Failed to send error message");
				_users.erase(it);
				return ;
			}
			it++;
		}
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if (it->getNickname() == user.getNickname())
			{
				if (send(fd, kickMessage.c_str(), kickMessage.size(), 0))
					 throw std::runtime_error("Failed to send error message");
				_users.erase(it);
				return ;
			}
			it++;
		}
		if (send(fd, userNotInChannel.c_str(), userNotInChannel.size(), 0))
			throw std::runtime_error("Failed to send error message");
	}
	void	Channel::sendToAll(std::string message, int fd)
	{
		std::vector<User &>::iterator it;
		for (it = _users.begin(); it != _users.end(); it++)
		{
			if (it->getSocketFd() =! fd)
			{
				if (send(it->getSocketFd(), message.c_str(), message.size(), 0))
					 throw std::runtime_error("Failed to send message");
				_users.erase(it);
				return ;
			}
			it++;
		}
		for (it = _operators.begin(); it != _operators.end(); it++)
		{
			if (it->getSocketFd() =! fd)
			{
				if (send(it->getSocketFd(), message.c_str(), message.size(), 0))
					 throw std::runtime_error("Failed to send message");
				_users.erase(it);
				return ;
			}
			it++;
		}
	}
}
