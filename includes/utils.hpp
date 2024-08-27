/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:50:52 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 17:33:22 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "ft_irc.hpp"

namespace irc {
    /**
     * @param password must not be empty, must not be nullptr
     * @param port must not exceed range of 1 ~ 65535, must not be nullptr
     */
    t_irc_exec_conf getIrcExecConf(char *password, char *port);
}

#endif