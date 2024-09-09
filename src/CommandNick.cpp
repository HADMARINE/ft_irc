/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 17:04:25 by bfaisy           ###   ########.fr       */
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
        }
        else if (commandType == "KICK")
            return handleKickCommand(server, user);
        else
            throw UnknownCommandException();  // Lancer une exception si la commande est inconnue
        }
        return 0;
    }

    int CommandNICK::handleNickCommand(Ircserv *server, User *user) {

        std::string newNickname = this->_params.at(1);
        user->setNickname(newNickname);
        if (findUserByNick(newNickname))
            throw ;
        return 0;
    }

    int CommandNICK::handleJoinCommand(Ircserv *server, User *user) {

        std::string channelName = this->_params.at(1);
        Channel *channel;
        std::string msg;
    
        channel = findChannelByName(channelName);
        channel->joinUser(user);
        msg = user->getNickname() + " has joined the channel\n";
        channel->sendToAll(msg);

        return 0;
    }

    int CommandNICK::handleQuitCommand(Ircserv *server, User *user) {
        server->quituser(user); // en DEV

        return 0;
    }

    int CommandNICK::handleKickCommand(Ircserv *server, User *operatorUser) {

        std::string channelName = this->_params.at(1);
        std::string targetUserNickname = this->_params.at(2);
        std::string msg;
        Channel *channel = findChannelByName(channelName);
        User *targetUser = server->findUserByNickname(targetUserNickname);

        if (!channel->isOperator(targetUser)) {
            throw NotOperatorException();  

        if (!targetUser || !channel->isUserInChannel(targetUser)) {
            throw UserNotInChannelException(); 

        channel->kickUser(targetUser);
        msg = targetUserNickname + " has been kicked from the channel by " + operatorUser->getNickname();
        channel->sendToAll(msg);
         

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
