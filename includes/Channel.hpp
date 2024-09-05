/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:40:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/05 17:49:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "User.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

namespace irc {

    class Channel {
		public:
			Channel();
			Channel(Channel &cpy);
			Channel &operator=(Channel &cpy);
			~Channel();

			std::string			getName();
			std::string			getTopic();
			std::string			getPassword();
			std::vector<User &> getUsers(void) const;
			std::vector<User &> getOperators(void) const;
			std::vector<User &> getInvitedUsers(void) const;
			int					getClientLimit();
			bool				isInvitOnly();
			bool				isTopicRestricted();
			void				setName(std::string name);
			void				setTopic(std::string topic);
			void				setPassword(std::string password);
			void				setClientLimit(int limit);
			void				changeInvitOnly();
			void				changeTopicRestrict();
			void				addOperators(User& user);
			int					sendToAll(std::string message);
			int 				joinUser(User& user);
			int 				kickUser(User& user);
			int 				inviteUser(User& user);
   		private:
			std::string 		_name;
			std::string 		_topic;
			std::string 		_channelPassword;
			std::vector<User *> _users;
			std::vector<User *> _operators;
			std::vector<User *> _invitedUsers;
			unsigned int		_clientLimit;
			bool				_invitOnly;
			bool				_topicRestriction;
    };
}

#endif
