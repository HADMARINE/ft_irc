/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:00 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/25 09:18:29 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandQUIT::resolve(Ircserv * server, User * user) {
        std::string msg = user->getNickname() + " has left the channel"; // TODO : what? not a standard !!
        server->sendToAll(msg);
        server->disconnectUser(user);
        return 0;
    }

    std::vector<std::string> CommandQUIT::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 1) {
            throw TooManyParameters("1", params.size());
        }
        return params;
    }
}