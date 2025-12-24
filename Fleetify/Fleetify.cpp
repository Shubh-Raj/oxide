#include <bits/stdc++.h>
using namespace std;

class Car{
    private:
    static int nextCarId;
    int carId;
    string make,model,type, licensePlateNo; 
    int year, rentalPricePerDay;
    public:
    Car(const string& make, const string& model, const string& type, const string& licensePlateNo, int year, int rentalPricePerDay){
        this->make = make;
        this->model = model;
        this->type = type;
        this->licensePlateNo = licensePlateNo;
        this->year = year;
        this->rentalPricePerDay = rentalPricePerDay;
        carId=++nextCarId;
    }
    int getRentalPricePerDay(){
        return rentalPricePerDay;
    }
    int getCarId(){
        return carId;
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

int Car::nextCarId = 0;

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
    vector<Car*> findCars(vector<Car*>& listOfCars){
        vector<Car*> cars;
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
    vector<Car*> findCars(vector<Car*>& listOfCars){
        vector<Car*> cars;
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
    static CarManager* getInstance(){
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
    static int nextCustomerId;
    int customerId;
    string name, phoneNo, licenseNo;
    public:
    Customer(const string& name, const string& phoneNo, const string& licenseNo){
        this->name = name;
        this->phoneNo = phoneNo;
        this->licenseNo = licenseNo;
        customerId = ++nextCustomerId;
    }
    int getCustomerId(){
        return customerId;
    }
    void getCustomerDetails(){
        cout << "Customer Name: " << name << endl;
        cout << "Phone No: " << phoneNo << endl;
        cout << "License No: " << licenseNo << endl;
    }
};

enum ReservationStatus{
    BOOKED, ACTIVE, CANCELLED, COMPLETED
};

int Customer::nextCustomerId = 0;

class Reservation{
    private:
    static int nextResId;
    int resId;
    Customer* customer;
    int startDate, endDate; //for ease in comparing
    Car* reservedCar;
    ReservationStatus status;
    public:
    Reservation(Customer* c, Car* car, int start, int end) 
        : customer(c), reservedCar(car), startDate(start), endDate(end) {
        this->status = BOOKED;
        resId = ++nextResId;
    }
    void updateStartEndDate(int start, int end){
        this->startDate = start;
        this->endDate = end;
    }
    int calculateTotalAmount(){
        int duration = endDate-startDate+1;
        int cost = duration*reservedCar->getRentalPricePerDay();
        return cost;
    }
    int getResId(){
        return resId;
    }
    Car* getReservedCar(){
        return reservedCar;
    }
    int getCustId(){
        return customer->getCustomerId();
    }
    int getCarId(){
        return reservedCar->getCarId();
    }
    void setStatus(ReservationStatus status){
        this->status = status;
    }
    int getStartDate(){
        return startDate;
    }
    int getEndDate(){
        return endDate;
    }
    void getDetail(){
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
};

int Reservation::nextResId = 0;

class ReservationManager{
    private:
    CarManager* carManager;
    map<int,vector<Reservation*>>reservationsByCar; //{carId,res}
    map<int,Reservation*> reservationsByResId; //{resId,res}
    map<int,vector<Reservation*>> reservationsByCustomer; //{custId,res}
    ReservationManager() {
        carManager = CarManager::getInstance();
    }
    static ReservationManager* instance;
    public:
    static ReservationManager* getInstance(){
        if(instance==nullptr){
            instance = new ReservationManager();
        }
        return instance;
    }
    bool isCarAvailable(Car* car, int startDate, int endDate){
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
    int createReservation(Customer* customer, Car* car, int startDate, int endDate){
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
    void updateReservation(int resId, int newStartDate, int newEndDate){
        Reservation* reservation = reservationsByResId[resId];
        Car* reservedCar  = reservation->getReservedCar();
        if(!isCarAvailable(reservedCar,newStartDate,newEndDate)){
            cout<<"Car is already booked on these dates\n";
            return;
        }
        reservation->updateStartEndDate(newStartDate,newEndDate);
        cout<<"Updated reservation Details\n";
    }
    void cancelReservation(int resId){
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
    void checkOut(int resId){
        Reservation* reservation = reservationsByResId[resId];
        cout<<"Car is out\n";
        reservation->setStatus(ACTIVE);
    }
    void checkIn(int resId){
        Reservation* reservation = reservationsByResId[resId];
        cout<<"Car is in\n";
        reservation->setStatus(COMPLETED);
    }
    Reservation* getReservation(int resId){
        Reservation* reservation = reservationsByResId[resId];
        return reservation;
    }
};

ReservationManager* ReservationManager::instance=nullptr;

class AvailablitySearchStrategy : public SearchStrategy{
    private:
    int startDate, endDate;
    ReservationManager* mgr;
    public:
    AvailablitySearchStrategy(ReservationManager* mgr, int startDate, int endDate){
        this->mgr = mgr;
        this->startDate = startDate;
        this->endDate = endDate;
    }
    vector<Car*> findCars(vector<Car*>& listOfCars){
        vector<Car*> cars;
        for(Car* car: listOfCars){
            if(mgr->isCarAvailable(car,startDate,endDate)){
                cars.push_back(car);
            }
        }
        return cars;
    }
};

class SearchFactory{
    private:
    ReservationManager* reservationManager;
    SearchFactory(){
        reservationManager = ReservationManager::getInstance();
    }
    static SearchFactory* instance;
    public:
    static SearchFactory* getInstance(){
        if(instance==nullptr){
            instance = new SearchFactory();
        }
        return instance;
    }
    SearchStrategy* createPriceStrategy(int maxPrice){
        return new PriceSearchStrategy(maxPrice);
    }
    SearchStrategy* createTypeStrategy(string type){
        return new TypeSearchStrategy(type);
    }
    SearchStrategy* createAvailabilityStrategy(int startDate, int endDate){
        return new AvailablitySearchStrategy(reservationManager, startDate, endDate);
    }
};

SearchFactory* SearchFactory::instance=nullptr;

class PaymentStrategy{
    public:
    virtual bool processPayment(int amount) = 0;
    virtual ~PaymentStrategy(){};
};

class UPIPayment : public PaymentStrategy {
    private:
    string upiId;
    public:
    UPIPayment(string upiId){
        this->upiId = upiId;
    }
    bool processPayment(int amount){
        cout<<"Successfully paid amount "<<amount<<" via UPI.\n";
        return true;
    }
};

class NetBanking : public PaymentStrategy {
    private:
    string id;
    public:
    NetBanking(string id){
        this->id = id;
    }
    bool processPayment(int amount){
        cout<<"Successfully paid amount "<<amount<<" via net banking.\n";
        return true;
    }
};

class PaymentFactory{
    private:
    PaymentFactory(){}
    static PaymentFactory* instance;
    public:
    static PaymentFactory* getInstance(){
        if(instance == nullptr){
            instance = new PaymentFactory();
        }
        return instance;
    }
    PaymentStrategy* createUPIStrategy(string upiId){
        return new UPIPayment(upiId);
    }
    PaymentStrategy* createNetBankingStrategy(string id){
        return new NetBanking(id);
    }
};

PaymentFactory* PaymentFactory::instance=nullptr;

//facade
class CarRentalSystem{
    private:
    ReservationManager* reservationManager;
    CarManager* carManager;
    SearchFactory* searchFactory;
    PaymentFactory* paymentFactory;
    vector<Customer*> customers;
    CarRentalSystem(){
        reservationManager = ReservationManager::getInstance();
        carManager = CarManager::getInstance();
        searchFactory = SearchFactory::getInstance();
        paymentFactory = PaymentFactory::getInstance();
    };
    static CarRentalSystem* instance;
    public:
    static CarRentalSystem* getInstance(){
        if(instance==nullptr){
            instance = new CarRentalSystem();
        }
        return instance;
    }
    int makeBooking(Customer* customer,Car* car, int startDate, int endDate){
        return reservationManager->createReservation(customer,car,startDate,endDate);
    }
    void cancelBooking(int resId){
        reservationManager->cancelReservation(resId);
    }
    void listAllCars(){
        carManager->getAllCarList();
    }
    void browseByPrice(int maxPrice) {
        carManager->setSearchStrategy(searchFactory->createPriceStrategy(maxPrice));
        vector<Car*> cars = carManager->performSearch();
        for(Car* car : cars){
            car->getCarDetails();
        }
    }
    void browseByType(string type){
        carManager->setSearchStrategy(searchFactory->createTypeStrategy(type));
        vector<Car*> cars = carManager->performSearch();
        for(Car* car : cars){
            car->getCarDetails();
        }
    }
    void browseByDate(int start, int end){
        carManager->setSearchStrategy(searchFactory->createAvailabilityStrategy(start,end));
        vector<Car*> cars = carManager->performSearch();
        for(Car* car : cars){
            car->getCarDetails();
        }
    }
    void checkOut(int resId){
        reservationManager->checkOut(resId);
    }
    void checkIn(int resId){
        reservationManager->checkIn(resId);
        //need to process payment
    }
    void processPayment(int resId, string paymentType, string id){
        Reservation* reservation = reservationManager->getReservation(resId);
        if (!reservation) {
            cout << "Invalid reservation ID.\n";
            return;
        }
        int amount = reservation->calculateTotalAmount();
        PaymentStrategy* paymentStrategy = nullptr;
        //can move this part to factory
        if(paymentType=="UPI"){
            paymentStrategy = paymentFactory->createUPIStrategy(id);
            paymentStrategy->processPayment(amount);
        }
        if(paymentType=="NetBanking"){
            paymentStrategy = paymentFactory->createNetBankingStrategy(id);
            paymentStrategy->processPayment(amount);
        }
        delete paymentStrategy;
    }
};

CarRentalSystem* CarRentalSystem::instance=nullptr;

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