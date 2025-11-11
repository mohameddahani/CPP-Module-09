/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:29:43 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/11 17:37:25 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av){
      if (ac != 2){
        std::cerr << "Error: You should run only program with Polish Notation" << std::endl;
        return 1;
    }

    // * Parse and calculate the RPN
    try {
        rpnParsing(av[1]);        
    } catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}