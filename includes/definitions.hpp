/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:44:25 by root              #+#    #+#             */
/*   Updated: 2024/09/10 15:44:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_irc.hpp"

#define IRC_LISTEN_BACKLOG 100


// ~~~ DEBUG CMD DEF

#define DEBUG

#ifdef DEBUG

#define DCMD(x) x

#else

#define DCMD(x)

#endif



// ~~~ END ~~~
