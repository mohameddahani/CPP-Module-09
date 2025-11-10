/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:03 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/10 15:24:44 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac != 2){
        std::cerr << "Error: You should run only program with file that has Dates and Values" << std::endl;
        return 1;
    }


    try {
        // * Create a Map to store data
        std::multimap<std::string, std::string>map;

        // * Parse the file
        parseFile(av[1], map);
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}