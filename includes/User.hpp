/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:27 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/05 15:49:33 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

#ifndef USER_HPP
#define USER_HPP

namespace irc {

    class User {
    public:
		User(int fd);
		User(User &cpy);
		User &operator=(User &cpy);
		~User();
		int			getSocketfd();
		std::string	getRealname();
		std::string	getNickname();
		std::string	getUsername();
		std::string	getHostname();
		std::string	getPendingpassword();
		void		setSocketfd(int fd);
		void		setRealname(std::string realname);
		void		setNickname(std::string nickname);
		void		setUsername(std::string username);
		void		setHostname(std::string hostname);
		void		setPendingpassword(std::string pp);

	private:
		User();
		int 		_socketfd;
        std::string _realname;
        std::string _nickname;
        std::string _username;
        std::string _hostname;  
        std::string _pendingPassword;
    };
}

#endif