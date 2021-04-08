//
// Created by toliman on 07.04.2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#ifndef INCLUDE_SOLUTION_H
#define INCLUDE_SOLUTION_H

constexpr int defaultCarCapacity = 150;
constexpr int defaultCarMaxOil = 100;
constexpr int defaultCarSpeed = 15;

constexpr char *DaniilProjectPath = const_cast<char *>(
        "/home/toliman/Projects/Algorithms-VRP-Problem/"
);

constexpr char *GrigoryProjectPath = const_cast<char *>(
        "???"
);

enum ObjectType {
    SHOP,
    GAS_STATION,
    BASE,
};

enum InputType {
    INPUT_STDIN,
    INPUT_FILE,
};

class Object {
protected:
    int id;
    int delivery;
public:
    int getDelivery() const;

    void setDelivery(int delivery);

public:
    int getId() const;

    void setId(int id);

protected:
    double posX, posY;
    int type;

public:
    explicit Object(int id, double x, double y, int type);

    double getPosX() const;

    void setPosX(double posX);

    double getPosY() const;

    void setPosY(double posY);

    int getType() const;

    void setType(int type);
};

class Shop : public Object {
private:
    int maxProductCapacity;
    int curProduct;
    int openTime, closeTime;
    int service;

public:
    explicit Shop(int id,
                  double x,
                  double y,
                  int type,
                  int openTime,
                  int closeTime,
                  int maxProductCapacity,
                  int service);

    int getMaxProductCapacity() const;

    void setMaxProductCapacity(int maxProductCapacity);

    int getCurProduct() const;

    void setCurProduct(int curProduct);

    int getOpenTime() const;

    void setOpenTime(int openTime);

    int getCloseTime() const;

    void setCloseTime(int closeTime);

    int getService() const;

    void setService(int service);
};

class Car {
private:
    int maxProductCapacity;
    int curProduct;
    int speed;

public:
    int getMaxProductCapacity() const;

    void setMaxProductCapacity(int maxProductCapacity);

    int getCurProduct() const;

    void setCurProduct(int curProduct);

    int getSpeed() const;

    void setSpeed(int speed);

    int getMaxOil() const;

    void setMaxOil(int maxOil);

    int getCurOil() const;

    void setCurOil(int curOil);

private:
    int maxOil;
    int curOil;

public:
    explicit Car(int maxProductCapacity,
                 int speed = defaultCarSpeed,
                 int maxOil = defaultCarMaxOil);
};

class Solution {
private:
    int n;
    int numberOfCars;
    int currentCost;
    double currentTime;
    std::vector<std::vector<double>> matrix;
    std::vector<Car *> cars;
    std::vector<Shop *> objects;
    Object *base;
    Object *currentVertex;
    std::vector<std::vector<Shop *>> solution;

public:
    static std::vector<std::string> split(const std::string &, char sep);

    void getObjectsInfo();

    explicit Solution(int numberOfCars, int inputType, const std::string &fileName = "");

    void parseInputStdin();

    int parseInputFile(const std::string &fileName) noexcept;

    double dist(Object *first, Object *second);

    bool isReachable(Shop *shop);

    void buildGreedySolution();

    void printCurrentSolution();

    double getCost();

    bool isvalid();

    void resetTime();
};

#endif  // INCLUDE_SOLUTION_H
