/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:42:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 15:41:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {
    class CommandPASS : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
        void permissionCheckMiddleware(Ircserv *server, User *user);
    };

    class CommandNICK : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };

    class CommandJOIN : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };

    class CommandQUIT : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };

    class CommandKICK : public ACommand {
        int resolve(Ircserv * server, User * user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };
    class CommandINVITE : public ACommand {
        int resolve(Ircserv *server, User *operatorUser);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };
    class CommandTOPIC : public ACommand {
        int resolve(Ircserv *server, User *user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };
    class CommandMODE : public ACommand {
        int resolve(Ircserv *server, User *user);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };
}
