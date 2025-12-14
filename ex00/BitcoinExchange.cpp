/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed-dahani <mohamed-dahani@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:56:58 by mdahani           #+#    #+#             */
/*   Updated: 2025/12/14 14:41:34 by mohamed-dah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ! Definitions of functions

void getDataFomDataBase(std::map<std::string, std::string>&map){
    // * Open Data Base file
    std::ifstream dataBase("./data.csv");
    if (!dataBase.is_open()){
        throw std::runtime_error("File of database is not open!");
    }

    // * Store all data in map
    std::string line;

    // * skip the fisrt line
    bool fisrtLine = true;

    // * get day from date that we search
    while (std::getline(dataBase, line)){
        // * skip the fisrt line
        if (fisrtLine){
            fisrtLine = false;
            continue;
        }
        
        // * if line is empty skip it
        if (line.empty()){
            continue;
        }

        // * get Date
        std::string dateOfDataBase = line.substr(0, 10);
        // * get Price
        std::string priceOfDataBase = line.substr(11, line.length());

        map[dateOfDataBase] = priceOfDataBase;
    }

    // * Close the file
    dataBase.close();
}

void printCalculation(std::string &date, std::string &value, std::map<std::string, std::string>&map){
    // * use lower bound to get value that i search, if not found it he will get me the next one
    std::map<std::string, std::string>::iterator it = map.lower_bound(date);

    if (it->first == date){
        std::cout << date << " => " << value << " = " << std::strtod(value.c_str(), NULL) * std::strtod(it->second.c_str(), NULL) << std::endl;
        return;
    }
    
    // * if im not found it and it is not on the end() so i will get the close one
    --it;
    std::cout << date << " => " << value << " = " << std::strtod(value.c_str(), NULL) * std::strtod(it->second.c_str(), NULL) << std::endl; 
}

void parseFile(std::string fileName, std::map<std::string, std::string>&map){
    // * Open the file
    std::ifstream inputFile(fileName.c_str());
    if (!inputFile.is_open()){
        throw std::runtime_error("File of tests is not open!");
    }
    
    // * Read from the file
    std::string line;
    
    // * Skip the first line
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
                    // * check if date befor pipe
                    if (i != 11){
                        pipe++;
                    }

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
            
            // * print data after parsing
            if (!error){
                printCalculation(date, value, map);
            }
        }
    }

    // * Close file
    inputFile.close();
}
