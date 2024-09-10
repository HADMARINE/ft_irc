/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcSpecificResponse.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:24:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 15:39:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {
    class IrcSpecificResponse {
    public:
        IrcSpecificResponse() : _numeric(0), _code("UNDEFINED"), _message("Unknown error occured") {}
        IrcSpecificResponse(std::string code, std::string message) : _numeric(0), _code(code), _message(message) {}
        void setNumeric(unsigned short numeric) { this->_numeric = numeric; }
        unsigned short getNumeric() const { return this->_numeric; }
        void setCode(std::string code) { this->_code = code; }
        std::string getCode() const { return this->_code; }
        void setMessage(std::string message) { this->_message = message; }
        std::string getMessage() const { return this->_message; }

        std::string what() {
            return this->getMessage();
        };
    protected:
        unsigned short _numeric;
        std::string _code;
        std::string _message;
    };
}
