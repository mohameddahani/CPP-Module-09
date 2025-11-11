/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:30:24 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/11 08:57:46 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

// * Includes
#include <iostream>
#include <algorithm>
#include <stack>

// * Functions
bool rpnParsing(std::string rpn);
void rpnCalculation(std::string rpn);

#endif