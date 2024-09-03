/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcSpecificException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:24:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:24:49 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSPECIFICEXCEPTION_HPP
#define IRCSPECIFICEXCEPTION_HPP

#include "ft_irc.hpp"

namespace irc {
    class IrcSpecificException {
    public:
        IrcSpecificException() : _code("UNDEFINED"), _message("Unknown error occured") {}
        IrcSpecificException(std::string code, std::string message) : _code(code), _message(message) {}
        void setCode(std::string code) { this->_code = code; }
        std::string getCode() const { return this->_code; }
        void setMessage(std::string message) { this->_message = message; }
        std::string getMessage() const { return this->_message; }
        
        virtual std::string what() = 0;
    protected:
        std::string _code;
        std::string _message;
    };
}

#endif