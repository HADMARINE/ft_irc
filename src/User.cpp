/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:47 by enorie            #+#    #+#             */
/*   Updated: 2024/09/06 13:36:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

namespace irc {
	User::User() {}
	User::User(int fd) : _socketfd(fd) {}
	User::~User() {}

	int			User::getSocketfd() { return (_socketfd); }
	std::string	User::getRealname() { return (_realname); }
	std::string User::getNickname() { return (_realname); }
	std::string User::getUsername() { return (_username); }
	std::string User::getHostname() { return (_hostname); }
	std::string User::getPendingpassword() { return (_pendingPassword); }
	void		User::setSocketfd(int fd) { _socketfd = fd; }
	void		User::setRealname(std::string realname) { _realname = realname; }
	void		User::setNickname(std::string nickname) { _nickname = nickname; }
	void		User::setUsername(std::string username) { _username = username; }
	void		User::setHostname(std::string hostname) { _hostname = hostname; }
	void		User::setPendingpassword(std::string pp) { _pendingPassword = pp; }
	void		User::sendPvtMessage(std::string message, int fd)
	{
		if (send(fd, message.c_str(), message.size(), 0))
					 throw std::runtime_error("Failed to send error message");
	}
}
