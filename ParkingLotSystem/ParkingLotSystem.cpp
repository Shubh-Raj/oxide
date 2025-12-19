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

class ParkingFloor
{
private:
    int floorNumber;
    map<string, ParkingSpot *> spots;
    vector<ParkingObserver *> observers;

public:
    ParkingFloor(int floorNum)
    {
        floorNumber = floorNum;
    }
    void addSpot(ParkingSpot *spot)
    {
        spots[spot->getSpotId()] = spot;
    }
    ParkingSpot *findAvailableSpot(Vehicle *vehicle)
    {
        for (auto it : spots)
        {
            if (it.second->canFitVehicle(vehicle))
            {
                return it.second;
            }
        }
        return nullptr; // No spot found
    }
    int getFloorNumber() const
    {
        return floorNumber;
    }
    int getAvailableSpotsCount()
    {
        int count = 0;
        for (auto i : spots)
        {
            if (i.second->isAvailable())
            {
                count++;
            }
        }
        return count;
    }
    // can create a different Iobeservable class
    void registerObserver(ParkingObserver *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(ParkingObserver *observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers()
    {
        int availableSpots = getAvailableSpotsCount();
        for (ParkingObserver *observer : observers)
        {
            observer->update(floorNumber, availableSpots);
        }
    }
};

class ParkingObserver
{
public:
    virtual void update(int floorNumber, int availableSpots) = 0;
    virtual ~ParkingObserver() = default;
};

class EntranceDisplayBoard : public ParkingObserver
{
public:
    void update(int floorNumber, int availableSpots) override
    {
        cout << "DISPLAY BOARD: Floor " << floorNumber << " has " << availableSpots << " spots available." << endl;
    }
};


class ParkingStrategy{
    public:
    virtual ParkingSpot* findSpot(vector<ParkingFloor*>& floors, Vehicle* vehicle) = 0;
    virtual ~ParkingStrategy() = default;
};

class NearestFit : public ParkingStrategy{
public:
    ParkingSpot* findSpot(vector<ParkingFloor*>& floors, Vehicle* vehicle) override
    {
        for (int i = 0; i < floors.size(); i++)
        {
            ParkingSpot* spot = floors[i]->findAvailableSpot(vehicle);
            if (spot != nullptr)
            {
                return spot;
            }
        }
        return nullptr;
    }
};

class FarthestFit : public ParkingStrategy{
    public:
    ParkingSpot* findSpot(vector<ParkingFloor*>& floors, Vehicle* vehicle) override
    {
        for (int i = floors.size() - 1; i >= 0; i--)
        {
            ParkingSpot* spot = floors[i]->findAvailableSpot(vehicle);
            if (spot != nullptr)
            {
                return spot;
            }
        }
        return nullptr;
    }
};