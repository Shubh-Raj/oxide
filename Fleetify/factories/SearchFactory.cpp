#include "SearchFactory.h"
#include "../managers/ReservationManager.h"
#include "../strategies/PriceSearchStrategy.h"
#include "../strategies/TypeSearchStrategy.h"
#include "../strategies/AvailablitySearchStrategy.h"

SearchFactory::SearchFactory(){
    reservationManager = ReservationManager::getInstance();
}

SearchFactory* SearchFactory::instance=nullptr;

SearchFactory* SearchFactory::getInstance(){
    if(instance==nullptr){
        instance = new SearchFactory();
    }
    return instance;
}
SearchStrategy* SearchFactory::createPriceStrategy(int maxPrice){
    return new PriceSearchStrategy(maxPrice);
}
SearchStrategy* SearchFactory::createTypeStrategy(string type){
    return new TypeSearchStrategy(type);
}
SearchStrategy* SearchFactory::createAvailabilityStrategy(int startDate, int endDate){
    return new AvailablitySearchStrategy(reservationManager, startDate, endDate);
}
