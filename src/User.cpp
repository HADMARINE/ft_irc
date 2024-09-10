/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:47 by enorie            #+#    #+#             */
/*   Updated: 2024/09/10 16:52:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	User::User() : _socketfd(-1), _realname(""), _nickname(""), _username(""), _hostname(""), _pendingPassword(""), _isRegistered(false) {}
	User::User(int fd) : _socketfd(fd), _realname(""), _nickname(""), _username(""), _hostname(""), _pendingPassword(""), _isRegistered(false) {}
	User::User(const User & cpy) : _socketfd(cpy.getSocketfd()), _realname(cpy.getRealname()), _nickname(cpy.getNickname()), _username(cpy.getUsername()), _hostname(cpy.getHostname()), _pendingPassword(cpy.getPendingpassword()), _isRegistered(cpy.getIsRegistered()) {}
	User & User::operator=(const User & cpy) {
		this->setSocketfd(cpy.getSocketfd());
		this->setRealname(cpy.getRealname());
		this->setNickname(cpy.getNickname());
		this->setUsername(cpy.getUsername());
		this->setHostname(cpy.getHostname());
		this->setPendingpassword(cpy.getPendingpassword());
		this->setIsRegistered(cpy.getIsRegistered());
		return *this;
	}
	User::~User() {}

	int			User::getSocketfd() const { return (_socketfd); }
	const std::string & User::getRealname() const { return (_realname); }
	const std::string & User::getNickname() const { return (_realname); }
	const std::string & User::getUsername() const { return (_username); }
	const std::string & User::getHostname() const { return (_hostname); }
	const std::string & User::getPendingpassword() const { return (_pendingPassword); }
	bool User::getIsRegistered() const { return _isRegistered; }

	void		User::setSocketfd(int fd) { _socketfd = fd; }
	void		User::setRealname(std::string realname) { _realname = realname; }
	void		User::setNickname(std::string nickname) { _nickname = nickname; }
	void		User::setUsername(std::string username) { _username = username; }
	void		User::setHostname(std::string hostname) { _hostname = hostname; }
	void		User::setPendingpassword(std::string pp) { _pendingPassword = pp; }
	void		User::sendPvtMessage(std::string message, int fd) {
		if (send(fd, message.c_str(), message.size(), 0))
					 throw std::runtime_error("Failed to send error message");
	}
	void		User::setIsRegistered(bool isRegistered) { _isRegistered = isRegistered; }
}
