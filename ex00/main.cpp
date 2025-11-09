/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:03 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/09 08:34:10 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac != 2){
        std::cerr << "Error: You should run only program with file that has Dates and Values" << std::endl;
        return 1;
    }


    try {
        parseFile(av[1]);
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}