/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:48:44 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/12 15:43:50 by lhojoon          ###   ########.fr       */
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
        conf.hostname = "localhost";

        return conf;
    }

    std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
        size_t last = 0;
        size_t next = 0;
        std::vector<std::string> svalues;
        while ((next = s.find(delimiter, last)) != std::string::npos) {
            svalues.push_back(s.substr(last, next - last));
            last = next + delimiter.length();
        } 
        svalues.push_back(s.substr(last));
        return svalues;
    }

    int getCRLFPos(char * str, size_t len) {
        char * s = str;
        if (!str) {
            return -1;
        }
        while (*s) {
            if (*s == '\r') {
                if (s - str < (int)len && *(s + 1) == '\n') {
                    return s - str;
                }
            }
            s += 1;
        }
        return -1;
    }

}