/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:44:38 by root              #+#    #+#             */
/*   Updated: 2024/09/11 18:51:49 by lhojoon          ###   ########.fr       */
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
}