#ifndef SEARCHFACTORY_H
#define SEARCHFACTORY_H

#include "../common.h"
#include "../interfaces/SearchStrategy.h"
class ReservationManager;

class SearchFactory{
    private:
    ReservationManager* reservationManager;
    SearchFactory();
    static SearchFactory* instance;
    public:
    static SearchFactory* getInstance();
    SearchStrategy* createPriceStrategy(int maxPrice);
    SearchStrategy* createTypeStrategy(string type);
    SearchStrategy* createAvailabilityStrategy(int startDate, int endDate);
};

#endif
