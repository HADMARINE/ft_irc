/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:35:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/16 18:03:18 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {

    class ACommand;
    class IrcSpecificResponse;

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
        std::vector<Channel> & getChannels() { return this->_channels; }
        const std::string & getMotd() const { return this->_motd; }
        const std::string & getHostname() const { return this->_hostname; }

        void addChannel(Channel channel);

        void setMotd(std::string & motd) { this->_motd = motd; }


        User * findUserByFd(int fd); // User * can be null
        User * findUserByFdSafe(int fd); // User * cannot be null, throw when null
        User * findUserByNick(std::string & nick); // User * can be null
        User * findUserByNickSafe(std::string & nick); // User * cannot be null, throw when null
        Channel * findChannelByName(std::string & name);
        Channel * findChannelByNameSafe(std::string & name);

        void sendToAll(std::string & message);
        void sendToSpecificDestination(const std::string & message, User * user);
        void sendToSpecificDestination(const std::string & message, std::vector<User *> users);
        void sendToSpecificDestination(const std::string & message, Channel * channel);

        void removeUser(User * user); // remove user from _users
        void disconnectUser(User * user); // Disconnect totally from server

        std::vector<ACommand *> parseCommandStr(std::string & str);
        std::string formatResponse(std::string message);
        std::string formatResponse(User * origin, std::string message);
        std::string formatResponse(IrcSpecificResponse message);

    protected:
    private:
        Ircserv();
        addrinfo _addrinfoHints;
        int _serverSock;
        std::string _password;
        bool *_isServerShut;
        std::time_t _time;
        std::string _hostname;


        std::vector<struct pollfd> _pfds;

        std::vector<User> _users;
		std::vector<Channel> _channels;
		std::vector<t_server_op> _operators;
        std::string _motd;
    };

}
