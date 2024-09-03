/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcSpecificException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:24:11 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 15:37:39 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSPECIFICEXCEPTION_HPP
#define IRCSPECIFICEXCEPTION_HPP

#include "ft_irc.hpp"

namespace irc {
    class IrcSpecificException {
        IrcSpecificException();
    private:
        std::string _code;
    };
}

#endif