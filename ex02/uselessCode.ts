    
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

    // // * merge the main and pend chains together
    // mergeMainAndPendChains(mainChain, pendChain);


    // // * print all element befor sorting
    // std::vector<long>::iterator vectorItAfterSort = vector.begin();
    
    // std::cout << "After: ";
    
    // for(; vectorItAfterSort != vector.end(); ++vectorItAfterSort){
    //     std::cout << *vectorItAfterSort << " ";
    // }

    // std::cout << std::endl;

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