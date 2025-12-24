#include "PriceSearchStrategy.h"

PriceSearchStrategy::PriceSearchStrategy(int maxPrice){
    this->maxPrice = maxPrice;
}
vector<Car*> PriceSearchStrategy::findCars(vector<Car*>& listOfCars){
    vector<Car*> cars;
    for(Car* car: listOfCars){
        if(car->getPrice()<=maxPrice){
            cars.push_back(car);
        }
    }
    return cars;
}
