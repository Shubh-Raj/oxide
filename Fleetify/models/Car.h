#ifndef CAR_H
#define CAR_H

#include "../common.h"

class Car{
    private:
    static int nextCarId;
    int carId;
    string make,model,type, licensePlateNo; 
    int year, rentalPricePerDay;
    public:
    Car(const string& make, const string& model, const string& type, const string& licensePlateNo, int year, int rentalPricePerDay);
    int getRentalPricePerDay();
    int getCarId();
    void getCarDetails();
    string getCarType();
    int getPrice();
};

#endif
