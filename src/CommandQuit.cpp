/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:00 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/25 15:39:43 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandQUIT::resolve(Ircserv * server, User * user) {
        std::string msg;
        if (_params.at(0).empty())
            msg = server->formatResponse(user,"QUIT");
        else
            msg = server->formatResponse(user, "QUIT " + _params.at(0)); 
        server->sendToAllServer(msg);
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