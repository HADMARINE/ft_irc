/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:41 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/05 15:30:14 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

bool isServerShut = false;

static void signalHdlr(int sig) {
    (void)sig;
    isServerShut = true;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc == 2 && strncmp(argv[1], "help", 5) == 0) {
        std::cout << "Usage : ./ircserv <password> <port>" << std::endl;
        std::cout << "\t<password> : non void string value\n\t<port> : number in range of 1 ~ 65535\n\n";
        std::cout << "Happy hacking !" << std::endl;
        return 0;
    }
    std::cout << "ircserv launched" << std::endl;
    if (argc != 3)
    {
        std::cerr << "Error : invalid parameters\n" << std::endl;
        std::cout << "Usage : ./ircserv <password> <port>" << std::endl;
        std::cout << "\t<password> : non void string value\n\t<port> : number in range of 1 ~ 65535\n\n";
        std::cout << "Happy hacking !" << std::endl;
        return 1;
    }
    try {
        irc::t_irc_exec_conf conf;
        conf = irc::getIrcExecConf(argv[1], argv[2], &isServerShut);
        
        irc::Ircserv server(conf);
        
        signal(SIGINT, signalHdlr);
        server.readFromConfigFile(const_cast<char *>("../config/servop.config"));
        server.bindLoop();
        
    } catch (std::exception & e) {
        std::cerr << "Launch failed : " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "La SNCF et ses équipes vous souhaitent un agréable voyage. À bientôt !" << std::endl;
    return 0;
}
