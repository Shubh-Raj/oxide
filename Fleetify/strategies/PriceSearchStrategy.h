#ifndef PRICESEARCHSTRATEGY_H
#define PRICESEARCHSTRATEGY_H

#include "../interfaces/SearchStrategy.h"

class PriceSearchStrategy : public SearchStrategy{
    private:
    int maxPrice;
    public:
    PriceSearchStrategy(int maxPrice);
    vector<Car*> findCars(vector<Car*>& listOfCars);
};

#endif
