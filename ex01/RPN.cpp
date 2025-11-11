/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:53:47 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/11 18:13:58 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void rpnCalculation(std::stack<int>&stack, char sign){
    
    int firstNumber = 0;
    int secondNumber = 0;
    int result = 0;

    // * check how many element in stack
    if (stack.size() <= 1){
        throw std::runtime_error("Error: you have only 1 number or less in stack");
    }
    
    // * get the first number
    firstNumber = stack.top();
    // * remove the first number
    stack.pop();

    // * get the second number
    secondNumber = stack.top();
    // * remove the second number
    stack.pop();

    if (sign == '+'){
        // * calculate the result (but we need to change the order of fisrt and second number because when we get the top of stack that is the last number)
        result = secondNumber + firstNumber;
    } else if (sign == '-'){
        // * calculate the result (but we need to change the order of fisrt and second number because when we get the top of stack that is the last number)
        result = secondNumber - firstNumber;
    } else if (sign == '*'){
        // * calculate the result (but we need to change the order of fisrt and second number because when we get the top of stack that is the last number)
        result = secondNumber * firstNumber;
    } else if (sign == '/'){
        // * handle the devide by 0
        if (firstNumber == 0){
            throw std::runtime_error("Error: you can't devide by 0");
        }

        // * calculate the result (but we need to change the order of fisrt and second number because when we get the top of stack that is the last number)
        result = secondNumber / firstNumber;
    }

    // * push the result to stack
    stack.push(result);
}

void rpnParsing(std::string rpn){

    // * Stack that we store to him all numbers
    std::stack<int>stack;
    
    for (size_t i = 0; i < rpn.length(); i++){
        // * Skip white spaces
        while(rpn[i] && rpn[i] <= 32 && rpn[i] > 0){
            i++;
        }

        // * check the string is empty after skip spaces
        if (!rpn[i]){
            break;
        }

        // * Store the numbers and if we found opearator we do the calculation
        if (std::isdigit(rpn[i])){
            // * push it to stack as int
            stack.push(rpn[i] - '0');
        }
        else if (rpn[i] == '+'){
            // * Calculate
            rpnCalculation(stack, '+');
        } else if (rpn[i] == '-'){
            // * Calculate
            rpnCalculation(stack, '-');
        } else if (rpn[i] == '*'){
            // * Calculate
            rpnCalculation(stack, '*');
        } else if (rpn[i] == '/'){
            // * Calculate
            rpnCalculation(stack, '/');
        } else {
            throw std::runtime_error("Error: syntax error");
        }
    }

    // * check if i have more than element in stack
    if (stack.size() > 1){
        throw std::runtime_error("Error: you have more than 1 number in stack");
    }
    
    std::cout << "Result: " << stack.top() << std::endl;
}
