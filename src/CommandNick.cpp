/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 16:25:48 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandNICK::resolve(Ircserv * server, User * user) {
        if (server->getPassword() != user->getPendingpassword()) {
            throw PasswordMisMatch();
        }
        std::string commandType = this->_params.at(0);
        
        if (commandType == "NICK") {
            return handleNickCommand(server, user);
        } else if (commandType == "JOIN") {
            return handleJoinCommand(server, user);
        } else if (commandType == "QUIT") {
            return handleQuitCommand(server, user);
        } else {
            throw UnknownCommandException();  // Lancer une exception si la commande est inconnue
        }
        return 0;
    }

    int CommandNICK::handleNickCommand(Ircserv *server, User *user) {

        std::string newNickname = this->_params.at(1);
        user->setNickname(newNickname);
        if (finduserbynick(newNickname))
            throw ;
        return 0;
    }

    int CommandNICK::handleJoinCommand(Ircserv *server, User *user) {

        std::string channelName = this->_params.at(1);
        Channel *channel;
    
        channel = findchannelbyname(channelName);
        channel->joinChanel(user); // en cours de DEV
        
        channel->sendToAll(" has joined the channel\n");

        return 0;
    }

    int CommandNICK::handleQuitCommand(Ircserv *server, User *user) {
        server->kickUser(user); // demander a eliott

        return 0;
    }

    int CommandChannel::handleKickCommand(Ircserv *server, User *operatorUser) {

        std::string channelName = this->_params.at(1);
        std::string targetUserNickname = this->_params.at(2);

        if (!server->isOperator(channelName, operatorUser)) {
            throw NotOperatorException();  

        User *targetUser = server->findUserByNickname(targetUserNickname);
        if (!targetUser || !server->isUserInChannel(channelName, targetUser)) {
            throw UserNotInChannelException(); 

        server->kickUserFromChannel(channelName, targetUser);

        server->notifyChannel(channelName, targetUserNickname + " has been kicked from the channel by " + operatorUser->getNickname());

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
