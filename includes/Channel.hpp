/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:40:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/31 22:22:19 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    class Channel {
    public:
        bool purgeUsers(const std::vector<User &> activeUsers); // Removes all disconected users from _activeUsers
        std::vector<User &> getUsers(void) const;
    private:
        std::string _name;
        std::string _topic;


        std::vector<User &> _activeUsers;
        
        std::vector<User &> _kickedUsers;
        std::vector<User &> _bannedUsers; // Must not be deleted even user disconnection
        std::vector<User &> _operators;
        std::vector<User &> _voicedUsers; // TODO : Search what this does

        std::string _operatorPassword;
        std::string _channelPassword;
        unsigned int _mod;
        unsigned int _maxUserCapacity;
    };
}