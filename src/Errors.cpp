/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:31:49 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"


namespace irc {
    TooManyParameters::TooManyParameters() {
        this->setCode("TOO_MANY_PARAMETERS");
        this->setMessage("Too many parameters received");
    }

    TooManyParameters::TooManyParameters(std::string condition, size_t receivedNum) {
        this->setCode("TOO_MANY_PARAMETERS");
        std::stringstream ss;
        ss << "Too many parameters received. Condition : " << condition << ", received : " << receivedNum;
        this->setMessage(ss.str());
    }

    std::string TooManyParameters::what() {
        return this->getMessage();     
    }
}
