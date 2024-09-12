/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:44:38 by root              #+#    #+#             */
/*   Updated: 2024/09/12 18:20:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {
    // 001
    class RPLWelcome : public IrcSpecificResponse {
    public:
        RPLWelcome(User * user);
    };

    // 002
    class RPLYourHost : public IrcSpecificResponse {
    public:
        RPLYourHost();
    };

    // 003
    class RPLCreated : public IrcSpecificResponse {
    public:
        RPLCreated();
    };

    // 004
    class RPLMyInfo : public IrcSpecificResponse {
    public:
        RPLMyInfo();
    };

    // 005
    class RPLIsupport : public IrcSpecificResponse {
    public:
        RPLIsupport();
    };

    // 251
    class RPLLUserClient : public IrcSpecificResponse {
    public:
       RPLLUserClient();
    };

    // 332
    class RPLTopic : public IrcSpecificResponse {
    public:
		RPLTopic(User *user, Channel *channel);
    };

	// 353
	class RPLNamReply : public IrcSpecificResponse {
	public:
		RPLNamReply(User *user, Channel *channel);
	};

	// 366
	class RPLEndOfNames : public IrcSpecificResponse {
	public:
		RPLEndOfNames(User *user, Channel *channel);
	};
}
