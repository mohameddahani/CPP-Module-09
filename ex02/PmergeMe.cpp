/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:24:34 by mdahani           #+#    #+#             */
/*   Updated: 2025/11/19 20:49:40 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// * all jacobsthal numbers that can we use it in this exercice
long long jacobNums[65] = {0,1,1,3,5,11,21,43,85,171,341,683,1365,2731,5461,10923,21845,43691,87381,
    174763,349525,699051,1398101,2796203,5592405,11184811,22369621,44739243,89478485,178956971,357913941,
    715827883,1431655765,2863311531,5726623061,11453246123,22906492245,45812984491,91625968981,183251937963,
    366503875925,733007751851,1466015503701,2932031007403,5864062014805,11728124029611,23456248059221,46912496118443,
    93824992236885,187649984473771,375299968947541,750599937895083,1501199875790165,3002399751580331,6004799503160661,12009599006321323,
    24019198012642645,48038396025285291,96076792050570581,192153584101141163,384307168202282325,768614336404564651,1537228672809129301,3074457345618258603,
    6148914691236517205};

// * Calculation the number of Comparisons
static unsigned long long comparisons = 0;

// * this func is to compaire the largest numbers in pair
bool comparison(long a, long b){
    comparisons++;
    return a > b;
}

// * function of lower bound to get index of insert
bool compFunc(std::pair<std::string, std::vector<long> > &pair, long value){
    comparisons++;
    return pair.second.back() < value;   // * same as default
}


// ! DON'T FORGET FLAGS IN MAKEFILE

// * get jacobsthal numbers
static bool getJacobsthalNumber(std::vector<std::pair<std::string, std::vector<long> > >&pendChain,
    std::vector<long>&jacobsthalNumberVector){
    // * clear the old data from jacobsthalNumberVector befor add the new numbers
    jacobsthalNumberVector.clear();

    // * get the get Jacobsthal Number
    for (size_t i = 0; i < pendChain.size(); i++){
        // * we add 1 to skip letter b
        double numOfChainWithoutBLetter = std::strtod(pendChain[i].first.c_str() + 1, NULL);

        for (int j = 0; j < 65; j++){
            if (numOfChainWithoutBLetter == jacobNums[j]){
                // * store the Jacobsthal Number in vector
                jacobsthalNumberVector.push_back(jacobNums[j - 1]); // * store the prev jacobsthal number first
                jacobsthalNumberVector.push_back(jacobNums[j]); // * store the jacobsthal number second
            }
        }
    }
    
    // * there no jacobsthal numbers
    if (jacobsthalNumberVector.empty()){
        return false;
    }
    
    return true;
}



static void divisionIntoPairsAndSorting(std::vector<long>&vector, int sizeOfPairs,
    std::vector<std::pair<std::string, std::vector<long> > >&mainChain,
    std::vector<std::pair<std::string, std::vector<long> > >&pendChain){
        // * vector
        // 10 9 8 7 6 5 4 3 2 1 0
        // [9 10] [7 8] [5 6] [3 4] [1 2] 0
        // [a1 b1] [a2 b2] [a3 b3] [a4 b4] [a5 b5] a6

        // [(7 8) (9 10)] [(3 4) (5 6)] 1 2 0
        // [(3 4 5 6) (7 8 9 10)] 1 2 0
        // 3 4 5 6 7 8 9 10           1 2 0
        //        main                 pend

        for (size_t i = 0; i + sizeOfPairs <= vector.size(); i += sizeOfPairs){
            // * index of comparison of largest number in every pair in recusion
            // ! 0-1 | 2-3 ... (index comparison in every recusion)
            // ! 1-3 | 5-7 ... (index comparison in every recusion)
            // ! 3-7 | 11-15 ... (index comparison in every recusion)
            int bs = i + (sizeOfPairs / 2) - 1;
            int as = i + sizeOfPairs - 1;

            // * calculate the start of range and end and start Of second range to swap
            std::vector<long>::iterator startOfBlock = vector.begin() + i;
            std::vector<long>::iterator endOfBlock = vector.begin() + i + sizeOfPairs / 2;
            std::vector<long>::iterator startOfSecondBlock =  vector.begin() + i + sizeOfPairs / 2;

            if (comparison(vector[bs], vector[as])) {
                std::swap_ranges(startOfBlock, endOfBlock, startOfSecondBlock);
            }
        }

         std::cout << "size of pairs befor recursion: " << sizeOfPairs << std::endl;
        
        // * condition of call recusion that's mean when we division into pairs and we has more than 1 pair then we need to do recursion
        if (vector.size() / sizeOfPairs >= 2){
            // * recall the function
            divisionIntoPairsAndSorting(vector, sizeOfPairs * 2, mainChain, pendChain);
        }

        std::cout << "size of pairs after recursion: " << sizeOfPairs << std::endl;
    
        // ? LOGIC OF INSERTION

        // * vector of number of pair
        std::vector<long>vectorOfPair;

        // * store element to main and pend chain
        unsigned int orderOfPairs = 0;
        // * is length numbers of one single pair
        unsigned int lengthOfOnePair = sizeOfPairs / 2;
        for (int i = 0; i + lengthOfOnePair <= vector.size(); i += lengthOfOnePair){
            // * clear vector
            vectorOfPair.clear();

            // * push all size of pair numbers to vector of pair
            for (size_t j = i; j < lengthOfOnePair + i; j++){
                vectorOfPair.push_back(vector[j]);
            }

            // * use string stream to convert fom int to string
            std::stringstream ss;

            // * key of pair
            std::string key;

            if (orderOfPairs % 2 == 0){
                // * odd index → b1, b2, b3...
                ss << orderOfPairs / 2 + 1;
                key = "b";
                key += ss.str();
            } else {
                // * even index → a1, a2, a3...
                ss << orderOfPairs / 2 + 1;
                key = "a";
                key += ss.str();
            }
            orderOfPairs++;

            // * push b1 and all a's
            if (key == "b1"){
                // * push b1 to main chain
                mainChain.push_back(std::make_pair(key, vectorOfPair));
            } else if (key[0] == 'b'){
                // * push the rest of b's to pend chain
                pendChain.push_back(std::make_pair(key, vectorOfPair));
            } else {               
                // * push all a's to main chain
                mainChain.push_back(std::make_pair(key, vectorOfPair));
            }
        }


        // * print the vector of main chain
        std::cout << "main111111111111: " << std::endl;
        for (size_t i = 0; i < mainChain.size(); i++){
            std::cout << mainChain[i].first << " = ";
            for (size_t j = 0; j < mainChain[i].second.size(); j++){
                std::cout << mainChain[i].second[j] << " ";
            }
            std::cout << std::endl;
        }

        // * print the vector of pend chain
        std::cout << "pend111111111111111: " << std::endl;
        for (size_t i = 0; i < pendChain.size(); i++){
            std::cout << pendChain[i].first << " = ";
            for (size_t j = 0; j < pendChain[i].second.size(); j++){
                std::cout << pendChain[i].second[j] << " ";
            }
            std::cout << std::endl;
        }


        // ? INSERT THE PEND CHAIN TO MAIN CHAIN
        // * check if pend empty
        if (pendChain.empty()){
            // * Clear the main chain if pend is empty
            mainChain.clear();
            return;
        }
        
        // * get jacobsthal number and insert
        std::vector<long>jacobsthalNumberVector;
        if (getJacobsthalNumber(pendChain, jacobsthalNumberVector)){

            // * we still looping until pend chain is empty
            while (!pendChain.empty()){
                if (jacobsthalNumberVector.size() >= 2){
                    // * get number of element that we need to push it to main chain
                    int numberOfElementThatWePush = jacobsthalNumberVector[1] - jacobsthalNumberVector[0];
                    
                    // * create the key of pair from jacobsthal number
                    std::string key = "b";
        
                    std::stringstream ss;
                    ss << jacobsthalNumberVector[1];
                    key += ss.str();
        
                    // * get index of pair by jacobsthal number
                    size_t j = 0;
                    for (; j < pendChain.size(); j++){
                        if (pendChain[j].first == key){
                            break;
                        }
                    }
    
                    // * check if we have a pair from as (like if we have b3 we need to check if we have a3 to limit the range of searching)
                    key[0] = 'a';
        
                    // * get end of range that we need to search in it
                    int endOfRange = -1;
                    for (size_t k = 0; k < mainChain.size(); k++){
                        if (mainChain[k].first == key){
                            endOfRange = k;
                            break;
                        }
                        
                    }
        
                    // * clear key
                    key.clear();
    
                    // * now insert pair of pend to main chain
                    for (int count = 0; (count < numberOfElementThatWePush) && !pendChain.empty(); count++){
                        // * get the larger number of pair to do binary search
                        long largeElemenOfPair = pendChain[j].second.back();
    
                        // * push the element of pair to main chain using lower bound
                        std::vector<std::pair<std::string, std::vector<long> > >::iterator itLowerBound;
            
                        // * check range
                        if (endOfRange == -1){
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), largeElemenOfPair, compFunc);
                        } else {
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.begin() + endOfRange, largeElemenOfPair, compFunc);
                        }
            
                        // * insert pair from pend to main chain
                        mainChain.insert(itLowerBound, pendChain[j]);
                        // * remove him from pend
                        pendChain.erase(pendChain.begin() + j);
                        // * remove jacobsthal numbers (current and prev) that we use
                        if (jacobsthalNumberVector.size() >= 2){
                            jacobsthalNumberVector.erase(jacobsthalNumberVector.begin(), jacobsthalNumberVector.begin() + 1);
                        }                        
                        // * decrement the var j to go to next pair because we are push element by revers order
                        if (j > 0){
                            j--;
                        }
                    }
                } else {
                    // * check if we are use all jacobsthal numbers but we still have an pair in pend chain
                    // * then we need to push all rest pairs by revers like from end to start
                    for (int count = pendChain.size() - 1; count >= 0; count--){
                        // * get the larger number of pair to do binary search
                        long largeElemenOfPair = pendChain[count].second.back();
                        
                        // * get key of pair to search the the bound of him
                        std::string key = pendChain[count].first;
                        
                        // * change the first character from b to a (like from b7 to a7)
                        key[0] = 'a';
                        
                        // * get end of range that we need to search in it
                        int endOfRange = -1;
                        for (size_t k = 0; k < mainChain.size(); k++){
                            if (mainChain[k].first == key){
                                endOfRange = k;
                                break;
                            }
                            
                        }
                        
                        // * clear key
                        key.clear();
                        
                        // * push the element of pair to main chain using lower bound
                        std::vector<std::pair<std::string, std::vector<long> > >::iterator itLowerBound;
                        
                        // * check range
                        if (endOfRange == -1){
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), largeElemenOfPair, compFunc);
                        } else {
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.begin() + endOfRange, largeElemenOfPair, compFunc);
                        }
                        
                        // * insert pair from pend to main chain
                        mainChain.insert(itLowerBound, pendChain[count]);
                        // * remove him from pend
                        pendChain.erase(pendChain.begin() + count);
                    }
                    
                }
            }

        } else {
            // * check if there no jacobsthal numbers but we still have an pairs in pend chain
            // * then we need to push all pairs by revers like from end to start
            for (int count = pendChain.size() - 1; count >= 0; count--){
                // * get the larger number of pair to do binary search
                long largeElemenOfPair = pendChain[count].second.back();

                // * get key of pair to search the the bound of him
                std::string key = pendChain[count].first;

                // * change the first character from b to a (like from b7 to a7)
                key[0] = 'a';

                // * get end of range that we need to search in it
                int endOfRange = -1;
                for (size_t k = 0; k < mainChain.size(); k++){
                    if (mainChain[k].first == key){
                        endOfRange = k;
                        break;
                    }
                    
                }
    
                // * clear key
                key.clear();

                // * push the element of pair to main chain using lower bound
                std::vector<std::pair<std::string, std::vector<long> > >::iterator itLowerBound;
    
                // * check range
                if (endOfRange == -1){
                    itLowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), largeElemenOfPair, compFunc);
                } else {
                    itLowerBound = std::lower_bound(mainChain.begin(), mainChain.begin() + endOfRange, largeElemenOfPair, compFunc);
                }

                // * insert pair from pend to main chain
                mainChain.insert(itLowerBound, pendChain[count]);
                // * remove him from pend
                pendChain.erase(pendChain.begin() + count);
            }
            
        }

        // * get rest element of vector that not belong to any pair
        // * create a vector to store the rest element
        std::vector<long> theRestOfVector;
        if (mainChain.size() * lengthOfOnePair < vector.size()){
            int theRest = vector.size() - mainChain.size() * lengthOfOnePair;
            for (int i = vector.size() - 1; theRest > 0; i--){
                theRestOfVector.insert(theRestOfVector.begin(), vector[i]);
                theRest--;
            }
        }

        // * clear the original vector and push to him main chain and the rest
        // * clear the vector
        vector.clear();

        // * push the element to him
        for (size_t i = 0; i < mainChain.size(); i++){
            for (size_t j = 0; j < mainChain[i].second.size(); j++){
                vector.push_back(mainChain[i].second[j]);
            }
        }

        // * add the rest if we have it
        if (!theRestOfVector.empty()){
            for (size_t i = 0; i < theRestOfVector.size(); i++){
                vector.push_back(theRestOfVector[i]);
            }
            
        }
        
        
        // * clear the main chain and pend
        mainChain.clear();
        pendChain.clear();

        std::cout << "================================" << std::endl;
        
        // * print the vector of main chain
        std::cout << "main: " << std::endl;
        for (size_t i = 0; i < mainChain.size(); i++){
            std::cout << mainChain[i].first << " = ";
            for (size_t j = 0; j < mainChain[i].second.size(); j++){
                std::cout << mainChain[i].second[j] << " ";
            }
            std::cout << std::endl;
        }

        // * print the vector of pend chain
        std::cout << "pend: " << std::endl;
        for (size_t i = 0; i < pendChain.size(); i++){
            std::cout << pendChain[i].first << " = ";
            for (size_t j = 0; j < pendChain[i].second.size(); j++){
                std::cout << pendChain[i].second[j] << " ";
            }
            std::cout << std::endl;
        }

        // * print the rest vector 
        std::cout << "rest: " << std::endl;
        for (size_t i = 0; i < theRestOfVector.size(); i++){
            std::cout << theRestOfVector[i] << " ";
        }
        std::cout << std::endl;

        
        // * print the original vector 
        std::cout << "the original vector: " << std::endl;
        for (size_t i = 0; i < vector.size(); i++){
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
}

// static double getTimeByUs(){
//     // ? timespec this is like a `struct timeval' but has nanoseconds not microseconds
//     // ? is used to store time
//     struct timespec time;

//     // ? this func get time by clock id like (CLOCK_REALTIME) this will get time from 01/01/1970
//     // ? and he will store it in sturct timespec
//     clock_gettime(CLOCK_REALTIME, &time);

//     // ? now we convert the seconds to microseconds and add the rest of nanoseconds
//     return (time.tv_sec * 1e6) + (time.tv_nsec / 1e3);
// }

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

    // todo: Step 1: the division into the pairs & sorting
    // * Main chain vector
    std::vector<std::pair<std::string, std::vector<long> > >mainChain;
    // * Pend chain vector
    std::vector<std::pair<std::string, std::vector<long> > >pendChain;

    divisionIntoPairsAndSorting(vector, 2, mainChain, pendChain);

    if (std::is_sorted(vector.begin(), vector.end())){
        std::cout << "Sorted\n";
    } else {
        std::cout << "Not sorted\n";
    }
    
    // // * print the vector of main chain
    // std::cout << "main: " << std::endl;
    // std::vector<long>::iterator itMainChain = mainChain.begin();
    // for (; itMainChain != mainChain.end(); ++itMainChain){
    //     std::cout << *itMainChain << " ";
    // }
    
    // std::cout << std::endl;

    // // * print the vector of pend chain
    // std::cout << "pend: " << std::endl;
    // std::vector<long>::iterator itPendChain = pendChain.begin();
    // for (; itPendChain != pendChain.end(); ++itPendChain){
    //     std::cout << *itPendChain << " ";
    // }
    
    // std::cout << std::endl;

    // * merge the main and pend chains together
    // mergeMainAndPendChains(mainChain, pendChain);


    // // * print all element befor sorting
    // std::vector<long>::iterator vectorItAfterSort = vector.begin();
    
    // std::cout << "After: ";
    
    // for(; vectorItAfterSort != vector.end(); ++vectorItAfterSort){
    //     std::cout << *vectorItAfterSort << " ";
    // }

    // std::cout << std::endl;


    
    // * print the compairs numbers
    std::cout << "Comparisons: " << comparisons << std::endl;

    // // * check if we have a even or odd vector and deque if is odd we need to store the last element in variable and the remove it to be contaier even
    // bool isEven = true;
    // long lastElement = 0;
    // if (vector.size() % 2 != 0){
    //     lastElement = vector.back();
    //     vector.pop_back();
    //     deque.pop_back();

    //     isEven = false;
    // }

    // // ! Sort the Vector
    // // * get time by microseconds befor sorting 
    // double startTime = getTimeByUs();


    // // * Main chain and Second chain of vector
    // std::vector<long>vectorMainChain;
    // std::vector<long>vectorSecondChain;

    // // * Dividing into pairs and Sort the pairs in vector
    // for (size_t i = 0; i < vector.size(); i+= 2){
    //     // * vector
    //     if (vector[i] > vector[i + 1]){
    //         std::swap(vector[i], vector[i + 1]);
    //     }
    // }
    
    // // * Forming two chains in vector
    // for (size_t i = 0; i < vector.size(); i+= 2){
    //     // * vector
    //     vectorMainChain.push_back(vector[i + 1]);
    //     vectorSecondChain.push_back(vector[i]);
    // }

    // // * check if we has a odd vector (push the last element that we remove it in the begin in second chain of vector)
    // if (!isEven){
    //     // * vector
    //     vectorSecondChain.push_back(lastElement);
    // }
    

    // // * Sort the main chain of vector
    // std::sort(vectorMainChain.begin(), vectorMainChain.end());

    // // * Merge chains of vector (Add the small numbers to main chain: every single one we need to add him to correct place)
    // std::vector<long>::iterator itVectorInsert;
    // for (size_t i = 0; i < vectorSecondChain.size(); i++){
    //     // * vector
    //     itVectorInsert = std::lower_bound(vectorMainChain.begin(), vectorMainChain.end(), vectorSecondChain[i]);
    //     vectorMainChain.insert(itVectorInsert, vectorSecondChain[i]);
    // }
    
    // // * get time by microseconds after sorting 
    // double endTime = getTimeByUs();

    // // * print all element after sorting
    // std::vector<long>::iterator vectorItAfterSort = vectorMainChain.begin();
    
    // std::cout << "After: ";
    
    // for(; vectorItAfterSort != vectorMainChain.end(); ++vectorItAfterSort){
    //     std::cout << *vectorItAfterSort << " ";
    // }

    // std::cout << std::endl;

    // // * print time of excution by microseconds
    // std::cout << std::fixed << std::setprecision(5)
    //     << "Time to process a range of "
    //     << (isEven ? vector.size() : vector.size() + 1) << " elements with std::[vector] : "
    //     << endTime - startTime << "µs" << std::endl;


    // // ! Sort the Deque
    // // * get time by microseconds befor sorting 
    // startTime = getTimeByUs();
    
    // // * Main chain and Second chain of deque
    // std::deque<long>dequeMainChain;
    // std::deque<long>dequeSecondChain;

    // // * Dividing into pairs and Sort the pairs in deque
    // for (size_t i = 0; i < deque.size(); i+= 2){
    //     // * deque
    //     if (deque[i] > deque[i + 1]){
    //         std::swap(deque[i], deque[i + 1]);
    //     }
    // }
    
    // // * Forming two chains in deque
    // for (size_t i = 0; i < deque.size(); i+= 2){
    //     // * deque
    //     dequeMainChain.push_back(deque[i + 1]);
    //     dequeSecondChain.push_back(deque[i]);
    // }

    // // * check if we has a odd deque (push the last element that we remove it in the begin in second chain of deque)
    // if (!isEven){
    //     // * deque
    //     dequeSecondChain.push_back(lastElement);
    // }
    

    // // * Sort the main chain of deque
    // std::sort(dequeMainChain.begin(), dequeMainChain.end());

    // // * Merge chains of deque (Add the small numbers to main chain: every single one we need to add him to correct place)
    // std::deque<long>::iterator itDequeInsert;
    // for (size_t i = 0; i < dequeSecondChain.size(); i++){
    //     // * deque
    //     itDequeInsert = std::lower_bound(dequeMainChain.begin(), dequeMainChain.end(), dequeSecondChain[i]);
    //     dequeMainChain.insert(itDequeInsert, dequeSecondChain[i]);
    // }
    
    // // * get time by microseconds after sorting 
    // endTime = getTimeByUs();

    // // * print time of excution by microseconds
    // std::cout << std::fixed << std::setprecision(5)
    //     << "Time to process a range of "
    //     << (isEven ? deque.size() : deque.size() + 1) << " elements with std::[deque] : "
    //     << endTime - startTime << "µs" << std::endl;
}
