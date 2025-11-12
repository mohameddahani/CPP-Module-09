/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:24:34 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/12 10:58:18 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void mergeInsertionSort(int ac, char **av){
    // ? PARSING

    // * Create a Vector to store all number
    std::vector<long>vector;

    // * use str to long to convert from str to number
    char *end = NULL;
    // * we need to define the base of convert (10 = decimal)
    const int base = 10;

    // * number
    long number = 0;

    int j = 0;
    std::string str = "";
    int size = 0;
    for (int i = 1; i < ac; ++i){
        // * skip white spaces
        // * remove it from front
        for (j = 0; std::isspace(av[i][j]); j++){}
        
        // * convert char * to std::string to do substr()
        str = (av[i]);
        if (j != 0){
            str.erase(0, j);
        }

        // * remove it from back
        size = str.length();
        
        for (j = 0; std::isspace(str[size - 1]); j++){
            size--;
        }

        if (j != 0 && !str.empty()){
            str.erase(str.length() - j, str.length());
        }
        
        // * convert str to number
        number = strtol(str.c_str(), &end, base);
        if (*end != '\0'){
            throw std::runtime_error("Error: Bad input");
        }

        // * check if number are not positive
        if (number < 0){
            throw std::runtime_error("Error: The number be positive");
        }
        // * check if big than max int
        if (number > INT_MAX){
            throw std::runtime_error("Error: The number bigger than MAX INT");
        }
        
        // * push it to vector after converting
        vector.push_back(number);
    }

    // ? ALGORITHM
    
    // * print all things in vector
    std::vector<long>::iterator it = vector.begin();
    for( ; it != vector.end(); ++it){
        std::cout << *it << std::endl;
    }
    
}
