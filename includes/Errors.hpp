/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:14:05 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 15:40:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {
    // 401
    class NoSuchNick : public IrcSpecificException {
    public:
        NoSuchNick();
        NoSuchNick(std::string nick);
    };

    // 402
    class NoSuchServer : public IrcSpecificException {
    public:
        NoSuchServer();
        NoSuchServer(std::string server);
    };

    // 403
    class NoSuchChannel : public IrcSpecificException {
    public:
        NoSuchChannel();
        NoSuchChannel(std::string channel);
    };

    // 404
    class CannotSendToChan : public IrcSpecificException {
    public:
        CannotSendToChan();
        CannotSendToChan(std::string channel);
    };

    // 421
    class UnknownCommand : public IrcSpecificException {
    public:
        UnknownCommand();
        UnknownCommand(std::string cmd);
    };

    // 432
    class ErroneusNickName : public IrcSpecificException {
    public:
        ErroneusNickName();
        ErroneusNickName(std::string nick);
    };

    // 433
    class NicknameInUse : public IrcSpecificException {
    public:
        NicknameInUse();
        NicknameInUse(std::string nick);
    };

    // 441
    class UserNotInChannel : public IrcSpecificException {
    public:
        UserNotInChannel();
        UserNotInChannel(std::string nick, std::string channel);
    };

    // 442
    class NotOnChannel : public IrcSpecificException {
    public:
        NotOnChannel();
        NotOnChannel(std::string channel);
    };

    // 443
    class UserOnChannel : public IrcSpecificException {
    public:
        UserOnChannel();
        UserOnChannel(std::string nick, std::string channel);
    };

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

    // 464
    class PasswordMisMatch : public IrcSpecificException {
    public:
        PasswordMisMatch();
    };

    // 473
    class InviteOnlyChan : public IrcSpecificException {
    public:
        InviteOnlyChan();
        InviteOnlyChan(std::string channel);
    };

    // 481
    class NoPrivileges : public IrcSpecificException {
    public:
        NoPrivileges();
    };

    // ~~~ Custom exceptions from here which are not defined in RFC1459 ~~~

    class IsTopicRestricted : public IrcSpecificException {
    public:
        IsTopicRestricted();
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

    class MessageBufferLimitExceeded : public IrcSpecificException {
    public:
        MessageBufferLimitExceeded();
    };

    class UserAlreadyOperator : public IrcSpecificException {
    public:
        UserAlreadyOperator();
        UserAlreadyOperator(std::string nick, std::string channel);
    };

    class UserAlreadyInvited : public IrcSpecificException {
    public:
        UserAlreadyInvited();
        UserAlreadyInvited(std::string nick, std::string channel);
    };

}
