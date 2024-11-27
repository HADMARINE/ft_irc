/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:55:39 by root              #+#    #+#             */
/*   Updated: 2024/11/27 15:28:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cout << "USAGE: ./bot PORT PASS" << std::endl;
        return (1);
    }
    try {
        Bot bot(av[1], av[2]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
