/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:30:24 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/11 17:35:44 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

// * Includes
#include <iostream>
#include <algorithm>
#include <stack>

// * Functions
void rpnCalculation(std::stack<int>&stack, char sign);
void rpnParsing(std::string rpn);

#endif