/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:29:43 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/11 08:59:03 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av){
      if (ac != 2){
        std::cerr << "Error: You should run only program with Polish Notation" << std::endl;
        return 1;
    }

    // * Parse the RPN
    if (!rpnParsing(av[1])){
        std::cerr << "Error: RPN not valid!" << std::endl;
        return 1;
    }
    
    return 0;
}