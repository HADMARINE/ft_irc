/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 17:30:10 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandNick::resolve(Ircserv & server, int fd) {
        std::vector<User> &users = server.getUsers();
        User * foundUser = NULL;
        for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++) {
            if ((*it)._socketfd == fd)
                foundUser = it.base();
        }
        if (foundUser == NULL) {
            throw UserNotFound();
        }
        foundUser->_nickname = this->_params.at(0);
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