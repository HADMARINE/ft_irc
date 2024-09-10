/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:27 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 16:51:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

#pragma once

namespace irc {

    class User {
    public:
		User(int fd);
		User(const User & cpy);
		User &operator=(const User & cpy);
		~User();

		int			getSocketfd() const;
		const std::string & getRealname() const;
		const std::string & getNickname() const;
		const std::string & getUsername() const;
		const std::string & getHostname() const;
		const std::string & getPendingpassword() const;
        bool          getIsRegistered() const;

		void		setSocketfd(int fd);
		void		setRealname(std::string realname);
		void		setNickname(std::string nickname);
		void		setUsername(std::string username);
		void		setHostname(std::string hostname);
		void		setPendingpassword(std::string pp);
		void		sendPvtMessage(std::string message, int fd);
        void        setIsRegistered(bool isRegistered);

	private:
		User();
		int 		_socketfd;
        std::string _realname;
        std::string _nickname;
        std::string _username;
        std::string _hostname;
        std::string _pendingPassword;
        bool        _isRegistered;
    };
}
