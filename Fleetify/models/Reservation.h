#ifndef RESERVATION_H
#define RESERVATION_H

#include "../common.h"
#include "Customer.h"
#include "Car.h"

class Reservation{
    private:
    static int nextResId;
    int resId;
    Customer* customer;
    int startDate, endDate; //for ease in comparing
    Car* reservedCar;
    ReservationStatus status;
    public:
    Reservation(Customer* c, Car* car, int start, int end);
    void updateStartEndDate(int start, int end);
    int calculateTotalAmount();
    int getResId();
    Car* getReservedCar();
    int getCustId();
    int getCarId();
    void setStatus(ReservationStatus status);
    int getStartDate();
    int getEndDate();
    void getDetail();
};

#endif
