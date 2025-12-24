#include <bits/stdc++.h>
using namespace std;

class Car{
    private:
    static int carId;
    string make,model,type, licensePlateNo; 
    int year, rentalPricePerDay;
    public:
    Car(string& make, string& model,string& type, string& licensePlateNo, int year, int rentalPricePerDay){
        this->make = make;
        this->model = model;
        this->type = type;
        this->licensePlateNo = licensePlateNo;
        this->year = year;
        this->rentalPricePerDay = rentalPricePerDay;
        carId=++carId;
    }
    int getRentalPricePerDay(){
        return rentalPricePerDay;
    }
    void getCarDetails(){
        cout << "Make: " << make << endl;
        cout << "Model: " << model << endl;
        cout << "Type: " << type << endl;
        cout << "License Plate No: " << licensePlateNo << endl;
        cout << "Year: " << year << endl;
        cout << "Rental Price Per Day: " << rentalPricePerDay << endl;
    }
    string getCarType(){
        return type;
    }
    int getPrice(){
        return rentalPricePerDay;
    }
};

int Car::carId = 0;

class SearchStrategy{
public:
    virtual vector<Car*> findCars(vector<Car*>& listOfCars) = 0;
    virtual ~SearchStrategy(){}
};

class TypeSearchStrategy : public SearchStrategy{
    private:
    string type;
    public:
    TypeSearchStrategy(string type){
        this->type = type;
    }
    vector<Car*> cars;
    vector<Car*> findCars(vector<Car*>& listOfCars){
        for(Car* car: listOfCars){
            if(car->getCarType()==type){
                cars.push_back(car);
            }
        }
        return cars;
    }
};

class PriceSearchStrategy : public SearchStrategy{
    private:
    int maxPrice;
    public:
    PriceSearchStrategy(int maxPrice){
        this->maxPrice = maxPrice;
    }
    vector<Car*> cars;
    vector<Car*> findCars(vector<Car*>& listOfCars){
        for(Car* car: listOfCars){
            if(car->getPrice()<=maxPrice){
                cars.push_back(car);
            }
        }
        return cars;
    }
};


class CarManager{
    private:
    static CarManager* instance;
    vector<Car*> listOfCars;
    SearchStrategy* searchStrategy;
    CarManager(){}
    public:
    CarManager* getInstance(){
        if(instance==nullptr){
            instance = new CarManager();
        }
        return instance;
    }
    void setSearchStrategy(SearchStrategy* strategy){
        searchStrategy = strategy;
    }
    void addCar(Car* car){
        listOfCars.push_back(car);
    }
    void removeCar(Car* car){
        auto it = find(listOfCars.begin(), listOfCars.end(), car);
        if (it != listOfCars.end()) {
            listOfCars.erase(it);
        }
    }
    void getAllCarList(){
        for(Car* car: listOfCars){
            car->getCarDetails();
        }
    }
    vector<Car*> performSearch(){
        return searchStrategy->findCars(listOfCars);
    }
};

CarManager* CarManager::instance=nullptr;

class Customer{
    private:
    static int customerId;
    string name, phoneNo, licenseNo;
    public:
    Customer(int customerId, string& name, string& phoneNo, string& licenseNo){
        this->customerId = customerId;
        this->name = name;
        this->phoneNo = phoneNo;
        this->licenseNo = licenseNo;
        customerId = ++customerId;
    }
    void getCustomerDetails(){
        cout << "Customer Name: " << name << endl;
        cout << "Phone No: " << phoneNo << endl;
        cout << "License No: " << licenseNo << endl;
    }
};

enum ReservationStatus{
    ACTIVE, CANCELLED, COMPLETED
};

int Customer::customerId = 0;

class Reservation{
    private:
    static int resId;
    Customer* customer;
    int startDate, endDate; //for ease in comparing
    Car* reservedCar;
    ReservationStatus status;
    public:
    Reservation(Customer* c, Car* car, int start, int end) 
        : customer(c), reservedCar(car), startDate(start), endDate(end) {
        this->status = ACTIVE;
    }
    int calculateTotalAmount(){
        int duration = endDate-startDate+1;
        int cost = duration*reservedCar->getRentalPricePerDay();
        return cost;
    }
    void getDetail(){
        cout << "Reservation Details:" << endl;
        customer->getCustomerDetails();
        reservedCar->getCarDetails();
        cout << "Start Date: " << startDate << endl;
        cout << "End Date: " << endDate << endl;
        cout << "Status: ";
        switch(status) {
            case ACTIVE: cout << "ACTIVE"; break;
            case CANCELLED: cout << "CANCELLED"; break;
            case COMPLETED: cout << "COMPLETED"; break;
        }
        cout << endl;
        cout << "Total Amount: " << calculateTotalAmount() << endl;
    }
};