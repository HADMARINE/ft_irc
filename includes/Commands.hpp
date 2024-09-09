/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:42:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 17:04:40 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"

namespace irc {
    class CommandPASS : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };

    class CommandNICK : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
        int handleNickCommand(Ircserv *server, User *user);
        int CommandNICK::handleJoinCommand(Ircserv *server, User *user);
        int CommandNICK::handleQuitCommand(Ircserv *server, User *user);
        int CommandNICK::handleKickCommand(Ircserv *server, User *operatorUser);
    };
}


#endif