/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:47:28 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 14:24:49 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    ACommand::ACommand() {}
    
    ACommand::ACommand(std::vector<std::string> params) {
        this->setParams(params);
    }
    
    void ACommand::setParams(std::vector<std::string> params) {
        this->_params = this->setParamsMiddleware(params);
    }

    std::vector<std::string> ACommand::setParamsMiddleware(std::vector<std::string> params) {
        return params;
    }
}