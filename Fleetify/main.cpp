#include "facade/CarRentalSystem.h"
#include "models/Car.h"
#include "models/Customer.h"
#include "managers/CarManager.h"


int main(){
    CarRentalSystem* system = CarRentalSystem::getInstance();

    Car* car1 = new Car(string("Toyota"), string("Camry"), string("Sedan"), string("ABC123"), 2020, 1000);
    Car* car2 = new Car(string("Honda"), string("Civic"), string("Sedan"), string("XYZ789"), 2021, 1200);
    Car* car3 = new Car(string("Ford"), string("EcoSport"), string("SUV"), string("SUV456"), 2019, 1500);
    CarManager::getInstance()->addCar(car1);
    CarManager::getInstance()->addCar(car2);
    CarManager::getInstance()->addCar(car3);

    Customer* cust1 = new Customer(string("Shubh"), string("9999999999"), string("LIC123"));
    Customer* cust2 = new Customer(string("Raj"), string("8888888888"), string("LIC456"));

    cout << "All Cars:\n";
    system->listAllCars();

    cout << "\nCars with price <= 1200:\n";
    system->browseByPrice(1200);

    cout << "\nCars of type SUV:\n";
    system->browseByType("SUV");

    cout << "\nCars available from day 1 to 3:\n";
    system->browseByDate(1, 3);

    cout << "\nMaking a booking for Shubh (car1, days 1-3):\n";
    int resId1 = system->makeBooking(cust1, car1, 1, 3);

    cout << "\nTrying to book car1 for Raj (days 2-4):\n";
    int resId2 = system->makeBooking(cust2, car1, 2, 4);

    cout << "\nBooking car3 for Raj (days 2-4):\n";
    int resId3 = system->makeBooking(cust2, car3, 2, 4);

    cout << "\nChecking out car1 for Shubh:\n";
    system->checkOut(resId1);

    cout << "\nChecking in car1 for Shubh and processing payment:\n";
    system->checkIn(resId1);
    system->processPayment(resId1, "UPI", "Shubh@upi");

    cout << "\nCancelling Raj's reservation for car3:\n";
    system->cancelBooking(resId3);

    delete car1;
    delete car2;
    delete car3;
    delete cust1;
    delete cust2;
}
