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
    bool parkVehicle(Vehicle *vehicle)
    {
        isOccupied = true;
        parkedVehicle = vehicle;
    }
    bool unparkVehicle(Vehicle *vehicle)
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
};
