/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:18:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/11/27 12:48:15 by root             ###   ########.fr       */
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
