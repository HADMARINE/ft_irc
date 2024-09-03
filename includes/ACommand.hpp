/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:18:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:58:49 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include "ft_irc.hpp"


namespace irc {

    class Ircserv;

    class ACommand {
    public:
        ACommand();
        ACommand(std::vector<std::string> params);
        virtual int resolve(Ircserv & server, int fd) = 0; // 0 if success
        void setParams(std::vector<std::string> params);
        virtual std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
    protected:
        std::vector<std::string> _params;
    private:
    };
}

#endif