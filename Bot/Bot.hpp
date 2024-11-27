/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:47:20 by root              #+#    #+#             */
/*   Updated: 2024/11/27 15:25:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
# include <iostream>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <string>
# include <vector>
# include <signal.h>

class Bot {
	public:
		Bot(std::string port, std::string pass);
		~Bot();
		Bot(const Bot &cpy);
		Bot &operator=(const Bot &cpy);
};
