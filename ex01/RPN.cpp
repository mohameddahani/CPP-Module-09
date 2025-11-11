/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:53:47 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/11 10:22:31 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool rpnParsing(std::string rpn){

    bool checkFirstTwoNumbers = true;
    bool isNumber = false;
    bool isOperator = false;
    
    for (size_t i = 0; i < rpn.length(); i++){
        // * Skip white spaces
        while(rpn[i] && rpn[i] <= 32 && rpn[i] > 0){
            i++;
        }
        
        // * check if the first two is numbers (not operators)
        if (checkFirstTwoNumbers){
            for (size_t j = 0; j < 2; j++){
                // * Skip white spaces
                while(rpn[i] && rpn[i] <= 32 && rpn[i] > 0){
                    i++;
                }
                // * Check if is number
                if (!std::isdigit(rpn[i])){
                    return false;
                }

                // * check if the index not null terminited
                if (rpn[i]){
                    i++;
                }
            }

            checkFirstTwoNumbers = false;
            isNumber = true;

            continue;
        }

        
        // * check Opeartor
        if (isNumber){
            if (rpn[i] != '+' && rpn[i] != '-' && rpn[i] != '*' && rpn[i] != '/'){
                return false;
            }

            isOperator = true;
            isNumber = false;
        }
        // * check Number
        else if (isOperator){
            if (!std::isdigit(rpn[i])){
                return false;
            }
            isNumber = true;
            isOperator = false;
        }
        
    }
    
    return true;
}

void rpnCalculation(std::string rpn){
    (void)rpn;
}
