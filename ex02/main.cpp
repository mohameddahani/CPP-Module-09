/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:26:05 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/12 08:30:26 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av){

    if (ac == 1){
        std::cerr << "Error: You should add numbers" << std::endl;
        return 1;
    }

    try {
        
    } catch(const std::exception &e){
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}