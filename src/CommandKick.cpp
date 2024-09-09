/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 17:19:41 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandKICK::resolve(Ircserv * server, User * user) {
        std::string channelName = this->_params.at(0);
        std::string targetUserNickname = this->_params.at(1);
        std::string msg;
        
        Channel *channel = server->findChannelByName(channelName);
        User *targetUser = server->findUserByNick(targetUserNickname);

        if (!channel->isOperator(targetUser)) {
            throw NotOperatorException();  
        }
        if (!targetUser || !channel->isUserInChannel(targetUser)) {
            throw UserNotInChannelException(); 
        }
        channel->kickUser(targetUser);
        msg = targetUserNickname + " has been kicked from the channel by " + operatorUser->getNickname();
        channel->sendToAll(msg);
         

        return 0;
    }

    std::vector<std::string> CommandKICK::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 2) {
            throw TooManyParameters("2", params.size());
        }
        return params;
    }
}