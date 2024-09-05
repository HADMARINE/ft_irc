/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:43:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/05 15:50:25 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandPASS::resolve(Ircserv & server, User * user) {
        (void)server;
        // TODO : Verification of logged-on user reauth try 
        if (user) {
            throw AlreadyRegistered();
        }
        user->getPendingpassword() = this->_params.at(0);
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