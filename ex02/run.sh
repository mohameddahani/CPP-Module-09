make re &&
make clean &&
clear &&
 ./PmergeMe `shuf -i 1-100000 -n 30 | tr "\n" " "`