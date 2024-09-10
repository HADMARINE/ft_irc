/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:18:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/10 16:53:34 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "ft_irc.hpp"


namespace irc {

    class Ircserv;

    class ACommand {
    public:
        ACommand();
        virtual int resolve(Ircserv * server, User * user) = 0; // return 0 if success
        void setParams(std::vector<std::string> params);
        int execute(Ircserv * server, User * user);
        virtual std::vector<std::string> setParamsMiddleware(std::vector<std::string> params);
        virtual void permissionCheckMiddleware(Ircserv * server, User * user);
        virtual ~ACommand();
    protected:
        std::vector<std::string> _params;
    private:
    };
}
