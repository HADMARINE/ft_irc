/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:14:05 by lhojoon           #+#    #+#             */
/*   Updated: 2024/09/03 16:22:22 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
#define ERRORS_H

#include "ft_irc.hpp"

namespace irc {
    class TooManyParameters : public IrcSpecificException {
    public:
        TooManyParameters();
        TooManyParameters(std::string condition, size_t receivedNum);
        std::string what();
    private:
        
    };
}

#endif