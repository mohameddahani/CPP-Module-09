/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:58 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/09 18:37:01 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ! Definitions of functions

void printCalculation(std::string date, std::string value){
    // * Open Data Base file
    std::ifstream dataBase("./data.csv");
    if (!dataBase.is_open()){
        throw std::runtime_error("File of database is not open!");
    }

    // * Check if date is in database
    std::string line;
    bool dateIsFound = false;
    while (std::getline(dataBase, line)){
        std::string dataBaseDate = line.substr(0, 10);
        if (dataBaseDate == date){
            dateIsFound = true;
            std::string dataBasePrice = line.substr(11, line.length());
            std::cout << date << " => " << value << " = " << std::strtod(value.c_str(), NULL) * std::strtod(dataBasePrice.c_str(), NULL) << std::endl;
        }
    }
    if (!dateIsFound){
        std::cerr << "Error: Date not found => " << date << std::endl;
    }
    
}

void parseFile(std::string fileName, std::multimap<std::string, std::string>&map){
    // * Open the file
    std::ifstream inputFile(fileName.c_str());
    if (!inputFile.is_open()){
        throw std::runtime_error("File of tests is not open!");
    }
    
    // * Read from the file
    std::string line;

    // * i use multimap because can i douplicate the key
    std::multimap<std::string, std::string>::iterator it = map.begin();
    
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
        while (size > 0 && line[size - 1] <= 32 && line[size - 1] > 0){
            size--;
            end++;
        }

        // * remove spaces in front
        if (i != 0){
            line.erase(0, i);
        }



        // * remove spaces in back
        if (end != 0 && !line.empty()){
            line.erase(line.length() - end, line.length());
        }
        
        // * check the first line has (date | value)
        if (firstLine){

            if (line != "date | value"){
                throw std::runtime_error("Header is not valid (date | value)");
            }
            firstLine = false;
            continue;
        }



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
                if (minusSign > 2){
                    std::cerr << "Error: not a positive number => " << line << std::endl;
                }
                else {
                    std::cerr << "Error: bad input => " << line << std::endl;
                }
                continue;
            }
            
            
            std::string date;
            std::string value;
            
            // * change line from read only to read and write
            char str[line.length() + 1];
            std::strcpy(str, line.c_str());
            
            // * split the line
            char *token = strtok(str, "-");

            // * this flag check order of line (Y-M-D | V)
            unsigned int order = 0;

            // * flag of error
            bool error = false;

            // * check if date more than 2022
            bool isMoreThan2022 = false;

            // * split the line
            while (token != NULL){
                char *endOfstrtod;
                // * get year
                if (order == 0){
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || std::strlen(token) != 4 || num < 2009){
                        std::cerr << token << " Error: year is incorrect!" << std::endl;
                        error = true;
                        break ;
                    }
                    // * check if year more than 2022
                    if (num > 2022){
                        isMoreThan2022 = true;
                        date = "2022";
                    } else {
                        date = token;
                    }
                }
                // * get month
                else if (order == 1){
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || std::strlen(token) != 2 || (num > 12 || num < 1)){
                        std::cerr << token << " Error: month is incorrect!" << std::endl;
                        error = true;
                        break ;
                    }

                    // * check if year more than 2022
                    // todo: i need to check if the month more than 3 in 2022
                    date += "-";
                    if (isMoreThan2022){
                        date += "03";                        
                    } else {
                        date += token;
                    }

                }
                // * get day
                else if (order == 2){
                    token = strtok(token, " ");
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || std::strlen(token) != 2 || (num > 31 || num < 1)){
                        std::cerr << token << " Error: day is incorrect!" << std::endl;
                        error = true;
                        break ;
                    }

                    // * check if year more than 2022
                    // todo: i need to check if the day more than 29 in month 3 in 2022
                    date += "-";
                    if (isMoreThan2022){
                        date += "29";                        
                    } else {
                        date += token;
                    }
                }
                // * get value
                else if (order == 3){
                    token = strtok(token, "|");
                    token = strtok(token, " ");
                    double num = strtod(token, &endOfstrtod);
                    if (*endOfstrtod != '\0' || (num > 1000 || num < 0)){
                        if (num > 1000){
                            std::cerr << token << " Error: too large a number." << std::endl;
                        }else {
                            std::cerr << token << " Error: value is incorrect!" << std::endl;
                        }
                        error = true;
                        break ;
                    }

                    value = token;
                }
                
                error = false;

                token = strtok(NULL, "-");
                
                order++;
            }
            
            // * Store data after parsing
            if (!error){
                map.insert(std::make_pair(date, value));
                ++it;
                if (it != map.end()){
                    printCalculation(it->first, it->second);
                }
            }
        }
    }
}
