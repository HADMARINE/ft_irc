/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:05:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/12 18:44:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    // 001
	RPLWelcome::RPLWelcome(User * user) {
		this->setCode("RPL_WELCOME");
		this->setNumeric(1);
		std::stringstream ss;
		ss << ":Welcome to the Internet Relay Network " << user->getNickname();
		if (!user->getUsername().empty() && !user->getRealname().empty())
			ss << "!" << user->getUsername() << "@" << user->getRealname();
		this->setMessage(ss.str());
	}

    // 002
	RPLYourHost::RPLYourHost() {
		this->setCode("RPL_YOURHOST");
		this->setNumeric(2);
		this->setMessage(":Your host is <servername>, running version <ver>");
	}

    // 003
	RPLCreated::RPLCreated() {
		this->setCode("RPL_CREATED");
		this->setNumeric(3);
		this->setMessage(":This server was created <date>");
	}

    // 004
	RPLMyInfo::RPLMyInfo() {
		this->setCode("RPL_MYINFO");
		this->setNumeric(4);
		this->setMessage("<servername> <version> <available user modes> <available channel modes>");
	}

    // 005
	RPLIsupport::RPLIsupport() {
		this->setCode("RPL_ISUPPORT");
		this->setNumeric(5);
		this->setMessage(":are supported by this server");
	}

    // 251
	RPLLUserClient::RPLLUserClient() {
		this->setCode("RPL_LUSERCLIENT");
		this->setNumeric(251);
		this->setMessage(":There are <integer> users and <integer> services on <integer> servers");
	}

    // 332
	RPLTopic::RPLTopic(User *user, Channel *channel) {
		this->setCode("RPL_TOPIC");
		this->setNumeric(332);
		this->setMessage(":" + user->getUsername() + " #" + channel->getName() + " :" + channel->getTopic());
	}

	// 353
	RPLNamReply::RPLNamReply(User *user, Channel *channel) {
		this->setCode("RPL_NAMREPLY");
		this->setNumeric(353);
		std::stringstream ss;
		std::vector<User *>	users;
		ss << ":" << user->getUsername() << " =#" << channel->getName() << " :";
		users = channel->getUsers();
		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it) {
			if (channel->isOperator(*it))
				ss << " @" << (*it)->getUsername();
			else
				ss << " " << (*it)->getUsername();
		}
		this->setMessage(ss.str());
	}

	// 366
	RPLEndOfNames::RPLEndOfNames(User *user, Channel *channel) {
		this->setCode("RPL_ENDOFNAMES");
		this->setNumeric(366);
		this->setMessage(":" + user->getUsername() + " #" + channel->getName() + " :End of /NAMES list");
	}
}
