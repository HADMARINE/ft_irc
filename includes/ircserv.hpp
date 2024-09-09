/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:35:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 17:05:25 by lhojoon          ###   ########.fr       */
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

        std::vector<User> & getUsers() { return this->_users; }
        const std::string & getPassword() const { return this->_password; }

        User * findUserByFd(int fd);
        User * findUserByNick(std::string & nick);
        Channel * findChannelByName(std::string & name);

        void sendToAll(std::string & message);
        void sendToSpecificDestination(std::string & message, User * user);
        void sendToSpecificDestination(std::string & message, std::vector<User *> users);
        void sendToSpecificDestination(std::string & message, Channel * channel);

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
        struct pollfd _serverPfd;

        std::vector<User> _users;
		std::vector<Channel> _channels;
		std::vector<t_server_op> _operators;
    };

}

#endif
