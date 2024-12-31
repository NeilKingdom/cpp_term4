#include <iostream>

#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(int w, int d) {
    //cout << "In constructor with 2 parameters, wheels = " << w << " doors = " << d << endl;
    setNumWheels(w);
    setNumDoors(d);
}

Vehicle::Vehicle(int w) : Vehicle(w, 4) {
    //cout << "In constructor with 1 parameter, wheels = " << w << endl;
}

Vehicle::Vehicle() : Vehicle(4) {
    //cout << "In constructor with 0 parameters" << endl;
}

Vehicle::Vehicle(Vehicle& copy) {
    setNumDoors(copy.getNumDoors());
    setNumWheels(copy.getNumWheels());
}

Vehicle::Vehicle(Vehicle* copy) : Vehicle(*copy) {}

Vehicle::~Vehicle() {
    //cout << "In destructor" << endl;
}

void Vehicle::printVehicle() const {
    cout << "Number of doors: " << this->getNumDoors() << endl;
    cout << "Number of wheels: " << this->getNumWheels() << endl;
}

void Vehicle::setNumWheels(int w) {
    numWheels = w;
}

void Vehicle::setNumDoors(int d) {
    numDoors = d;
}

int Vehicle::getNumWheels() const {
    return numWheels;
}

int Vehicle::getNumDoors() const {
    return numDoors;
}

Vehicle& Vehicle::operator=(const Vehicle& veh) {
    numDoors = veh.getNumDoors();
    numWheels = veh.getNumWheels();
    return *this;
}

bool Vehicle::operator==(const Vehicle& veh) const {
    return ((numDoors == veh.getNumDoors()) && (numWheels == veh.getNumWheels())) ? true : false;
}

bool Vehicle::operator!=(const Vehicle& veh) const {
    return (numDoors == veh.getNumDoors() && (numWheels == veh.getNumWheels())) ? false : true;
}

//Prefix++
Vehicle& Vehicle::operator++() {
    ++numWheels;
    ++numDoors;
    return *this;
}

//Postfix++
Vehicle& Vehicle::operator++(int) {
    Vehicle* copy = new Vehicle(this);
    ++numWheels;
    ++numDoors;
    return *copy;
}

//Prefix--
Vehicle& Vehicle::operator--() {
    --numWheels;
    --numDoors;
    return *this;
}

//Postfix--
Vehicle& Vehicle::operator--(int) {
    Vehicle* copy = new Vehicle(this);
    --numWheels;
    --numDoors;
    return *copy;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& veh) {
    cout << "\n";
    cout << "Number of doors: " << veh.numDoors << endl;
    cout << "Number of wheels: " << veh.numWheels << endl;
    return os;
}

// Never used but need to be defined
float Vehicle::calculateRange() const { return 0.0f; }
float Vehicle::percentEnergyRemaining() const { return 0.0f; }
void Vehicle::drive(const float km) {}

