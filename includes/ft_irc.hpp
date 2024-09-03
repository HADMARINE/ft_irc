/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:11:03 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:17:09 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include "includes.hpp"
#include "definitions.hpp"
#include "ircstruct.hpp"
#include "utils.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "ircserv.hpp"
#include "ACommand.hpp"
#include "Commands.hpp"
#include "EIrcException.hpp"
#include "IrcSpecificException.hpp"
#include "Errors.hpp"

namespace irc {
    class Ircserv;
    class ACommand;
}

#endif
