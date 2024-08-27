/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:41 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/27 20:38:42 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int argc, char **argv)
{
    std::cout << "ircserv launched" << std::endl;
    if (argc != 3)
    {
        std::cerr << "Error : invalid parameters\n" << std::endl;
        std::cout << "Usage : ./ircserv <password> <port>" << std::endl;
        std::cout << "\t<password> : non void string value\n\t<port> : number in range of 1 ~ 65535" << std::endl;
        std::cout << "Happy hacking !" << std::endl;
        return 1;
    }
    try {
        irc::t_irc_exec_conf conf;
        conf = irc::getIrcExecConf(argv[1], argv[2]);
        
        irc::Ircserv server(conf);
        
        server.bindLoop();
        
    } catch (std::exception & e) {
        std::cerr << "Launch failed : " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "La SNCF et ses équipes vous souhaite un agréable voyage. À bientôt !" << std::endl;
    return 0;
}
