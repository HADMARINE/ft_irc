/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:11:03 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/12 18:07:02 by root             ###   ########.fr       */
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
#include "NumericResponse.hpp"
#include "Errors.hpp"

namespace irc {
    class Ircserv;
    class ACommand;
}
