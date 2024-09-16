/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:40:47 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/16 18:24:59 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

namespace irc {

    class Channel {
		public:
			Channel(std::string name);
			//Channel(Channel &cpy);
			Channel &operator=(const Channel &cpy);
			~Channel();

			const std::string & getName() const;
			const std::string & getTopic() const;
			const std::string & getPassword() const;
			std::vector<User *> getUsers() const;
			std::vector<User *> getOperators() const;
			std::vector<User *> getInvitedUsers() const;
			unsigned int		getUserLimit();
			bool				isInviteOnly();
			bool				isTopicRestricted();
			void				setName(std::string & name);
			void				setTopic(std::string & topic);
			void				setPassword(std::string & password);
			void				setUserLimit(int limit);
			void				changeInviteOnly(bool cond);
			void				changeTopicRestrict(bool cond);
			void				addOperator(User * user);
			void				removeOperator(User * user);
			bool				isOperator(User * user);
			bool				isPasswordRequired();
			void 				addUser(User * user);
			void 				removeUser(User * user);
			void 				inviteUser(User * user);
			bool				isInvitedUser(User * user);
			bool				isUserInChannel(const User * user);
			void				setPasswordRequired(bool cond);
			void				isUserLimit(bool cond);
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
			bool				_isPasswordRequired;
			bool				_isUserLimit;
    };
}
