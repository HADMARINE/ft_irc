/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:27 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/07 14:11:41 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

#ifndef USER_HPP
#define USER_HPP

namespace irc {

    class User {
    public:
		User();
		User(int fd);
		User(const User & cpy);
		// User &operator=(const User & cpy);
		~User();
        
		int			getSocketfd() const;
		const std::string & getRealname() const;
		const std::string	& getNickname() const;
		const std::string	& getUsername() const;
		const std::string	& getHostname() const;
		const std::string	& getPendingpassword() const;
        
		void		setSocketfd(int fd);
		void		setRealname(std::string realname);
		void		setNickname(std::string nickname);
		void		setUsername(std::string username);
		void		setHostname(std::string hostname);
		void		setPendingpassword(std::string pp);
		void		sendPvtMessage(std::string message, int fd);

	private:
		int 		_socketfd;
        std::string _realname;
        std::string _nickname;
        std::string _username;
        std::string _hostname;
        std::string _pendingPassword;
    };
}

#endif
