/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:57:01 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/08 15:03:24 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

// * Includes
#include <iostream>
#include <stack>
#include <deque>

// * Class With Orthodox Canonical Form
// * Tempate Class
// template<typename T>
class BitcoinExchange {
    // ! public
    public:
        // * Default constructor
        BitcoinExchange();

        // * Copy constructor
        BitcoinExchange(const BitcoinExchange &other);

        // * Copy assignment operator
        BitcoinExchange &operator=(const BitcoinExchange &other);

        // * Destructor
        ~BitcoinExchange();

        // * Setters & Getters
        
        // * Methods
};
#endif