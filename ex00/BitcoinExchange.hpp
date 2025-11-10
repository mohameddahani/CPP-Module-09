/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:57:01 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/10 15:22:44 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

// * Includes
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>

// * Functions
void parseFile(std::string fileName, std::multimap<std::string, std::string>&map);
void printCalculation(std::string date, std::string value);

#endif