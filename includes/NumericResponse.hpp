/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:44:38 by root              #+#    #+#             */
/*   Updated: 2024/09/18 13:32:02 by root             ###   ########.fr       */
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
        RPLYourHost(User * user, std::string hostname, std::string version);
    };

    // 003
    class RPLCreated : public IrcSpecificResponse {
    public:
        RPLCreated(User * user, std::time_t * time);
    };

    // 004
    class RPLMyInfo : public IrcSpecificResponse {
    public:
        RPLMyInfo(User * user);
    };

    // 005
    class RPLIsupport : public IrcSpecificResponse {
    public:
        RPLIsupport(User * user);
    };

    // 251
    class RPLLUserClient : public IrcSpecificResponse {
    public:
       RPLLUserClient();
    };

	// 331
	class RPLNoTopic : public IrcSpecificResponse {
	public:
		RPLNoTopic(User *user, Channel *channel);
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
