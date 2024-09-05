/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:40:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/05 15:33:43 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "User.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

namespace irc {

    class Channel {
    public:
		Channel(std::string name);
		Channel(const Channel &cpy);
		~Channel();
		Channel	&operator=(const Channel &cpy);
		int		sendToAll(std::string message);

		std::string			getName();
		std::string			getTopic();
		std::string			getPassword();
		std::vector<User &> getUsers(void) const;
		std::vector<User &> getOperators(void) const;
		std::vector<User &> getInvites(void) const;
		bool				isLimit();
		bool				isInvites();
		bool				isTopicRestricted();

		int		joinUser(User &user);
		int		kickUser(User &user);
        int		inviteUser(User &user);
		void	setTopic(std::string newTopic);
		void	setPassword(std::string newPassword);
		void	changeLimit(unsigned int limit);
		void	changeInvite();
		void	changeTopicRestrict();

	private:
		Channel();
        std::string _name;
        std::string _topic;
		std::string _channelPassword;

		std::vector<User *>	_users;
        std::vector<User *>	_operators;
        std::vector<User *>	_invitedUsers;
		unsigned int		_userLimit;
		bool				_onInvite;
		bool				_topicRestricted;
    };
}

#endif