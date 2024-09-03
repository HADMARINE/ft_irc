/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcSpecificException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:24:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 17:08:35 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSPECIFICEXCEPTION_HPP
#define IRCSPECIFICEXCEPTION_HPP

#include "ft_irc.hpp"

namespace irc {
    class IrcSpecificException {
    public:
        IrcSpecificException() : _numeric(0), _code("UNDEFINED"), _message("Unknown error occured") {}
        IrcSpecificException(std::string code, std::string message) : _numeric(0), _code(code), _message(message) {}
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

#endif