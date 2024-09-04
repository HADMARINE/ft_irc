/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/04 18:31:07 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandNICK::resolve(Ircserv & server, User * user) {
        if (!user->_isUserLoggedOn && server.getPassword() != user->_pendingPassword) {
            throw BadPassword();
        }
        user->_nickname = this->_params.at(0);
        return 0;
    }
    
    std::vector<std::string> CommandPASS::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 1) {
            throw TooManyParameters("1", params.size());
        }
        return params;
    }
}