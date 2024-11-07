/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:33:59 by root              #+#    #+#             */
/*   Updated: 2024/11/07 19:23:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandPING::resolve(Ircserv * server, User * user) {
        server->sendToSpecificDestination("PONG " + server->getHostname(), user);
        return 0;
    }
}
