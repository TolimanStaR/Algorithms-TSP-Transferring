//
// Created by toliman on 07.04.2021.
//

#ifndef INCLUDE_SOLUTION_H
#define INCLUDE_SOLUTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

constexpr char *DaniilProjectPath = const_cast<char *>(
        "/home/toliman/Projects/Algorithms-VRP-Problem/"
);

constexpr char *GrigoryProjectPath = const_cast<char *>(
        "???"
);

enum ObjectType {
    SHOP,
    GAS_STATION,
};

class Object {
protected:
    int posX, posY;
    int openTime, closeTime;
    int type;
};

class Shop : public Object {
private:
    int maxProductCapacity;
    int curProduct;
};

class Car {
private:
    int maxProductCapacity;
    int curProduct;
    int speed;
    int maxOil;
    int curOil;
};

class Solution {
private:
    std::vector<Car *> cars;
    std::vector<Object *> objects;
public:
    explicit Solution();

    void parseInputStdin();

    void parseInputFile();
};


#endif  // INCLUDE_SOLUTION_H
