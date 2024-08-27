/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircstruct.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:05:10 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 15:50:04 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSTRUCT_HPP
#define IRCSTRUCT_HPP

#include "ft_irc.hpp"

namespace irc {

typedef struct s_exec_conf {
    std::string password; // server password
    unsigned short port; // 0 ~ 65535
} t_irc_exec_conf;

}

#endif