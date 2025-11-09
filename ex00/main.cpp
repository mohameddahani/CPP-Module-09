/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:03 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/09 10:56:15 by mdahani          ###   ########.fr       */
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
        std::map<std::string, std::string>map;

        // * Parse the file
        parseFile(av[1], map);

        std::cout << "==========print the map==========" << std::endl;
        std::map<std::string, std::string>::iterator it;
        for ( it = map.begin(); it != map.end(); ++it){
            std::cout << it->first << " " << it->second << std::endl;
        }
        
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}