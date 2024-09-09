/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 17:23:01 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    int CommandNICK::resolve(Ircserv * server, User * user) {
        if (server->getPassword() != user->getPendingpassword()) {
            throw PasswordMisMatch();
        }
       
       if (server->findUserByNick(this->_params.at(0))) {
            // TODO : throw NicknameInUse~~~();
       }
        user->setNickname(this->_params.at(0));
        return 0;
    }

    std::vector<std::string> CommandNICK::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NeedMoreParams();
        }
        if (params.size() != 1) {
            throw TooManyParameters("1", params.size());
        }
        return params;
    }
}
