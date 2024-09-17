/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:05:22 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/17 14:20:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    // 001
	RPLWelcome::RPLWelcome(User * user) {
		this->setCode("RPL_WELCOME");
		this->setNumeric(1);
		std::stringstream ss;
		ss << user->getUsername() << " :Welcome to the Internet Relay Network " << user->getNickname();
		if (!user->getUsername().empty() && !user->getRealname().empty())
			ss << "!" << user->getUsername() << "@" << user->getRealname();
		this->setMessage(ss.str());
	}

    // 002
        RPLYourHost::RPLYourHost(User * user, std::string hostname, std::string version) {
            this->setCode("RPL_YOURHOST");
            this->setNumeric(2);
            std::stringstream ss;
            ss << user->getUsername() << " :Your host is " << hostname << ", running version " << version;
            this->setMessage(ss.str());
        }

    // 003
        RPLCreated::RPLCreated(User * user, std::time_t * time) {
            this->setCode("RPL_CREATED");
            this->setNumeric(3);
            std::tm * now = std::localtime(time);
            std::stringstream ss;
            ss << user->getUsername() << " :This server was created "
            << (now->tm_year + 1900) << '-'
            << (now->tm_mon + 1) << '-'
            <<  now->tm_mday << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec;
            this->setMessage(ss.str());
        }

    // 004
	RPLMyInfo::RPLMyInfo(User * user) {
		this->setCode("RPL_MYINFO");
		this->setNumeric(4);
		std::stringstream ss;
		ss << user->getUsername() << "<servername> <version> <available user modes> <available channel modes>";
		this->setMessage(ss.str());
	}

    // 005
	RPLIsupport::RPLIsupport(User * user) {
		this->setCode("RPL_ISUPPORT");
		this->setNumeric(5);
		std::stringstream ss;
		ss << user->getUsername() << " :are supported by this server";
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
		this->setMessage(user->getUsername() + " " + channel->getName() + " :" + channel->getTopic());
	}

	// 353
	RPLNamReply::RPLNamReply(User *user, Channel *channel) {
		this->setCode("RPL_NAMREPLY");
		this->setNumeric(353);
		std::stringstream ss;
		std::vector<User *>	users;
		ss << user->getNickname() << " @ #" << channel->getName() << " :";
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
	RPLEndOfNames::RPLEndOfNames(User *user, Channel *channel) {
		this->setCode("RPL_ENDOFNAMES");
		this->setNumeric(366);
		this->setMessage(user->getNickname() + " #" + channel->getName() + " :End of /NAMES list.");
	}
}
