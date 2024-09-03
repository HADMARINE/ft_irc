/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeurConfig.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:30:58 by bfaisy            #+#    #+#             */
/*   Updated: 2024/09/03 16:55:40 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int 		irc::Ircserv::readFromConfigFile(char *filename)
{
	std::ifstream				data;
	std::string					buffer;
	std::vector<std::string>	operators;

	data.open(filename);
	if (!data)
		return (0);
	while (getline(data, buffer)) {
		operators.push_back(buffer);
	}
	data.close();

	std::vector<std::string>::iterator it;
	for (it = operators.begin(); it != operators.end(); it++)
	{
		std::string	line = *it;
		t_server_op	op;
		
		int len = line.size() - (line.size() - line.find_first_of(' '));

		op.name.insert(0, line, 0, len);
		op.host.insert(0, line, len + 1, line.find_last_of(' ') - len - 1);
		op.password.insert(0, line, line.find_last_of(' ') + 1, line.size() - 1);
		
		_operators.push_back(op);
	}
   return (1);
}