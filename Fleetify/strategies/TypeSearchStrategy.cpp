#include "TypeSearchStrategy.h"

TypeSearchStrategy::TypeSearchStrategy(string type){
    this->type = type;
}
vector<Car*> TypeSearchStrategy::findCars(vector<Car*>& listOfCars){
    vector<Car*> cars;
    for(Car* car: listOfCars){
        if(car->getCarType()==type){
            cars.push_back(car);
        }
    }
    return cars;
}
