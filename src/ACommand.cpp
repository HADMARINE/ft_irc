/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:47:28 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:37:16 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
    ACommand::ACommand() {}
    
    ACommand::ACommand(std::vector<std::string> params) {
        this->setParams(params);
    }
    
    void ACommand::setParams(std::vector<std::string> params) {
        this->_params = this->setParamsMiddleware(params);
    }

    std::vector<std::string> ACommand::setParamsMiddleware(std::vector<std::string> params) {
        return params;
    }
}
  //   size_t passPos = message.find("PASS "); // TODO : c'est pas bon ce truc
  //   if (passPos != std::string::npos) {
  //       std::string password = message.substr(passPos + 5);
  //       size_t endPos = password.find("\r\n");
  //       if (endPos != std::string::npos) {
  //           password = password.substr(0, endPos);
  //       }

  //       if (_password == password) {
  //           std::cout << "Client " << fd << " authenticated successfully" << std::endl;
  //       } else {
  //           std::cerr << "Client " << fd << " provided wrong password" << std::endl;
  //           pfd.fd = fd;
  //           pfd.events = POLLIN;
  //           pfd.revents = 0;
  //           _pfds.push_back(pfd);
  //           clientDisconnect(fd);
  //           return ;
  //       }
  //   }
  // }