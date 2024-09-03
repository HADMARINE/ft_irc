/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:43:42 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 17:31:05 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandPASS::resolve(Ircserv & server, int fd) {
        std::vector<User> &users = server.getUsers();
        User * foundUser = NULL;
        for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++) {
            if ((*it)._socketfd == fd)
                foundUser = it.base();
        }
        if (foundUser == NULL) {
            throw UserNotFound();
        }
        foundUser->_pendingPassword = this->_params.at(0);
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