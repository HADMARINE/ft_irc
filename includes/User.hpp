/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:50:27 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/04 18:14:03 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

#ifndef USER_HPP
#define USER_HPP

namespace irc {
    enum EUserMod {
        USERMOD_IS_INVISIBLE = 1,
        USERMOD_IS_OPERATOR = 2,
        USERMOD_RECEIVE_SERVER_NOTICE = 4,
        USERMOD_RECEIVE_WALLOPS = 8,
    };

    class User {
    public:
        int _socketfd;
        std::string _serverip;
        std::string _realname;
        std::string _nickname;
        std::string _username;
        std::string _hostname;
        
        std::vector<std::string> _recentNicknames;
        std::string _pendingPassword;
        unsigned short _mod; // Refer EUserMod
        bool _isUserLoggedOn;
    };
}

#endif