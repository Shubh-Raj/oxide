#include "CarManager.h"

CarManager::CarManager(){}

CarManager* CarManager::instance=nullptr;

CarManager* CarManager::getInstance(){
    if(instance==nullptr){
        instance = new CarManager();
    }
    return instance;
}
void CarManager::setSearchStrategy(SearchStrategy* strategy){
    searchStrategy = strategy;
}
void CarManager::addCar(Car* car){
    listOfCars.push_back(car);
}
void CarManager::removeCar(Car* car){
    auto it = find(listOfCars.begin(), listOfCars.end(), car);
    if (it != listOfCars.end()) {
        listOfCars.erase(it);
    }
}
void CarManager::getAllCarList(){
    for(Car* car: listOfCars){
        car->getCarDetails();
    }
}
vector<Car*> CarManager::performSearch(){
    return searchStrategy->findCars(listOfCars);
}
