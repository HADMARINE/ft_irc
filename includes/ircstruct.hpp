/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircstruct.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:05:10 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/12 18:40:23 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {

typedef struct s_exec_conf {
    std::string password; // server password
    short port; // 0 ~ 65535
    std::string portStr;
    bool *isServerShut;
    std::string hostname;
    std::time_t time;
} t_irc_exec_conf;

typedef struct s_server_op
{
	std::string name;
	std::string	host;
	std::string	password;
} t_server_op;

}
