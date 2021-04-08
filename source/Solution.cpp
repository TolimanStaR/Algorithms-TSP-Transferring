//
// Created by toliman on 07.04.2021.
//

#include "../include/Solution.h"

Solution::Solution(int numberOfCars1, int inputType, const std::string &fileName) {
    this->numberOfCars = numberOfCars1;
    this->n = 0;
    this->currentTime = 0;
    this->currentCost = 0;
    this->solution.resize(numberOfCars1);
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
        auto car = new Car(defaultCarCapacity);
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
    int id, demand, ready_time, due_date, service_time;
    double x, y;
    auto splittedString = split(line, ' ');
    id = std::atoi(splittedString[0].c_str());
    x = std::atof(splittedString[1].c_str());
    y = std::atof(splittedString[2].c_str());
    auto baseVertex = new Object(id, x, y, BASE);
    this->currentVertex = baseVertex;
    this->base = baseVertex;
    for (int i = 0; i < graphSize; ++i) {
        std::getline(input, line);
        while (line[0] == '#' || line.length() == 0) {
            std::getline(input, line);
        }
        splittedString = split(line, ' ');
        id = std::atoi(splittedString[0].c_str());
        x = std::atof(splittedString[1].c_str());
        y = std::atof(splittedString[2].c_str());
        demand = std::atoi(splittedString[3].c_str());
        ready_time = std::atoi(splittedString[4].c_str());
        due_date = std::atoi(splittedString[5].c_str());
        service_time = std::atoi(splittedString[6].c_str());
        // todo: parse 4 more shop obj params
        auto newCustomer = new Shop(id, x, y, SHOP, ready_time, due_date, demand, service_time);
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
    std::cout << base->getId() << " " << base->getPosX() << " " << base->getPosY()
              << " (id, x position, y  position)\n\n";
    if (n < 11) {
        for (int i = 0; i < n; ++i) {
            std::cout << objects[i]->getId() << " " << objects[i]->getPosX() << " " << objects[i]->getPosY() << "\n";
        }
    } else {
        for (int i = 0; i < 5; ++i) {
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

bool Solution::isReachable(Shop *shop) {
    if (this->currentTime + this->dist(this->currentVertex, shop) /*+ shop->getService()*/ <= shop->getCloseTime())
        return true;
    return false;
}

void Solution::buildGreedySolution() {
    int carNumber = 0;
    for (auto &car : this->cars) {
        this->resetTime();
        while (car->getCurProduct() > 0) {
            bool isSuccessfulIteration = false;
            Shop *nearest = nullptr;
            double curDist = 1e9;
            for (auto &shop : this->objects) {
                if (shop->getType() == SHOP) {
                    std::cout << shop->getId() << '\n';
                    if (isReachable(static_cast<Shop *>(shop)) &&
                        shop->getMaxProductCapacity() - shop->getCurProduct() <= car->getCurProduct()
                        && shop->getMaxProductCapacity() != shop->getCurProduct()) {
                        if (dist(currentVertex, shop) < curDist) {
                            nearest = shop;
                            curDist = dist(currentVertex, shop);
                        }
                    }
                }
            }
            if (nearest != nullptr) {
                isSuccessfulIteration = true;
                currentTime += dist(currentVertex, nearest);
                currentVertex = nearest;
                currentTime += nearest->getService();
                car->setCurProduct(
                        car->getCurProduct() - (nearest->getMaxProductCapacity() -
                                                nearest->getCurProduct()));
                nearest->setCurProduct(nearest->getMaxProductCapacity());
                this->solution[carNumber].push_back(nearest);
            } else if (car->getCurProduct() > 0) {
                curDist = 1e9;
                for (auto &shop : objects) {
                    if (shop->getType() == SHOP) {
                        if (shop->getMaxProductCapacity() != shop->getCurProduct() && isReachable(shop) &&
                            dist(currentVertex, shop) < curDist) {
                            nearest = shop;
                            curDist = dist(currentVertex, shop);
                        }
                    }
                }
                if (nearest != nullptr) {
                    isSuccessfulIteration = true;
                    currentTime += dist(currentVertex, nearest);
                    currentVertex = nearest;
                    currentTime += nearest->getService();
                    int possibleToAdd = std::min(car->getCurProduct(),
                                                 nearest->getMaxProductCapacity() -
                                                 nearest->getCurProduct());
                    car->setCurProduct(car->getCurProduct() - possibleToAdd);
                    nearest->setCurProduct(nearest->getCurProduct() + possibleToAdd);
                    this->solution[carNumber].push_back(nearest);
                }
            }
            if (!isSuccessfulIteration) break;
        }
        carNumber++;
    }
}

void Solution::resetTime() {
    this->currentTime = 0;
}

void Solution::printCurrentSolution() {
    std::cout << "Current solution is:\n\n";
    for (auto &carSolution:this->solution) {
        if (!carSolution.empty()) {
            for (auto &shop : carSolution) {
                std::cout << shop->getId() << " ";
            }
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}

double Solution::getCost() {
    double pathCost = 0;
    for (auto &route : solution) {
        auto size = route.size();
        if (size > 1) {
            for (int i = 0; i < size - 1; ++i) {
                pathCost += dist(route[i], route[(i + 1) % size]);
            }
            pathCost += dist(base, route[0]);
            pathCost += dist(route[size - 1], base);
        }
    }
    return pathCost;
}

bool Solution::isvalid() {
    std::vector<bool> visited(this->n, false);
    for (auto &route : solution) {
        for (auto &shop : route) {
            visited[shop->getId() - 1] = true;
        }
    }
    auto p = [](bool value) { return value; };
    auto p2 = [](Shop *s) { return s->getMaxProductCapacity() == s->getCurProduct(); };
    if (!(std::all_of(visited.begin(), visited.end(), p)))
        return false;
    if (!std::all_of(objects.begin(), objects.end(), p2))
        return false;
    return true;
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

Object::Object(int
               id1, double
               x1, double
               y1, int
               type1) {
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

Car::Car(int
         maxProductCapacity1, int
         speed1, int
         maxOil1) {
    this->maxProductCapacity = maxProductCapacity1;
    this->speed = speed1;
    this->maxOil = maxOil1;
    this->curOil = 0;
    this->curProduct = maxProductCapacity1;
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

Shop::Shop(int
           id,
           double
           x,
           double
           y,
           int
           type,
           int
           openTime1,
           int
           closeTime1,
           int
           maxProductCapacity1,
           int
           service1)
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
