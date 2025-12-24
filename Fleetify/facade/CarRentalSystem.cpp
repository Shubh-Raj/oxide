#include "CarRentalSystem.h"

CarRentalSystem::CarRentalSystem(){
    reservationManager = ReservationManager::getInstance();
    carManager = CarManager::getInstance();
    searchFactory = SearchFactory::getInstance();
    paymentFactory = PaymentFactory::getInstance();
};

CarRentalSystem* CarRentalSystem::instance=nullptr;

CarRentalSystem* CarRentalSystem::getInstance(){
    if(instance==nullptr){
        instance = new CarRentalSystem();
    }
    return instance;
}
int CarRentalSystem::makeBooking(Customer* customer,Car* car, int startDate, int endDate){
    return reservationManager->createReservation(customer,car,startDate,endDate);
}
void CarRentalSystem::cancelBooking(int resId){
    reservationManager->cancelReservation(resId);
}
void CarRentalSystem::listAllCars(){
    carManager->getAllCarList();
}
void CarRentalSystem::browseByPrice(int maxPrice) {
    carManager->setSearchStrategy(searchFactory->createPriceStrategy(maxPrice));
    vector<Car*> cars = carManager->performSearch();
    for(Car* car : cars){
        car->getCarDetails();
    }
}
void CarRentalSystem::browseByType(string type){
    carManager->setSearchStrategy(searchFactory->createTypeStrategy(type));
    vector<Car*> cars = carManager->performSearch();
    for(Car* car : cars){
        car->getCarDetails();
    }
}
void CarRentalSystem::browseByDate(int start, int end){
    carManager->setSearchStrategy(searchFactory->createAvailabilityStrategy(start,end));
    vector<Car*> cars = carManager->performSearch();
    for(Car* car : cars){
        car->getCarDetails();
    }
}
void CarRentalSystem::checkOut(int resId){
    reservationManager->checkOut(resId);
}
void CarRentalSystem::checkIn(int resId){
    reservationManager->checkIn(resId);
    //need to process payment
}
void CarRentalSystem::processPayment(int resId, string paymentType, string id){
    Reservation* reservation = reservationManager->getReservation(resId);
    if (!reservation) {
        cout << "Invalid reservation ID.\n";
        return;
    }
    int amount = reservation->calculateTotalAmount();
    PaymentStrategy* p = paymentFactory->getStrategy(paymentType, id);
    if (p) {
        p->processPayment(reservation->calculateTotalAmount());
        delete p; 
    }
}
