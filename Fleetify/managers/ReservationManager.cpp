#include "ReservationManager.h"

ReservationManager::ReservationManager() {
    carManager = CarManager::getInstance();
}

ReservationManager* ReservationManager::instance=nullptr;

ReservationManager* ReservationManager::getInstance(){
    if(instance==nullptr){
        instance = new ReservationManager();
    }
    return instance;
}
bool ReservationManager::isCarAvailable(Car* car, int startDate, int endDate){
    int carId = car->getCarId();
    for(auto it: reservationsByCar[carId]){
        int existingStart = it->getStartDate();
        int existingEnd = it->getEndDate();
        if (!(endDate < existingStart || startDate > existingEnd)) {
            return false; 
        }
    }
    return true;
}
int ReservationManager::createReservation(Customer* customer, Car* car, int startDate, int endDate){
    if(!isCarAvailable(car,startDate,endDate)){
        cout<<"Car is unavailable!\n";
        return -1;
    }
    Reservation* reservation = new Reservation(customer,car,startDate,endDate);
    int resId = reservation->getResId();
    reservationsByResId[resId]=reservation;
    int carId = car->getCarId();
    reservationsByCar[carId].push_back(reservation);
    int custId = customer->getCustomerId();
    reservationsByCustomer[custId].push_back(reservation);
    cout<<"Reservation made successfully!\n";
    return resId;
}
void ReservationManager::updateReservation(int resId, int newStartDate, int newEndDate){
    Reservation* reservation = reservationsByResId[resId];
    Car* reservedCar  = reservation->getReservedCar();
    if(!isCarAvailable(reservedCar,newStartDate,newEndDate)){
        cout<<"Car is already booked on these dates\n";
        return;
    }
    reservation->updateStartEndDate(newStartDate,newEndDate);
    cout<<"Updated reservation Details\n";
}
void ReservationManager::cancelReservation(int resId){
    Reservation* reservation = reservationsByResId[resId];
    reservation->setStatus(CANCELLED);
    reservationsByResId.erase(resId);
    int custId = reservation->getCustId();
    auto& custReservations = reservationsByCustomer[custId];
    custReservations.erase(
        remove(custReservations.begin(), custReservations.end(), reservation),
        custReservations.end()
    );
    int carId = reservation->getCarId();
    auto& carReservations = reservationsByCar[carId];
    carReservations.erase(
        remove(carReservations.begin(), carReservations.end(), reservation),
        carReservations.end()
    );
    delete reservation;
    cout<<"Reservation cancelled successfully. \n";
}
void ReservationManager::checkOut(int resId){
    Reservation* reservation = reservationsByResId[resId];
    cout<<"Car is out\n";
    reservation->setStatus(ACTIVE);
}
void ReservationManager::checkIn(int resId){
    Reservation* reservation = reservationsByResId[resId];
    cout<<"Car is in\n";
    reservation->setStatus(COMPLETED);
}
Reservation* ReservationManager::getReservation(int resId){
    Reservation* reservation = reservationsByResId[resId];
    return reservation;
}
