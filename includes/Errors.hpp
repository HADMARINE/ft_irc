/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:14:05 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/04 18:51:33 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
#define ERRORS_H

#include "ft_irc.hpp"

namespace irc {
    // 461
    class NeedMoreParams : public IrcSpecificException {
    public:
        NeedMoreParams();
        NeedMoreParams(std::string cmd);
    };

    // 462
    class AlreadyRegistered : public IrcSpecificException {
    public:
        AlreadyRegistered();
    };

    // 421
    class UnknownCommand : public IrcSpecificException {
    public:
        UnknownCommand();
        UnknownCommand(std::string cmd);
    };

    class TooManyParameters : public IrcSpecificException {
    public:
        TooManyParameters();
        TooManyParameters(std::string condition, size_t receivedNum);
    private:
    };

    class UserNotFound : public IrcSpecificException {
    public:
        UserNotFound();
    };

    class BadPassword : public IrcSpecificException {
    public:
        BadPassword();
    };
}

#endif