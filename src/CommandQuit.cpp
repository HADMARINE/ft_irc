/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:00 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 23:11:53 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandQUIT::resolve(Ircserv * server, User * user) {
        server->removeUser(user);
        for (std::vector<Channel>::iterator it = server->getChannels().begin(); it != server->getChannels().end(); it++) {
            it->removeUser(user);
            std::string str(user->getNickname() + " has left the channel");
            server->sendToSpecificDestination(str, it.base());
        }
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