#include <iostream>

#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(int w, int d) {
    cout << "In constructor with 2 parameters, wheels = " << w << " doors = " << d << endl;
    setNumWheels(w);
    setNumDoors(d);
}

Vehicle::Vehicle(int w) : Vehicle(w, 4) {
    cout << "In constructor with 1 parameter, wheels = " << w << endl;
}

Vehicle::Vehicle() : Vehicle(4) {
    cout << "In constructor with 0 parameters" << endl;
}

Vehicle::Vehicle(Vehicle& copy) {
    setNumDoors(copy.getNumDoors());
    setNumWheels(copy.getNumWheels());
}

Vehicle::Vehicle(Vehicle* copy) : Vehicle(*copy) {}

Vehicle::~Vehicle() {
    cout << "In destructor" << endl;
}

void Vehicle::printVehicle() {
    cout << "Number of doors: " << this->getNumDoors() << endl;
    cout << "Number of wheels: " << this->getNumWheels() << endl;
}

void Vehicle::setNumWheels(int w) {
    numWheels = w;
}

void Vehicle::setNumDoors(int d) {
    numDoors = d;
}

int Vehicle::getNumWheels() {
    return numWheels;
}

int Vehicle::getNumDoors() {
    return numDoors;
}