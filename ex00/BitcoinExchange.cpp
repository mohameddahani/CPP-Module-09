/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:58 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/10 15:36:16 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ! Definitions of functions

void printCalculation(std::string date, std::string value, std::ifstream &inputFile){
    // * Open Data Base file
    std::ifstream dataBase("./data.csv");
    if (!dataBase.is_open()){
        inputFile.close();
        throw std::runtime_error("File of database is not open!");
    }

    // * Check if date is in database
    std::string line;
    // * get day from date that we search
    std::string dateWithoutDay = date.substr(0, 8);
    // * get day from data base
    std::string dateWithOnlytDay = date.substr(8, 2);
    
    // * get the prev date from data base
    std::string prevDataBaseDate;
    // * get date from database
    while (std::getline(dataBase, line)){
        // * if line is empty skip it
        if (line.empty()){
            continue;
        }
         
        // * get only year and month from data base
        std::string dataBaseYearAndMonth = line.substr(0, 8);
        // * check if i found year and month
        if (dataBaseYearAndMonth == dateWithoutDay){
            // * get day of year and month from data base
            std::string dataBaseDay = line.substr(8, 2);
            // * check if i found the day
            if (dateWithOnlytDay == dataBaseDay){
                std::string dataBasePrice = line.substr(11, line.length());
                std::cout << date << " => " << value << " = " << std::strtod(value.c_str(), NULL) * std::strtod(dataBasePrice.c_str(), NULL) << std::endl;
                
                // * Close file
                dataBase.close();

                return;
            } else {
                // * check if we are in the close day that we need
                if (std::strtod(dataBaseDay.c_str(), NULL) > std::strtod(dateWithOnlytDay.c_str(), NULL)){
                    break;
                }
                // * if im not found the day then store it in prev date
                prevDataBaseDate = line;
                continue;
            }
        }
    }
    
    // * if im not found date then i will print the prev date
    if (!prevDataBaseDate.empty()){
        std::string dataBasePrice = prevDataBaseDate.substr(11, line.length());
        std::cout << date << " => " << value << " = " << std::strtod(value.c_str(), NULL) * std::strtod(dataBasePrice.c_str(), NULL) << std::endl;
    } else {
        std::cerr << "Error: Date not found => " << date << std::endl;
    }
    
    // * Close file
    dataBase.close();
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
                inputFile.close();
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
            bool is2022orMore = false;

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
                    if (num >= 2022){
                        is2022orMore = true;
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
                    if (is2022orMore && num >= 3) {
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

                    // * check max days in every month
                    std::string getMonth = date.substr(5, 6);
                    if (getMonth == "02" && num > 28){
                        std::cerr << token << " Error: day is incorrect!" << std::endl;
                        error = true;
                        break ;
                    } else if (getMonth == "04" && num > 30){
                        std::cerr << token << " Error: day is incorrect!" << std::endl;
                        error = true;
                        break ;

                    } else if (getMonth == "06" && num > 30){
                        std::cerr << token << " Error: day is incorrect!" << std::endl;
                        error = true;
                        break ;

                    } else if (getMonth == "09" && num > 30){
                        std::cerr << token << " Error: day is incorrect!" << std::endl;
                        error = true;
                        break ;

                    } else if (getMonth == "11" && num > 30){
                        std::cerr << token << " Error: day is incorrect!" << std::endl;
                        error = true;
                        break ;
                    }
                    
                    // * check if year more than 2022
                    date += "-";
                    if (is2022orMore && num >= 29){
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
                    printCalculation(it->first, it->second, inputFile);
                }
            }
        }
    }

    // * Close file
    inputFile.close();
}
