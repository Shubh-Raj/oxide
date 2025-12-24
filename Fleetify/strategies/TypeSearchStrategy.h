#ifndef TYPESEARCHSTRATEGY_H
#define TYPESEARCHSTRATEGY_H

#include "../interfaces/SearchStrategy.h"

class TypeSearchStrategy : public SearchStrategy{
    private:
    string type;
    public:
    TypeSearchStrategy(string type);
    vector<Car*> findCars(vector<Car*>& listOfCars);
};

#endif
