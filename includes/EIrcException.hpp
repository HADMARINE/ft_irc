/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EIrcException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:18:04 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 15:21:07 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EIRCEXCEPTION_HPP
#define EIRCEXCEPTION_HPP

namespace irc {
    enum EIrcException {
      ERR_NEEDMOREPARAMS = 461,
    };
}

#endif