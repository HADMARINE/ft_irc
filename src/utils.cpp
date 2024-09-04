/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:48:44 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/04 23:07:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

namespace irc {
    t_irc_exec_conf getIrcExecConf(char *password, char *port, bool *isServerShut) {
        if (!password || !port || !isServerShut)
            throw std::runtime_error("parameters invalid - nullptr");
        
        std::string passwordStr(password), portStr(port);
        
        if (portStr.find_first_not_of("0123456789") != std::string::npos || // check is numeric, positive, non floating point
            passwordStr.empty())
            throw std::runtime_error("parameters invalid - port format incorrect");
        
        t_irc_exec_conf conf;
        
        int portTmp;
        std::istringstream(portStr) >> portTmp; // string to int
        if (portTmp <= 0 || portTmp >= 65536) // check port range
            throw std::range_error("port range exceeded");
        if (portTmp <= 1023)
            std::cout << "Warning : ports below 1024 are reserved." << std::endl;
        
        conf.password = passwordStr;
        conf.port = portTmp;
        conf.portStr = portStr;
        conf.isServerShut = isServerShut;

        return conf;
    }

    std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
        size_t last = 0;
        size_t next = 0;
        std::vector<std::string> svalues;
        while ((next = s.find(delimiter, last)) != std::string::npos) {
            svalues.push_back(s.substr(last, next - last));
            last = next + 1;
        } 
        svalues.push_back(s.substr(last));
        return svalues;
    }
}