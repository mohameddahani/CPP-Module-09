#include <iostream>
#include <vector>
#include <string>
#include <utility> // for std::pair

int main()
{
    std::vector<std::pair<std::string, long> > vec;

    long numbers[] = {6, 15, 8, 16};  
    int n = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < n; i++)
    {
        std::string label;

        if (i % 2 == 0)          // even index → a1, a2, a3...
            label = "a" + std::to_string(i/2 + 1);
        else                     // odd index → b1, b2, b3...
            label = "b" + std::to_string(i/2 + 1);

        vec.push_back(std::make_pair(label, numbers[i]));
    }

    // print the result
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i].first << " = " << vec[i].second << std::endl;
    }

    return 0;
}
