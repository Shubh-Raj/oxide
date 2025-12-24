#ifndef CARMANAGER_H
#define CARMANAGER_H

#include "../common.h"
#include "../models/Car.h"
#include "../interfaces/SearchStrategy.h"

class CarManager{
    private:
    static CarManager* instance;
    vector<Car*> listOfCars;
    SearchStrategy* searchStrategy;
    CarManager();
    public:
    static CarManager* getInstance();
    void setSearchStrategy(SearchStrategy* strategy);
    void addCar(Car* car);
    void removeCar(Car* car);
    void getAllCarList();
    vector<Car*> performSearch();
};

#endif
