/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:03 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/10 20:03:42 by mdahani          ###   ########.fr       */
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

        // * Store the data base
        getDataFomDataBase(map); 

        
        // std::map<std::string, std::string>::iterator it = map.begin();
        // for (; it != map.end(); ++it){
        //     std::cout << it->first << " " << it->second << std::endl;
        // }

        // * Parse the file
        parseFile(av[1], map);
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}