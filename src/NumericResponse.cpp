/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:05:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/28 17:32:58 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    // 001
	RPLWelcome::RPLWelcome(User * user) {
		this->setCode("RPL_WELCOME");
		this->setNumeric(1);
		std::stringstream ss;
		ss << user->getNickname() << " :Welcome to the Internet Relay Network " << user->getNickname();
		this->setMessage(ss.str());
	}

    // 002
        RPLYourHost::RPLYourHost(User * user, std::string hostname, std::string version) {
            this->setCode("RPL_YOURHOST");
            this->setNumeric(2);
            std::stringstream ss;
            ss << user->getNickname() << " :Your host is " << hostname << ", running version " << version;
            this->setMessage(ss.str());
        }

    // 003
        RPLCreated::RPLCreated(User * user, std::time_t * time) {
            this->setCode("RPL_CREATED");
            this->setNumeric(3);
            std::tm * now = std::localtime(time);
            std::stringstream ss;
            ss << user->getNickname() << " :This server was created "
            << (now->tm_year + 1900) << '-'
            << std::setfill('0') << std::setw(2) << (now->tm_mon + 1) << '-'
            << std::setfill('0') << std::setw(2) <<  now->tm_mday << ' '
			<< std::setfill('0') << std::setw(2) << now->tm_hour << ':'
			<< std::setfill('0') << std::setw(2) << now->tm_min << ':'
			<< std::setfill('0') << std::setw(2) << now->tm_sec;
            this->setMessage(ss.str());
        }

    // 004
	RPLMyInfo::RPLMyInfo(User * user) {
		this->setCode("RPL_MYINFO");
		this->setNumeric(4);
		std::stringstream ss;
		ss << user->getNickname() << " :<servername> <version> <available user modes> <available channel modes>";
		this->setMessage(ss.str());
	}

    // 005
	RPLIsupport::RPLIsupport(User * user) {
		this->setCode("RPL_ISUPPORT");
		this->setNumeric(5);
		this->setMessage(user->getNickname() + " :are supported by this server");
	}

    // 251
	RPLLUserClient::RPLLUserClient() {
		this->setCode("RPL_LUSERCLIENT");
		this->setNumeric(251);
		this->setMessage(":There are <integer> users and <integer> services on <integer> servers");
	}

  // 324
  RPLChannelModeIs::RPLChannelModeIs(User *user, Channel *channel) {
		this->setCode("RPL_CHANNELMODEIS");
		this->setNumeric(324);
		std::stringstream ss;
			ss << user->getNickname() << " #" << channel->getName();
		if (channel->isInviteOnly() || channel->isTopicRestricted() || channel->isPasswordRequired() ||channel->isUserLimit())
			ss << " +";
		if (channel->isInviteOnly())
			ss << "i";
		if (channel->isTopicRestricted())
			ss << "t";
		if (channel->isPasswordRequired())
			ss << "k";
		if (channel->isUserLimit())
			ss << "l";
		this->setMessage(ss.str());
	}

	// 331
	RPLNoTopic::RPLNoTopic(User *user, Channel * channel) {
		this->setCode("RPL_NOTOPIC");
		this->setNumeric(331);
		std::stringstream ss;
		ss << user->getNickname() << " #" << channel->getName() << " :No topic is set";
		this->setMessage(ss.str());
	}

    // 332
	RPLTopic::RPLTopic(User *user, Channel * channel) {
		this->setCode("RPL_TOPIC");
		this->setNumeric(332);
		std::stringstream ss;
		ss << user->getNickname() << " #" << channel->getName() << " :" << channel->getTopic();
		this->setMessage(ss.str());
	}

	// 353
	RPLNamReply::RPLNamReply(User *user, Channel * channel) {
		this->setCode("RPL_NAMREPLY");
		this->setNumeric(353);
		std::stringstream ss;
		std::vector<User *>	users;
		// TODO (maybe) : faut changer le symbole selon les types des channels - public = secret @ private *
		ss << user->getNickname() << " = #" << channel->getName() << " :";
		users = channel->getUsers();
		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it) {
			if (it != users.begin())
				ss << " ";
			if (channel->isOperator(*it))
				ss << "@" << (*it)->getNickname();
			else
				ss <<  (*it)->getNickname();
		}
		this->setMessage(ss.str());
	}

	// 366
	RPLEndOfNames::RPLEndOfNames(User *user, Channel * channel) {
		this->setCode("RPL_ENDOFNAMES");
		this->setNumeric(366);
		std::stringstream ss;
		ss << user->getNickname() << " #" << channel->getName() << " :End of /NAMES list.";
		this->setMessage(ss.str());
	}
}
