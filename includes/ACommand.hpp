/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:18:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/08/31 22:09:38 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


namespace irc {
    class ACommand {
    public:
        virtual int resolve() = 0;
    protected:
        std::string _cmd;
        std::vector<std::string> _params;
    private:
    };
}