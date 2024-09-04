/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/04 18:32:47 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"


namespace irc {
    NeedMoreParams::NeedMoreParams() {
        this->setCode("NEED_MORE_PARAMS");
        this->setNumeric(461);
        this->setMessage("Not enough parameters");
    }

    NeedMoreParams::NeedMoreParams(std::string cmd) {
        this->setCode("NEED_MORE_PARAMS");
        this->setNumeric(461);
        std::stringstream ss;
        ss << cmd << " :Not enough parameters";
        this->setMessage(ss.str());
    }

    AlreadyRegistered::AlreadyRegistered() {
        this->setCode("ALREADY_REGISTERED");
        this->setNumeric(462);
        this->setMessage("Already registered");
    }

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

    UserNotFound::UserNotFound() {
        this->setCode("USER_NOT_FOUND");
        this->setMessage("User not found");
    }

    BadPassword::BadPassword() {
        this->setCode("BAD_PASSWORD");
        this->setMessage("Bad password");
    }
}
