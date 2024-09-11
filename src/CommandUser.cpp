/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:38:42 by root              #+#    #+#             */
/*   Updated: 2024/09/11 18:52:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

namespace irc {
	int CommandUSER::resolve(User * user) {
		user->setRealname(_params.at(3));
		user->setUsername(_params.at(0));
        return 0;
    }
    std::vector<std::string> CommandUSER::setParamsMiddleware(std::vector<std::string> params) {
        if (params.size() < 4) {
            throw NeedMoreParams();
        }
        if (params.size() > 4) {
            throw TooManyParameters("4", params.size());
        }
        return params;
    }
}
