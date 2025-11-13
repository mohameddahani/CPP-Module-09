/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:24:34 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/13 11:33:59 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static double getTimeByUs(){
    // ? timespec this is like a `struct timeval' but has nanoseconds not microseconds
    // ? is used to store time
    struct timespec time;

    // ? this func get time by clock id like (CLOCK_REALTIME) this will get time from 01/01/1970
    // ? and he will store it in sturct timespec
    clock_gettime(CLOCK_REALTIME, &time);

    // ? now we convert the seconds to microseconds and add the rest of nanoseconds
    return (time.tv_sec * 1e6) + (time.tv_nsec / 1e3);
}

void mergeInsertionSort(int ac, char **av){
    // ? PARSING

    // * Create a Vector and Deque to store all number
    std::vector<long>vector;
    std::deque<long>deque;

    // * use str to long to convert from str to number
    char *end = NULL;
    // * we need to define the base of convert (10 = decimal)
    const int base = 10;

    // * number
    long number = 0;

    int j = 0;
    std::string str = "";
    int size = 0;
    for (int i = 1; i < ac; ++i){
        // * skip white spaces
        // * remove it from front
        for (j = 0; std::isspace(av[i][j]); j++){}
        
        // * convert char * to std::string to do substr()
        str = (av[i]);
        if (j != 0){
            str.erase(0, j);
        }

        // * remove it from back
        size = str.length();
        
        for (j = 0; std::isspace(str[size - 1]); j++){
            size--;
        }

        if (j != 0 && !str.empty()){
            str.erase(str.length() - j, str.length());
        }

        // * check if we have empty string
        if (str.empty()){
            throw std::runtime_error("Error: you have an empty string");
        }
        
        
        // * convert str to number
        number = strtol(str.c_str(), &end, base);
        if (*end != '\0'){
            throw std::runtime_error("Error: Bad input");
        }

        // * check if number are not positive
        if (number < 0){
            throw std::runtime_error("Error: The number is not positive");
        }
        // * check if big than max int
        if (number > INT_MAX){
            throw std::runtime_error("Error: The number bigger than MAX INT");
        }
        
        // * push it to vector and deque after converting
        vector.push_back(number);
        deque.push_back(number);
    }


    // ? ford johnson algorithm (Merge-Insertion Sort)

    // * print all element befor sorting
    std::vector<long>::iterator vectorItBeforSort = vector.begin();
    
    std::cout << "Before: ";
    
    for(; vectorItBeforSort != vector.end(); ++vectorItBeforSort){
        std::cout << *vectorItBeforSort << " ";
    }

    std::cout << std::endl;

    // * check if we have a even or odd vector and deque if is odd we need to store the last element in variable and the remove it to be contaier even
    bool isEven = true;
    long lastElement = 0;
    if (vector.size() % 2 != 0){
        lastElement = vector.back();
        vector.pop_back();
        deque.pop_back();

        isEven = false;
    }

    // ! Sort the Vector
    // * get time by microseconds befor sorting 
    double startTime = getTimeByUs();


    // * Main chain and Second chain of vector
    std::vector<long>vectorMainChain;
    std::vector<long>vectorSecondChain;

    // * Dividing into pairs and Sort the pairs in vector
    for (size_t i = 0; i < vector.size(); i+= 2){
        // * vector
        if (vector[i] > vector[i + 1]){
            std::swap(vector[i], vector[i + 1]);
        }
    }
    
    // * Forming two chains in vector
    for (size_t i = 0; i < vector.size(); i+= 2){
        // * vector
        vectorMainChain.push_back(vector[i + 1]);
        vectorSecondChain.push_back(vector[i]);
    }

    // * check if we has a odd vector (push the last element that we remove it in the begin in second chain of vector)
    if (!isEven){
        // * vector
        vectorSecondChain.push_back(lastElement);
    }
    

    // * Sort the main chain of vector
    std::sort(vectorMainChain.begin(), vectorMainChain.end());

    // * Merge chains of vector (Add the small numbers to main chain: every single one we need to add him to correct place)
    std::vector<long>::iterator itVectorInsert;
    for (size_t i = 0; i < vectorSecondChain.size(); i++){
        // * vector
        itVectorInsert = std::lower_bound(vectorMainChain.begin(), vectorMainChain.end(), vectorSecondChain[i]);
        vectorMainChain.insert(itVectorInsert, vectorSecondChain[i]);
    }
    
    // * get time by microseconds after sorting 
    double endTime = getTimeByUs();

    // * print all element after sorting
    std::vector<long>::iterator vectorItAfterSort = vectorMainChain.begin();
    
    std::cout << "After: ";
    
    for(; vectorItAfterSort != vectorMainChain.end(); ++vectorItAfterSort){
        std::cout << *vectorItAfterSort << " ";
    }

    std::cout << std::endl;

    // * print time of excution by microseconds
    std::cout << std::fixed << std::setprecision(5)
        << "Time to process a range of "
        << (isEven ? vector.size() : vector.size() + 1) << " elements with std::[vector] : "
        << endTime - startTime << "µs" << std::endl;


    // ! Sort the Deque
    // * get time by microseconds befor sorting 
    startTime = getTimeByUs();
    
    // * Main chain and Second chain of deque
    std::deque<long>dequeMainChain;
    std::deque<long>dequeSecondChain;

    // * Dividing into pairs and Sort the pairs in deque
    for (size_t i = 0; i < deque.size(); i+= 2){
        // * deque
        if (deque[i] > deque[i + 1]){
            std::swap(deque[i], deque[i + 1]);
        }
    }
    
    // * Forming two chains in deque
    for (size_t i = 0; i < deque.size(); i+= 2){
        // * deque
        dequeMainChain.push_back(deque[i + 1]);
        dequeSecondChain.push_back(deque[i]);
    }

    // * check if we has a odd deque (push the last element that we remove it in the begin in second chain of deque)
    if (!isEven){
        // * deque
        dequeSecondChain.push_back(lastElement);
    }
    

    // * Sort the main chain of deque
    std::sort(dequeMainChain.begin(), dequeMainChain.end());

    // * Merge chains of deque (Add the small numbers to main chain: every single one we need to add him to correct place)
    std::deque<long>::iterator itDequeInsert;
    for (size_t i = 0; i < dequeSecondChain.size(); i++){
        // * deque
        itDequeInsert = std::lower_bound(dequeMainChain.begin(), dequeMainChain.end(), dequeSecondChain[i]);
        dequeMainChain.insert(itDequeInsert, dequeSecondChain[i]);
    }
    
    // * get time by microseconds after sorting 
    endTime = getTimeByUs();

    // * print time of excution by microseconds
    std::cout << std::fixed << std::setprecision(5)
        << "Time to process a range of "
        << (isEven ? deque.size() : deque.size() + 1) << " elements with std::[deque] : "
        << endTime - startTime << "µs" << std::endl;
}
