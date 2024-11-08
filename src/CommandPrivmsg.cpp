/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrivmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:26:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/08 13:34:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {

    // TODO : test authority to send message to channel
    static std::vector<User *> getDestinatingUsersList(std::string & target, Ircserv * server, User * user) {
        std::vector<User *> users;
        Channel * channel = NULL;
        if (target[0] == '#') {
            std::string targetCpy  = target.substr(1);
            channel = server->findChannelByNameSafe(targetCpy);
            users = channel->getUsers();
        } else if (target.find_first_of("%#") == 0) {
            std::string targetCpy = target.substr(2);
            channel = server->findChannelByNameSafe(targetCpy);
            users = channel->getOperators();
        } else if (target.find_first_of("@%#") == 0) {
            std::string targetCpy = target.substr(3);
            channel = server->findChannelByNameSafe(targetCpy);
            users = channel->getOperators();
        } else {
            User * targetUser = server->findUserByNickSafe(target);
            users.push_back(targetUser);
        }
        if (channel && !channel->isUserInChannel(user)) {
            throw CannotSendToChan(channel->getName());
        }
        for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
            if (*it == user) {
                users.erase(it);
                break;
            }
        }
        return users;
    }

    int CommandPRIVMSG::resolve(Ircserv * server, User * user) {


        std::stringstream ss;

        ss << "PRIVMSG ";
        std::string &target = _params.at(0);
        std::string targetcpy = target.substr(1);
        if (server->findChannelByName(targetcpy))
        {
            std::vector<User *> users = getDestinatingUsersList(target, server, user);
            for (std::vector<std::string>::iterator it = _params.begin(); it != _params.end(); it++) {
                ss << *it << " ";
            }

            std::string str = ss.str();
            server->sendToSpecificDestination(server->formatResponse(user, str), users);
        }
        else if (server->findUserByNick(target))
        {
            User * user1 = server->findUserByNickSafe(target);
            if (_params.at(1).empty())
                throw NeedMoreParams();
            std::string msg  = _params.at(1).substr(1);
            for (std::vector<std::string>::iterator it = _params.begin() += 2; it != _params.end(); it++) {
              std::cout << *it << std::endl;
              msg = msg + " " + *it;
            }
            std::string str = server->formatResponse(":" + user->getNickname() +  " PRIVMSG " + user1->getNickname() + " :" + msg);
            std::cout << str << std::endl;
            server->sendToSpecificDestination(str, user1);
        }
        else
            throw NoSuchNick(user, target);
        return 0;
    }

    std::vector<std::string> CommandPRIVMSG::setParamsMiddleware(std::vector<std::string> params) {
        if (params.size() < 2) {
            throw NeedMoreParams();
        }
        return params;
    }

    void CommandPRIVMSG::permissionCheckMiddleware(Ircserv * server, User * user) {
        (void)server;
        (void)user;
    }

}
