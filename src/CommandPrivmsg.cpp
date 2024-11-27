/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrivmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:26:48 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/27 19:36:53 by lhojoon          ###   ########.fr       */
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
        if (_params.at(0).at(0) == '#')
        {
            std::vector<User *> users = getDestinatingUsersList(_params.at(0), server, user);
            for (std::vector<std::string>::iterator it = _params.begin(); it != _params.end(); it++) {
                ss << *it << " ";
            }
            server->sendToSpecificDestination(server->formatResponse(user, ss.str()), users);
        }
        else
        {
            User * destination = server->findUserByNick(_params.at(0));
            if (!destination) {
                server->sendToSpecificDestination(server->formatResponse(user, NoSuchNick(user, _params.at(0))), user);
                return 0;
            }
            if (_params.at(1).empty())
                throw NeedMoreParams();
            for (std::vector<std::string>::iterator it = _params.begin(); it != _params.end(); it++) {
                ss << *it << " ";
            }
            std::string str = server->formatResponse(user, ss.str());
            server->sendToSpecificDestination(str, destination);
        }
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
