/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:43:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 10:04:52 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandPASS::resolve(Ircserv * server, User * user) {
        (void)server;
        user->setPendingpassword(this->_params.at(0));
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

    void CommandPASS::permissionCheckMiddleware(Ircserv * server, User * user) {
        (void)server;
        if (user->getIsRegistered()) {
            throw AlreadyRegistered();
        }
    }
    
}