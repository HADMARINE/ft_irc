/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:40:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 13:40:40 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "User.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

namespace irc {

    enum EChannelMode {
        CHANNELMOD_BAN_MASK = 1,
        CHANNELMOD_NO_MESSAGES_TO_CHANNEL = 2,
        CHANNELMOD_TOPIC_SETTABLE = 4,
        CHANNELMOD_USER_LIMIT = 8,
        CHANNELMOD_MODERATED_CHANNEL = 16,
        CHANNELMOD_INVITATION = 32,
        CHANNELMOD_CHANNEL_KEY = 64,
        CHANNELMOD_SECRET_CHANNEL = 128,
        CHANNELMOD_PRIVATE_CHANNEL = 256
    };

    class Channel {
    public:
        bool purgeUsers(const std::vector<User &> activeUsers); // Removes all disconected users from _activeUsers
        std::vector<User &> getUsers(void) const;

        int joinUser(User & user);
        int joinUser(std::vector<User &> users);
        
        int removeUser(User & user);
        int removeUser(std::vector<User &> users);

        int banUser(User & user);
        int banUser(std::vector<User &> users);

        int kickUser(User & user);
        int kickUser(std::vector<User &> users);

        int inviteUser(User & user);
        int inviteUser(std::vector<User &> users);
    private:
        std::string _name;
        std::string _topic;


        std::vector<User *> _activeUsers;
        
        std::vector<User *> _kickedUsers;
        std::vector<User *> _bannedUsers; // Must not be deleted even user disconnection
        std::vector<User *> _operators;
        std::vector<User *> _voicedUsers; // TODO : Search what this does
        std::vector<User *> _invitedUsers; // Must be purged on purgeUsers

        std::string _operatorPassword;
        std::string _channelPassword;
        unsigned int _mod; // Refer EChannelMod
        unsigned int _maxUserCapacity;
    };
}

#endif