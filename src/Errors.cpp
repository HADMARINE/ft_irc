/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 16:36:31 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errors.hpp"


namespace irc {
    UserNotInChannel::UserNotInChannel() {
        this->setCode("ERR_USERNOTINCHANNEL");
        this->setNumeric(441);
        this->setMessage(":They aren't on that channel");
    }

    UserNotInChannel::UserNotInChannel(std::string nick, std::string channel) {
        this->setCode("ERR_USERNOTINCHANNEL");
        this->setNumeric(441);
        std::stringstream ss;
        ss << nick << " " << channel << " :They aren't on that channel";
        this->setMessage(ss.str());
    }

    NotOnChannel::NotOnChannel() {
        this->setCode("ERR_NOTONCHANNEL");
        this->setNumeric(442);
        this->setMessage(":You're not on that channel");
    }

    NotOnChannel::NotOnChannel(std::string channel) {
        this->setCode("ERR_NOTONCHANNEL");
        this->setNumeric(442);
        std::stringstream ss;
        ss << channel << " :You're not on that channel";
        this->setMessage(ss.str());
    }

    UserOnChannel::UserOnChannel() {
        this->setCode("ERR_USERONCHANNEL");
        this->setNumeric(443);
        this->setMessage(":is already on channel");
    }

    UserOnChannel::UserOnChannel(std::string nick, std::string channel) {
        this->setCode("ERR_USERONCHANNEL");
        this->setNumeric(443);
        std::stringstream ss;
        ss << nick << " " << channel << " :is already on channel";
        this->setMessage(ss.str());
    }

    NeedMoreParams::NeedMoreParams() {
        this->setCode("ERR_NEEDMOREPARAMS");
        this->setNumeric(461);
        this->setMessage(":Not enough parameters");
    }

    NeedMoreParams::NeedMoreParams(std::string cmd) {
        this->setCode("ERR_NEEDMOREPARAMS");
        this->setNumeric(461);
        std::stringstream ss;
        ss << cmd << " :Not enough parameters";
        this->setMessage(ss.str());
    }

    AlreadyRegistered::AlreadyRegistered() {
        this->setCode("ERR_ALREADYREGISTRED");
        this->setNumeric(462);
        this->setMessage(":You may not reregister");
    }

    PasswordMisMatch::PasswordMisMatch() {
        this->setCode("ERR_PASSWDMISMATCH");
        this->setNumeric(464);
        this->setMessage(":Password incorrect");
    }

    TooManyParameters::TooManyParameters() {
        this->setCode("TOO_MANY_PARAMETERS");
        this->setMessage(":Too many parameters received");
    }

    TooManyParameters::TooManyParameters(std::string condition, size_t receivedNum) {
        this->setCode("TOO_MANY_PARAMETERS");
        std::stringstream ss;
        ss << ":Too many parameters received. Condition : " << condition << ", received : " << receivedNum;
        this->setMessage(ss.str());
    }

    UserNotFound::UserNotFound() {
        this->setCode("USER_NOT_FOUND");
        this->setMessage(":User not found");
    }

    UnknownCommand::UnknownCommand() {
        this->setNumeric(421);
        this->setCode("UNKNOWN_COMMAND");
        this->setMessage(":Unknown command");
    }

    UnknownCommand::UnknownCommand(std::string cmd) {
        this->setNumeric(421);
        this->setCode("UNKNOWN_COMMAND");
        std::stringstream ss;
        ss << cmd << " :Unknown command";
        this->setMessage(ss.str());
    }

    MessageBufferLimitExceeded::MessageBufferLimitExceeded() {
        this->setCode("MESSAGE_BUFFER_LIMIT_EXCEEDED");
        this->setMessage(":Message too long, 512 characters max !");
    }

    UserAlreadyOperator::UserAlreadyOperator() {
        this->setCode("ERR_USERISOPERATOR");
        this->setMessage(":is already an operator");
    }

    UserAlreadyOperator::UserAlreadyOperator(std::string nick, std::string channel) {
        this->setCode("ERR_USERISOPERATOR");
        std::stringstream ss;
        ss << nick << " " << channel << " :is already an operator";
        this->setMessage(ss.str());
    }
}
