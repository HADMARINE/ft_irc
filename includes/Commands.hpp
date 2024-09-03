/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:42:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 17:31:52 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"

namespace irc {
    class CommandPASS : public ACommand {
        int resolve(Ircserv & server, int fd);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };

    class CommandNick : public ACommand {
        int resolve(Ircserv & server, int fd);
        std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    };
}


#endif