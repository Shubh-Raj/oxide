#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "../common.h"
#include "CarManager.h"
#include "../models/Reservation.h"
#include "../models/Customer.h"
#include "../models/Car.h"

class ReservationManager{
    private:
    CarManager* carManager;
    map<int,vector<Reservation*>>reservationsByCar; //{carId,res}
    map<int,Reservation*> reservationsByResId; //{resId,res}
    map<int,vector<Reservation*>> reservationsByCustomer; //{custId,res}
    ReservationManager();
    static ReservationManager* instance;
    public:
    static ReservationManager* getInstance();
    bool isCarAvailable(Car* car, int startDate, int endDate);
    int createReservation(Customer* customer, Car* car, int startDate, int endDate);
    void updateReservation(int resId, int newStartDate, int newEndDate);
    void cancelReservation(int resId);
    void checkOut(int resId);
    void checkIn(int resId);
    Reservation* getReservation(int resId);
};

#endif
