/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:40:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/09 17:19:33 by lhojoon          ###   ########.fr       */
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
			Channel(Channel &cpy);
			Channel &operator=(Channel &cpy);
			~Channel();

			const std::string & getName() const;
			const std::string & getTopic() const;
			const std::string & getPassword() const;
			std::vector<User *> getUsers() const;
			std::vector<User *> getOperators() const;
			std::vector<User *> getInvitedUsers() const;
			int					getUserLimit();
			bool				isInviteOnly();
			bool				isTopicRestricted();
			void				setName(std::string & name);
			void				setTopic(std::string & topic);
			void				setPassword(std::string & password);
			void				setUserLimit(int limit);
			void				changeInvitOnly();
			void				changeTopicRestrict();
			void				addOperators(User * user);
			bool				isOperator(User * user);
			void				sendToAll(std::string & message);
			void 				joinUser(User * user);
			void 				kickUser(User * user);
			void 				inviteUser(User * user);
			bool				isUserInChannel(const User * user);
   		private:
			Channel();
			std::string 		_name;
			std::string 		_topic;
			std::string 		_channelPassword;
			std::vector<User *> _users;
			std::vector<User *> _operators;
			std::vector<User *> _invitedUsers;
			unsigned int		_userLimit;
			bool				_onInvite;
			bool				_topicRestriction;
    };
}

#endif
