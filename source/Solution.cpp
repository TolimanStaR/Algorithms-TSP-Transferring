//
// Created by toliman on 07.04.2021.
//

#include "../include/Solution.h"

Solution::Solution(int numberOfCars1, int inputType, const std::string &fileName) {
    this->numberOfCars = numberOfCars1;
    this->n = 0;
    if (inputType == INPUT_FILE) {
        this->n = this->parseInputFile(fileName);
    } else {
        this->parseInputStdin();
    }
    if (n > 0) {
        this->currentCost = 1e9;
        this->base = this->objects[0];
    } else {
        std::cout << "graph size is 0\n";
    }
    for (int i = 0; i < this->numberOfCars; ++i) {
        auto car = new Car(defautCarCapacity);
        this->cars.push_back(car);
    }
}

int Solution::parseInputFile(const std::string &fileName) noexcept {
    std::basic_fstream<char> input((std::string(DaniilProjectPath)) + "test-cases/" + fileName);
    std::string line;
    std::getline(input, line);
    while (line[0] == '#' || line.length() == 0) {
        std::getline(input, line);
    }
    int graphSize = std::atoi(line.c_str());
    std::getline(input, line);
    while (line[0] == '#' || line.length() == 0) {
        std::getline(input, line);
    }
    std::string Sid, Sx, Sy;
    int id;
    double x, y;
    auto splittedString = split(line, ' ');
    id = std::atoi(splittedString[0].c_str());
    x = std::atof(splittedString[1].c_str());
    y = std::atof(splittedString[2].c_str());
    auto baseVertex = new Object(id, x, y, BASE);
    this->objects.push_back(baseVertex);
    for (int i = 0; i < graphSize; ++i) {
        std::getline(input, line);
        while (line[0] == '#' || line.length() == 0) {
            std::getline(input, line);
        }
        splittedString = split(line, ' ');
        id = std::atoi(splittedString[0].c_str());
        x = std::atof(splittedString[1].c_str());
        y = std::atof(splittedString[2].c_str());
        auto newCustomer = new Object(id, x, y, SHOP);
        this->objects.push_back(newCustomer);
    }
    return graphSize;
}

std::vector<std::string> Solution::split(const std::string &string, char sep) {
    std::vector<std::string> result;
    std::string buffer;
    for (auto &c : string + sep) {
        if (c == sep) {
            result.push_back(buffer);
            buffer = "";
        } else {
            buffer += c;
        }
    }
    return result;
}

void Solution::getObjectsInfo() {
    std::cout.precision(3);
    std::cout << n << " (number of customers)\n\n";
    std::cout << "Base vertex:\n";
    std::cout << objects[0]->getId() << " " << objects[0]->getPosX() << " " << objects[0]->getPosY()
              << " (id, x position, y  position)\n\n";
    if (n < 11) {
        for (int i = 1; i < n; ++i) {
            std::cout << objects[i]->getId() << " " << objects[i]->getPosX() << " " << objects[i]->getPosY() << "\n";
        }
    } else {
        for (int i = 1; i < 6; ++i) {
            std::cout << objects[i]->getId() << " " << objects[i]->getPosX() << " " << objects[i]->getPosY() << "\n";
        }
        std::cout << "... ... ...\n";
        for (int i = n - 5; i < n; ++i) {
            std::cout << objects[i]->getId() << " " << objects[i]->getPosX() << " " << objects[i]->getPosY() << "\n";
        }
    }
}

void Solution::parseInputStdin() {
    // ???
}

double Solution::dist(Object *first, Object *second) {
    double result = sqrt(pow(first->getPosX() - second->getPosX(), 2) + pow(first->getPosY() - second->getPosY(), 2));
    return result;
}

double Object::getPosX() const {
    return posX;
}

void Object::setPosX(double posX1) {
    Object::posX = posX1;
}

double Object::getPosY() const {
    return posY;
}

void Object::setPosY(double posY1) {
    Object::posY = posY1;
}

int Object::getType() const {
    return type;
}

void Object::setType(int type1) {
    this->type = type1;
}

int Object::getId() const {
    return this->id;
}

void Object::setId(int id1) {
    this->id = id1;
}

Object::Object(int id1, double x1, double y1, int type1) {
    setId(id1);
    setPosX(x1);
    setPosY(y1);
    setType(type1);
}

int Object::getDelivery() const {
    return delivery;
}

void Object::setDelivery(int delivery1) {
    Object::delivery = delivery1;
}

Car::Car(int maxProductCapacity1, int speed1, int maxOil1) {
    this->maxProductCapacity = maxProductCapacity1;
    this->speed = speed1;
    this->maxOil = maxOil1;
    this->curOil = 0;
    this->curProduct = 0;
}

int Car::getMaxProductCapacity() const {
    return maxProductCapacity;
}

void Car::setMaxProductCapacity(int maxProductCapacity1) {
    Car::maxProductCapacity = maxProductCapacity1;
}

int Car::getCurProduct() const {
    return curProduct;
}

void Car::setCurProduct(int curProduct1) {
    Car::curProduct = curProduct1;
}

int Car::getSpeed() const {
    return speed;
}

void Car::setSpeed(int speed1) {
    Car::speed = speed1;
}

int Car::getMaxOil() const {
    return maxOil;
}

void Car::setMaxOil(int maxOil1) {
    Car::maxOil = maxOil1;
}

int Car::getCurOil() const {
    return curOil;
}

void Car::setCurOil(int curOil1) {
    Car::curOil = curOil1;
}

Shop::Shop(int id,
           double x,
           double y,
           int type,
           int openTime1,
           int closeTime1,
           int maxProductCapacity1,
           int service1)
        : Object(id,
                 x,
                 y,
                 type) {
    this->openTime = openTime1;
    this->closeTime = closeTime1;
    this->maxProductCapacity = maxProductCapacity1;
    this->service = service1;
}

int Shop::getMaxProductCapacity() const {
    return maxProductCapacity;
}

void Shop::setMaxProductCapacity(int maxProductCapacity1) {
    Shop::maxProductCapacity = maxProductCapacity1;
}

int Shop::getCurProduct() const {
    return curProduct;
}

void Shop::setCurProduct(int curProduct1) {
    Shop::curProduct = curProduct1;
}

int Shop::getOpenTime() const {
    return openTime;
}

void Shop::setOpenTime(int openTime1) {
    Shop::openTime = openTime1;
}

int Shop::getCloseTime() const {
    return closeTime;
}

void Shop::setCloseTime(int closeTime1) {
    Shop::closeTime = closeTime1;
}

int Shop::getService() const {
    return service;
}

void Shop::setService(int service1) {
    Shop::service = service1;
}
