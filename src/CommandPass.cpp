/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:43:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:32:47 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandPASS::resolve(Ircserv & server) {
        (void)server;
        return 0;
    }

    std::vector<std::string> CommandPASS::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw ERR_NEEDMOREPARAMS;
        }
        if (params.size() != 1) {
            throw TooManyParameters("1", params.size());
        }
        return params;
    }
    
}