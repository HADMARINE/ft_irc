/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:47:28 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/24 16:25:49 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    ACommand::ACommand() {}
    
    
    void ACommand::setParams(std::vector<std::string> params) {
        this->_params = this->setParamsMiddleware(params);
    }

    int ACommand::execute(Ircserv * server, User * user) {
        this->permissionCheckMiddleware(server, user);
        return this->resolve(server, user);
    }

    std::vector<std::string> ACommand::setParamsMiddleware(std::vector<std::string> params) {
        return params;
    }

    void ACommand::permissionCheckMiddleware(Ircserv * server, User * user) {
        (void)server;
        (void)user;
    }
    

    ACommand::~ACommand() {}
}
