/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed-dahani <mohamed-dahani@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:24:34 by mdahani           #+#    #+#             */
/*   Updated: 2025/12/13 21:53:03 by mohamed-dah      ###   ########.fr       */
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

template<typename TPairChain>
// * function of lower bound to get index of insert
struct compFunc {
    bool operator()(const TPairChain &pair, const long value){
        comparisons++;
        return pair.second.back() < value;   // * same as default
    }
};

template<typename TContainer, typename TChain>
// * get jacobsthal numbers
static bool getJacobsthalNumber(TChain &pendChain,
    TContainer &jacobsthalNumberContainer){
    // * clear the old data from jacobsthalNumberContainer befor add the new numbers
    jacobsthalNumberContainer.clear();

    // * get the get Jacobsthal Number
    for (size_t i = 0; i < pendChain.size(); i++){
        // * we add 1 to skip letter b
        double numOfChainWithoutBLetter = std::strtod(pendChain[i].first.c_str() + 1, NULL);

        for (int j = 0; j < 65; j++){
            if (numOfChainWithoutBLetter == jacobNums[j]){
                // * store the Jacobsthal Number in Container
                jacobsthalNumberContainer.push_back(jacobNums[j - 1]); // * store the prev jacobsthal number first
                jacobsthalNumberContainer.push_back(jacobNums[j]); // * store the jacobsthal number second
            }
        }
    }
    
    // * there no jacobsthal numbers
    if (jacobsthalNumberContainer.empty()){
        return false;
    }
    
    return true;
}


template<typename TContainer, typename TChain>

static void divisionIntoPairsAndSorting(TContainer &container, int sizeOfPairs,
    TChain &mainChain,
    TChain &pendChain){
        // 10 9 8 7 6 5 4 3 2 1 0
        // [9 10] [7 8] [5 6] [3 4] [1 2] 0
        // [b1 a1] [a2 a2] [a3 a3] [a4 a4] [a5 a5]
        
        // [(7 8) (9 10)] [(3 4) (5 6)] 1 2 0
        // [b1        a1] [a2       a2]
        // [(3 4 5 6) (7 8 9 10)] 1 2 0
        // [b1                a1]

        //        main                 pend
        // b1 a1 a2 ... a's             b2 b3 b4 ... b's

        for (size_t i = 0; i + sizeOfPairs <= container.size(); i += sizeOfPairs){
            // * index of comparison of largest number in every pair in every level of recusion
            // ! 0-1 | 2-3 ... (index comparison in every recusion)
            // ! 1-3 | 5-7 ... (index comparison in every recusion)
            // ! 3-7 | 11-15 ... (index comparison in every recusion)
            int bs = i + (sizeOfPairs / 2) - 1;
            int as = i + sizeOfPairs - 1;

            // * calculate the start of range and end and start Of second range to swap
            typename TContainer::iterator startOfBlock = container.begin() + i;
            typename TContainer::iterator endOfBlock = container.begin() + i + sizeOfPairs / 2;
            typename TContainer::iterator startOfSecondBlock =  container.begin() + i + sizeOfPairs / 2;

            if (comparison(container[bs], container[as])) {
                std::swap_ranges(startOfBlock, endOfBlock, startOfSecondBlock);
            }
        }
        
        // * condition of call recusion that's mean when we division into pairs and we has more than 1 pair then we need to do recursion
        if (container.size() / sizeOfPairs >= 2){
            // * recall the function
            divisionIntoPairsAndSorting(container, sizeOfPairs * 2, mainChain, pendChain);
        }
    
        // ? LOGIC OF INSERTION

        // * container that store the numbers inside of pair
        TContainer containerOfPair;

        // * store element to main and pend chain
        unsigned int orderOfPairs = 0;
        // * is length numbers of one single pair
        unsigned int lengthOfOnePair = sizeOfPairs / 2;
        for (int i = 0; i + lengthOfOnePair <= container.size(); i += lengthOfOnePair){
            // * clear the container
            containerOfPair.clear();

            // * push all size of pair numbers to container of pair
            for (size_t j = i; j < lengthOfOnePair + i; j++){
                containerOfPair.push_back(container[j]);
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
                mainChain.push_back(std::make_pair(key, containerOfPair));
            } else if (key[0] == 'b'){
                // * push the rest of b's to pend chain
                pendChain.push_back(std::make_pair(key, containerOfPair));
            } else {               
                // * push all a's to main chain
                mainChain.push_back(std::make_pair(key, containerOfPair));
            }
        }

        // ? INSERT THE PEND CHAIN TO MAIN CHAIN
        // * check if pend empty
        if (pendChain.empty()){
            // * Clear the main chain if pend is empty
            mainChain.clear();
            return;
        }
        
        // * get jacobsthal number and insert
        TContainer jacobsthalNumberContainer;
        if (getJacobsthalNumber(pendChain, jacobsthalNumberContainer)){

            // * we still looping until pend chain is empty
            while (!pendChain.empty()){
                if (jacobsthalNumberContainer.size() >= 2){
                    // * get number of element that we need to push it to main chain
                    int numberOfElementThatWePush = jacobsthalNumberContainer[1] - jacobsthalNumberContainer[0];
                    
                    // * create the key of pair from jacobsthal number
                    std::string key = "b";
        
                    std::stringstream ss;
                    ss << jacobsthalNumberContainer[1];
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
                        typename TChain::iterator itLowerBound;

                        // * create object of compFunc sturct
                        compFunc<typename TChain::value_type> cmp;
            
                        // * check range
                        if (endOfRange == -1){
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), largeElemenOfPair, cmp);
                        } else {
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.begin() + endOfRange, largeElemenOfPair, cmp);
                        }
            
                        // * insert pair from pend to main chain
                        mainChain.insert(itLowerBound, pendChain[j]);
                        // * remove him from pend
                        pendChain.erase(pendChain.begin() + j);
                        // * remove jacobsthal numbers (current and prev) that we use
                        if (jacobsthalNumberContainer.size() >= 2){
                            jacobsthalNumberContainer.erase(jacobsthalNumberContainer.begin(), jacobsthalNumberContainer.begin() + 1);
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
                        typename TChain::iterator itLowerBound;

                        // * create object of compFunc sturct
                        compFunc<typename TChain::value_type> cmp;
                        
                        // * check range
                        if (endOfRange == -1){
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), largeElemenOfPair, cmp);
                        } else {
                            itLowerBound = std::lower_bound(mainChain.begin(), mainChain.begin() + endOfRange, largeElemenOfPair, cmp);
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
                    typename TChain::iterator itLowerBound;

                    // * create object of compFunc sturct
                    compFunc<typename TChain::value_type> cmp;
        
                    // * check range
                    if (endOfRange == -1){
                        itLowerBound = std::lower_bound(mainChain.begin(), mainChain.end(), largeElemenOfPair, cmp);
                    } else {
                        itLowerBound = std::lower_bound(mainChain.begin(), mainChain.begin() + endOfRange, largeElemenOfPair, cmp);
                    }

                    // * insert pair from pend to main chain
                    mainChain.insert(itLowerBound, pendChain[count]);
                    // * remove him from pend
                    pendChain.erase(pendChain.begin() + count);
                }
            
            }

        // * get rest element of container that not belong to any pair
        // * create a container to store the rest element
        TContainer theRestOfContainer;
        if (mainChain.size() * lengthOfOnePair < container.size()){
            int theRest = container.size() - mainChain.size() * lengthOfOnePair;
            for (int i = container.size() - 1; theRest > 0; i--){
                theRestOfContainer.insert(theRestOfContainer.begin(), container[i]);
                theRest--;
            }
        }

        // * clear the original container and push to him main chain and the rest
        // * clear the container
        container.clear();

        // * push the element from main chain to container
        for (size_t i = 0; i < mainChain.size(); i++){
            for (size_t j = 0; j < mainChain[i].second.size(); j++){
                container.push_back(mainChain[i].second[j]);
            }
        }

        // * push the rest of number in container if we have it
        if (!theRestOfContainer.empty()){
            for (size_t i = 0; i < theRestOfContainer.size(); i++){
                container.push_back(theRestOfContainer[i]);
            }
            
        }
        
        
        // * clear the main chain and pend
        mainChain.clear();
        pendChain.clear();
}

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


    // ? FORD JOHNSON ALGORITHM (MERGE-INSERTION SORT)

    // * print all element befor sorting
    std::vector<long>::iterator vectorItBeforSort = vector.begin();
    
    std::cout << "Before: ";
    
    for(; vectorItBeforSort != vector.end(); ++vectorItBeforSort){
        std::cout << *vectorItBeforSort << " ";
    }

    std::cout << std::endl;

    // todo: the division into the pairs & sorting
    // ! VECTOR

    // * Main chain vector
    std::vector<std::pair<std::string, std::vector<long> > >vectorMainChain;
    // * Pend chain vector
    std::vector<std::pair<std::string, std::vector<long> > >vectorPendChain;

    // * get time by microseconds befor sorting by vector
    double startTime = getTimeByUs();

    // * Process of vector
    divisionIntoPairsAndSorting(vector, 2, vectorMainChain, vectorPendChain);

    // * get time by microseconds after sorting by vector
    double endTime = getTimeByUs();

    // * print all element after sorting
    std::vector<long>::iterator vectorItAfterSort = vector.begin();
    
    std::cout << "After: ";
    
    for(; vectorItAfterSort != vector.end(); ++vectorItAfterSort){
        std::cout << *vectorItAfterSort << " ";
    }

    std::cout << std::endl;

    // * print time of excution by microseconds
    std::cout << std::fixed << std::setprecision(5)
        << "Time to process a range of "
        << vector.size() << " elements with std::[vector] : "
        << endTime - startTime << "µs" << std::endl;

    // * print the number of Comparisons
    std::cout << "Comparisons: " << comparisons << std::endl;

    // ! DEQUE

    // * Main chain deque
    std::deque<std::pair<std::string, std::deque<long> > >dequeMainChain;
    // * Pend chain deque
    std::deque<std::pair<std::string, std::deque<long> > >dequePendChain;

    // * get time by microseconds befor sorting by deque
    startTime = getTimeByUs();

    // * Process of deque
    divisionIntoPairsAndSorting(deque, 2, dequeMainChain, dequePendChain);

    // * get time by microseconds after sorting by deque
    endTime = getTimeByUs();

    // * print time of excution by microseconds
    std::cout << std::fixed << std::setprecision(5)
        << "Time to process a range of "
        << deque.size() << " elements with std::[deque] : "
        << endTime - startTime << "µs" << std::endl;

    // // * check numbers of vector if sorted
    // if (std::is_sorted(vector.begin(), vector.end())){
    //     std::cout << "Vector is Sorted\n";
    // } else {
    //     std::cout << "Vector is Not sorted\n";
    // }

    // // * check numbers of deque if sorted
    // if (std::is_sorted(deque.begin(), deque.end())){
    //     std::cout << "Deque is Sorted\n";
    // } else {
    //     std::cout << "Deque is Not sorted\n";
    // }
}
