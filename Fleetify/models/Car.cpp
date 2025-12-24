#include "Car.h"

int Car::nextCarId = 0;

Car::Car(const string& make, const string& model, const string& type, const string& licensePlateNo, int year, int rentalPricePerDay){
    this->make = make;
    this->model = model;
    this->type = type;
    this->licensePlateNo = licensePlateNo;
    this->year = year;
    this->rentalPricePerDay = rentalPricePerDay;
    carId=++nextCarId;
}
int Car::getRentalPricePerDay(){
    return rentalPricePerDay;
}
int Car::getCarId(){
    return carId;
}
void Car::getCarDetails(){
    cout << "Make: " << make << endl;
    cout << "Model: " << model << endl;
    cout << "Type: " << type << endl;
    cout << "License Plate No: " << licensePlateNo << endl;
    cout << "Year: " << year << endl;
    cout << "Rental Price Per Day: " << rentalPricePerDay << endl;
}
string Car::getCarType(){
    return type;
}
int Car::getPrice(){
    return rentalPricePerDay;
}
