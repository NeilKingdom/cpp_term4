#pragma once

class Vehicle {

private:
    int numWheels;
    int numDoors;

public:
    // Constructors
    Vehicle(int, int);
    Vehicle(int);
    Vehicle();

    // Copy constructors
    Vehicle(Vehicle&);
    Vehicle(Vehicle*);

    // Destructor
    ~Vehicle();

    // Functions
    void printVehicle();
    void setNumWheels(int);
    void setNumDoors(int);
    int getNumWheels();
    int getNumDoors();
};
