/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:35:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 17:05:43 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include "ft_irc.hpp"

namespace irc {
    
    class ACommand;

    class Ircserv {
    public:
        Ircserv(t_irc_exec_conf & conf);
        Ircserv(const Ircserv &);
        Ircserv & operator=(const Ircserv &);
        ~Ircserv();

        void clientConnect();
        void clientDisconnect(int fd);
        void clientMessage(int fd);
        void bindLoop();
        int readFromConfigFile(char *filename);

        std::vector<ACommand *> parseCommandStr(std::string & str);
    protected:
    private:
        Ircserv();
        addrinfo *_addrinfo;
        addrinfo _addrinfoHints;
        int _serverSock;
        std::string _password;
        bool *_isServerShut;
        std::vector<struct pollfd> _pfds;

        std::vector<User> _users;
        std::vector<t_server_op> _operators;
        
    };

}

#endif
