/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:35:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 19:37:15 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include "ft_irc.hpp"

namespace irc {

class Ircserv {
public:
    Ircserv();
    Ircserv(t_irc_exec_conf & conf);
    Ircserv(const Ircserv &);
    Ircserv & operator=(const Ircserv &);
    ~Ircserv();
    
    void bindLoop();
protected:
private:
    addrinfo _addrinfo;
    int _serverSock;
    std::string _password;
};

}

#endif