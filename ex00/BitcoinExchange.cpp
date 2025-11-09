/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:58 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/09 10:57:49 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ! Definitions of functions

void parseFile(std::string fileName, std::map<std::string, std::string>&map){
    // * Open the file
    std::ifstream inputFile(fileName.c_str());
    if (!inputFile.is_open()){
        throw std::runtime_error("File is not open!");
    }
    
    // * Read from the file
    std::string line;
    bool firstLine = true;
    while (std::getline(inputFile, line)){
        // * skip the line if empty
        if (line.empty()){
            continue;
        }
        
        // * Skip white spaces from front of line
        unsigned int i = 0;
        while (line[i] <= 32 && line[i] > 0){
            i++;
        }
        
        // * Skip white spaces from back of line
        unsigned int size = line.length();
        unsigned int end = 0;
        while (line[size - 1] <= 32 && line[size - 1] > 0){
            size--;
            end++;
        }

        // * remove spaces in front
        if (i != 0){
            line.erase(0, i);
        }

        // * remove spaces in back
        if (end != 0){
            line.erase(line.length() - end, line.length());
        }
        
        
        // * check the first line has (date | value)
        if (firstLine){        
            if (line != "date | value"){
                throw std::runtime_error("Header is not valid (date | value)");
            }
        }


        // std::cout << "=====line=====" << std::endl;
        // std::cout << line << std::endl;
        

        // * get Dates and Values
        if (!firstLine){
            // * check format of dates and values is valid
            unsigned int minusSign = 0;
            unsigned int plusSign = 0;
            unsigned int pipe = 0;
            unsigned int space = 0;
            for (size_t i = 0; line[i]; i++){
                if (line[i] == '-'){
                    minusSign++;
                }
                if (line[i] == '|'){
                    pipe++;
                }
                if (line[i] == ' '){
                    space++;
                }
                if (line[i] == '+'){
                    plusSign++;
                }
            }

            if (minusSign != 2 || pipe != 1 || space != 2 || plusSign){
                throw std::runtime_error("The Fomat is not valid");
            }
            
            
            std::string date;
            std::string value;
            
            char str[line.length() + 1];
            // * change line from read only to read and write 
            std::strcpy(str, line.c_str());
            
            char *token = strtok(str, "-");

            unsigned int order = 0;
            while (token != NULL){
                char *endOfstrtod;
                // * get year
                if (order == 0){
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || std::strlen(token) != 4 || num < 2009){
                        throw std::runtime_error("year is incorrect!");
                    }

                    date = token;

                    // std::cout << "year is:" << num << std::endl;
                }
                // * get month
                else if (order == 1){
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || std::strlen(token) != 2 || (num > 12 || num < 1)){
                        throw std::runtime_error("month is incorrect!");
                    }

                    date += "-";
                    date += token;

                    // std::cout << "month is:" << num << std::endl;
                }
                // * get day
                else if (order == 2){
                    token = strtok(token, " ");
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || std::strlen(token) != 2 || (num > 31 || num < 1)){
                        throw std::runtime_error("day is incorrect!");
                    }

                    date += "-";
                    date += token;

                    // std::cout << "day is:" << num << std::endl;
                }
                // * get value
                else if (order == 3){
                    token = strtok(token, "|");
                    token = strtok(token, " ");
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || (num > 1000 || num < 0)){
                        throw std::runtime_error("value is incorrect!");
                    }

                    value = token;

                    // std::cout << "value is:" << num << std::endl;
                }
                

                token = strtok(NULL, "-");

                order++;
            }
            
            // * Store data after parsing
            map[date] = value;
        }
        


        firstLine = false;
    }
}