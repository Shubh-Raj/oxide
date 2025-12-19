#include <bits/stdc++.h>
using namespace std;

enum VehicleSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Vehicle
{
private:
    VehicleSize vehiclesize;
    string licenseNumber;

public:
    Vehicle(VehicleSize vs, string license)
    {
        vehiclesize = vs;
        licenseNumber = license;
    }
    VehicleSize getSize()
    {
        return vehiclesize;
    }
    string getLicenseNumber()
    {
        return licenseNumber;
    }
};

class Truck : public Vehicle
{
public:
    Truck(string license) : Vehicle(LARGE, license) {}
};

class Car : public Vehicle
{
public:
    Car(string license) : Vehicle(MEDIUM, license) {}
};

class Bike : public Vehicle
{
public:
    Bike(string license) : Vehicle(SMALL, license) {}
};

class ParkingSpot
{
private:
    VehicleSize spotSize;
    string spotId;
    bool isOccupied;
    Vehicle *parkedVehicle;

public:
    ParkingSpot(string id, VehicleSize size)
    {
        isOccupied = false;
        spotSize = size;
        spotId = id;
        parkedVehicle = nullptr;
    }
    bool canFitVehicle(Vehicle *vehicle)
    {
        return !isOccupied && vehicle->getSize() <= spotSize;
    }
    void parkVehicle(Vehicle *vehicle)
    {
        isOccupied = true;
        parkedVehicle = vehicle;
    }
    void unparkVehicle()
    {
        isOccupied = false;
        parkedVehicle = nullptr;
    }
    bool isAvailable()
    {
        return !isOccupied;
    }
    string getSpotId() const { return spotId; }
    VehicleSize getSpotSize() const { return spotSize; }
    Vehicle *getParkedVehicle() const { return parkedVehicle; }
};

class ParkingTicket
{
private:
    ParkingSpot *parkingSpot;
    string ticketId;
    // Vehicle* vehicle; omitting this for now, as we can access through the spot
    long entryTime, exitTime;

public:
    ParkingTicket(ParkingSpot *spot, Vehicle *v)
    {
        parkingSpot = spot;
        entryTime = time(0);
        ticketId = spot->getSpotId() + "_" + to_string(entryTime);
    }
    void setExitTimeStamp()
    {
        exitTime = time(0);
    }
    long getEntryTimestamp() const
    {
        return entryTime;
    }
    long getExitTimestamp() const
    {
        return exitTime;
    }
    string getTicketId() const
    {
        return ticketId;
    }
    ParkingSpot *getParkingSpot() const
    {
        return parkingSpot;
    }
};

class ParkingFloor{
    private:
    int floorNumber;
    map<string,ParkingSpot*> spots;
    // vector<ParkingObserver*> observers;
    public:
    ParkingFloor(int floorNum){
        floorNumber = floorNumber;
    }
    void addSpot(ParkingSpot* spot) {
        spots[spot->getSpotId()] = spot;
    }
    ParkingSpot* findAvailableSpot(Vehicle* vehicle) {
        for (auto it : spots) {
            if (it.second->canFitVehicle(vehicle)) {
                return it.second;
            }
        }
        return nullptr; // No spot found
    }
    int getFloorNumber() const {
        return floorNumber;
    }
};
