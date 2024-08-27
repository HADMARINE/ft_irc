/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:48:44 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 17:46:26 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

namespace irc {
    t_irc_exec_conf getIrcExecConf(char *password, char *port) {
        if (!password || !port)
            throw std::runtime_error("parameters invalid : nullptr");
        
        std::string passwordStr(password), portStr(port);
        
        if (portStr.find_first_not_of("0123456789") != std::string::npos || // check is numeric, positive, non floating point
            passwordStr.empty())
            throw std::runtime_error("parameters invalid : constraint");
        
        t_irc_exec_conf conf;
        
        int portTmp;
        std::istringstream(portStr) >> portTmp; // string to int
        if (portTmp <= 0 || portTmp >= 65536) // check port range
            throw std::range_error("port range exceeded");
        if (portTmp <= 1023)
            std::cout << "Warning : ports below 1024 are reserved." << std::endl;
        
        conf.password = passwordStr;
        conf.port = portTmp;
        return conf;
    }
}