#include "AvailablitySearchStrategy.h"
#include "../managers/ReservationManager.h"

AvailablitySearchStrategy::AvailablitySearchStrategy(ReservationManager* mgr, int startDate, int endDate){
    this->mgr = mgr;
    this->startDate = startDate;
    this->endDate = endDate;
}
vector<Car*> AvailablitySearchStrategy::findCars(vector<Car*>& listOfCars){
    vector<Car*> cars;
    for(Car* car: listOfCars){
        if(mgr->isCarAvailable(car,startDate,endDate)){
            cars.push_back(car);
        }
    }
    return cars;
}
