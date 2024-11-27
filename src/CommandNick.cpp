/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:28:34 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/26 16:36:54 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/*

TODO : Verify nickname rules
Nickname rules : 

They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('*', 0x2A), question mark ('?', 0x3F), exclamation mark ('!', 0x21), at sign ('@', 0x40).
They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A).
They MUST NOT start with a character listed as a channel type, channel membership prefix, or prefix listed in the IRCv3 multi-prefix Extension.
They SHOULD NOT contain any dot character ('.', 0x2E).

*/
namespace irc {
    int CommandNICK::resolve(Ircserv * server, User * user) {
        
    	    
        if (server->findUserByNick(this->_params.at(0))) {
            throw NicknameInUse(this->_params.at(0));
        }
        user->setNickname(this->_params.at(0));
        return 0;
    }

    std::vector<std::string> CommandNICK::setParamsMiddleware(std::vector<std::string> params) {
        if (params.empty()) {
            throw NoNicknameGiven();
        }
        if (params.size() != 1) {
            throw TooManyParameters("1", params.size());
        }
        if (!checkNickValidity(params.at(0))) {
            throw ErroneusNickName(params.at(0));
        }
        return params;
    }

    bool CommandNICK::checkNickValidity(const std::string & nick) {
        if (nick.find_first_of(" ,*?!@") != std::string::npos) {
            return false;
        }
        if (nick.find_first_of("$:") == 0) {
            return false;
        }
        if (nick.find_first_of(".") != std::string::npos) {
            return false;
        }
        return true;
    }
}
