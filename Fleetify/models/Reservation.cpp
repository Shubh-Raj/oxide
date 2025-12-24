#include "Reservation.h"

int Reservation::nextResId = 0;

Reservation::Reservation(Customer* c, Car* car, int start, int end) 
    : customer(c), reservedCar(car), startDate(start), endDate(end) {
    this->status = BOOKED;
    resId = ++nextResId;
}
void Reservation::updateStartEndDate(int start, int end){
    this->startDate = start;
    this->endDate = end;
}
int Reservation::calculateTotalAmount(){
    int duration = endDate-startDate+1;
    int cost = duration*reservedCar->getRentalPricePerDay();
    return cost;
}
int Reservation::getResId(){
    return resId;
}
Car* Reservation::getReservedCar(){
    return reservedCar;
}
int Reservation::getCustId(){
    return customer->getCustomerId();
}
int Reservation::getCarId(){
    return reservedCar->getCarId();
}
void Reservation::setStatus(ReservationStatus status){
    this->status = status;
}
int Reservation::getStartDate(){
    return startDate;
}
int Reservation::getEndDate(){
    return endDate;
}
void Reservation::getDetail(){
    cout << "Reservation Details:" << endl;
    customer->getCustomerDetails();
    reservedCar->getCarDetails();
    cout << "Start Date: " << startDate << endl;
    cout << "End Date: " << endDate << endl;
    cout << "Status: ";
    switch(status) {
        case BOOKED: cout << "BOOKED\n"; break;
        case ACTIVE: cout << "ACTIVE\n"; break;
        case CANCELLED: cout << "CANCELLED\n"; break;
        case COMPLETED: cout << "COMPLETED\n"; break;
    }
    cout << endl;
    cout << "Total Amount: " << calculateTotalAmount() << endl;
}
