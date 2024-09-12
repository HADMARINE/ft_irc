/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrivmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:26:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/12 15:30:39 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandPRIVMSG::resolve(Ircserv * server, User * user) {
        return 0;
    }

    std::vector<std::string> CommandPRIVMSG::setParamsMiddleware(std::vector<std::string> params) {
        if (params.size() < 2) {
            throw NeedMoreParams();
        }
        if (params.size() > 2) {
            throw TooManyParameters("2", params.size());
        }
        return params;
    }

    void CommandPRIVMSG::permissionCheckMiddleware(Ircserv * server, User * user) {
        (void)server;
        (void)user;
    }
}