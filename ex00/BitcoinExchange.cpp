/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:58 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/08 21:09:23 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ! Definitions of functions

bool parseFile(std::string fileName){
    // * Open the file
    std::ifstream inputFile(fileName.c_str());
    if (!inputFile.is_open()){
        std::cerr << "File is not open!" << std::endl;
        return false;
    }

    // * Create a Map to store data
    std::map<std::string, std::string>map;
    
    // * Read from the file
    std::string line;
    unsigned int i = 0;
    while (std::getline(inputFile, line)){
        // * skip the line if empty
        if (line.empty()){
            continue;
        }
        
        // * Skip white spaces from front of line
        unsigned int j = 0;
        while (line[j] <= 32 && line[j] > 0){
            j++;
        }
        
        // * Skip white spaces from back of line
        unsigned int size = line.length();
        unsigned int end = 0;
        while (line[size - 1] <= 32 && line[size - 1] > 0){
            size--;
            end++;
        }

        if (j != 0){
            line.erase(0, j);
        }

        if (end != 0){
            line.erase(line.length() - end, line.length());
        }
        
        
        std::cout << "line after skip spaces: " << line << std::endl;
        
        // * check the first line has (date | value)
        if (i == 0){        
            if (line != "date | value"){
                return false;
            }
            
        }
        i++;
    }

    return true;
    
}