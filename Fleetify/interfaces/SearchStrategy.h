#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include "../common.h"
#include "../models/Car.h"

class SearchStrategy{
public:
    virtual vector<Car*> findCars(vector<Car*>& listOfCars) = 0;
    virtual ~SearchStrategy(){}
};

#endif
