/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:14:05 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/17 13:56:18 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {
    // 401
    class NoSuchNick : public IrcSpecificResponse {
    public:
        NoSuchNick();
        NoSuchNick(std::string nick);
    };

    // 402
    class NoSuchServer : public IrcSpecificResponse {
    public:
        NoSuchServer();
        NoSuchServer(std::string server);
    };

    // 403
    class NoSuchChannel : public IrcSpecificResponse {
    public:
        NoSuchChannel();
        NoSuchChannel(std::string channel);
    };

    // 404
    class CannotSendToChan : public IrcSpecificResponse {
    public:
        CannotSendToChan();
        CannotSendToChan(std::string channel);
    };

    // 421
    class UnknownCommand : public IrcSpecificResponse {
    public:
        UnknownCommand();
        UnknownCommand(std::string cmd);
    };

    // 431
    class NoNicknameGiven : public IrcSpecificResponse {
    public:
        NoNicknameGiven();
    };

    // 432
    class ErroneusNickName : public IrcSpecificResponse {
    public:
        ErroneusNickName();
        ErroneusNickName(std::string nick);
    };

    // 433
    class NicknameInUse : public IrcSpecificResponse {
    public:
        NicknameInUse();
        NicknameInUse(std::string nick);
    };

    // 441
    class UserNotInChannel : public IrcSpecificResponse {
    public:
        UserNotInChannel();
        UserNotInChannel(std::string nick, std::string channel);
    };

    // 442
    class NotOnChannel : public IrcSpecificResponse {
    public:
        NotOnChannel();
        NotOnChannel(std::string channel);
    };

    // 443
    class UserOnChannel : public IrcSpecificResponse {
    public:
        UserOnChannel(User *user);
        UserOnChannel(std::string nick, std::string channel);
    };

    // 461
    class NeedMoreParams : public IrcSpecificResponse {
    public:
        NeedMoreParams();
        NeedMoreParams(std::string cmd);
    };

    // 462
    class AlreadyRegistered : public IrcSpecificResponse {
    public:
        AlreadyRegistered();
    };

    // 464
    class PasswordMisMatch : public IrcSpecificResponse {
    public:
        PasswordMisMatch();
    };

    // 473
    class InviteOnlyChan : public IrcSpecificResponse {
    public:
        InviteOnlyChan();
        InviteOnlyChan(std::string channel);
    };

    // 475
    class BadKey : public IrcSpecificResponse {
      public :
        BadKey();
    };

    // 481
    class NoPrivileges : public IrcSpecificResponse {
    public:
        NoPrivileges();
    };

    // ~~~ Custom exceptions from here which are not defined in RFC1459 ~~~

	class ChannelFull : public IrcSpecificResponse {
    public:
        ChannelFull();
    };

    class IsTopicRestricted : public IrcSpecificResponse {
    public:
        IsTopicRestricted();
    };

    class TooManyParameters : public IrcSpecificResponse {
    public:
        TooManyParameters();
        TooManyParameters(std::string condition, size_t receivedNum);
    private:
    };

    class UserNotFound : public IrcSpecificResponse {
    public:
        UserNotFound();
    };

    class MessageBufferLimitExceeded : public IrcSpecificResponse {
    public:
        MessageBufferLimitExceeded();
    };

    class UserAlreadyOperator : public IrcSpecificResponse {
    public:
        UserAlreadyOperator();
        UserAlreadyOperator(std::string nick, std::string channel);
    };

    class UserAlreadyInvited : public IrcSpecificResponse {
    public:
        UserAlreadyInvited();
        UserAlreadyInvited(std::string nick, std::string channel);
    };

}
