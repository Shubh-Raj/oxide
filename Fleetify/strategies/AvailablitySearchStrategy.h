#ifndef AVAILABLITYSEARCHSTRATEGY_H
#define AVAILABLITYSEARCHSTRATEGY_H

#include "../interfaces/SearchStrategy.h"
class ReservationManager;

class AvailablitySearchStrategy : public SearchStrategy{
    private:
    int startDate, endDate;
    ReservationManager* mgr;
    public:
    AvailablitySearchStrategy(ReservationManager* mgr, int startDate, int endDate);
    vector<Car*> findCars(vector<Car*>& listOfCars);
};

#endif
