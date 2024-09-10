/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:11:03 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 22:19:31 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"
#include "definitions.hpp"
#include "ircstruct.hpp"
#include "utils.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "ircserv.hpp"
#include "ACommand.hpp"
#include "Commands.hpp"
#include "IrcSpecificResponse.hpp"
#include "Errors.hpp"

namespace irc {
    class Ircserv;
    class ACommand;
}

