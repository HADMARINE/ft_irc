/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:09:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 09:40:22 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


namespace irc {
    int CommandJOIN::resolve(Ircserv * server, User * user) {
        std::string channelName = this->_params.at(0);
        Channel *channel;
        std::string msg;
    
        channel = server->findChannelByName(channelName);
        // TODO : check channel rights
        channel->addUser(user);
        msg = user->getNickname() + " has joined the channel\n";
        server->sendToSpecificDestination(msg, channel);

        return 0;
    }

    std::vector<std::string> CommandJOIN::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 2) {
            throw TooManyParameters("2", params.size());
        }
        return params;
    }
}