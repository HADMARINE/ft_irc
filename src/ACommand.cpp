/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:47:28 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/07 17:07:22 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    ACommand::ACommand() {}
    
    
    void ACommand::setParams(std::vector<std::string> params) {
        this->_params = this->setParamsMiddleware(params);
    }

    std::vector<std::string> ACommand::setParamsMiddleware(std::vector<std::string> params) {
        return params;
    }

    ACommand::~ACommand() {}
}
