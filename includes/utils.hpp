/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:50:52 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 15:38:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {
    /**
     * @param password must not be empty, must not be nullptr
     * @param port must not exceed range of 1 ~ 65535, must not be nullptr
     */
    t_irc_exec_conf getIrcExecConf(char *password, char *port, bool *isServerShut);
    std::vector<std::string> split(const std::string& s, const std::string& delimiter);
    int getCRLFPos(char * str, size_t len);


}
