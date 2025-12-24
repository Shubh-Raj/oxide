#ifndef CARRENTALSYSTEM_H
#define CARRENTALSYSTEM_H

#include "../common.h"
#include "../managers/ReservationManager.h"
#include "../managers/CarManager.h"
#include "../factories/SearchFactory.h"
#include "../factories/PaymentFactory.h"
#include "../models/Customer.h"
#include "../models/Car.h"

class CarRentalSystem{
    private:
    ReservationManager* reservationManager;
    CarManager* carManager;
    SearchFactory* searchFactory;
    PaymentFactory* paymentFactory;
    vector<Customer*> customers;
    CarRentalSystem();
    static CarRentalSystem* instance;
    public:
    static CarRentalSystem* getInstance();
    int makeBooking(Customer* customer,Car* car, int startDate, int endDate);
    void cancelBooking(int resId);
    void listAllCars();
    void browseByPrice(int maxPrice);
    void browseByType(string type);
    void browseByDate(int start, int end);
    void checkOut(int resId);
    void checkIn(int resId);
    void processPayment(int resId, string paymentType, string id);
};

#endif
