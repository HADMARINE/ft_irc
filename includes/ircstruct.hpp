/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircstruct.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:05:10 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:49:08 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSTRUCT_HPP
#define IRCSTRUCT_HPP

#include "ft_irc.hpp"

namespace irc {

typedef struct s_exec_conf {
    std::string password; // server password
    short port; // 0 ~ 65535
    std::string portStr;
    bool *isServerShut;
} t_irc_exec_conf;

typedef struct s_server_op
{
	std::string name;
	std::string	host;
	std::string	password;
} t_server_op;

}

#endif