#include <iostream>

#include "../include/Solution.h"

int main() {
    Solution s(10, INPUT_FILE, "test0015");
    // s.getObjectsInfo();
    s.buildGreedySolution();
    s.printCurrentSolution();
    std::cout << s.getCost() << std::endl;
    std::cout << s.isvalid();
    return 0;
}

// input is -> customers, cars, car capacity
