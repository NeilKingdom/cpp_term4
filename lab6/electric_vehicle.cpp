#include <iostream>

#include "ElectricVehicle.h"

using namespace std;

// ElectricVehicle constructor

ElectricVehicle::ElectricVehicle(float maxCharge, float efficiency)
: maximumCharge(maxCharge), currentCharge(maxCharge) {
    engineEfficiency = efficiency;
}

// ElectricVehicle destructor

ElectricVehicle::~ElectricVehicle() {
    cout << "In Electric Destructor" << endl;
}

// ElectricVehicle virtual function definitions

float ElectricVehicle::calculateRange() const {
    return ((currentCharge * 100.0f)/engineEfficiency);
}

float ElectricVehicle::percentEnergyRemaining() const {
    return ((currentCharge/maximumCharge) * 100.0f);
}

void ElectricVehicle::drive(const float km) {
    if(currentCharge > (km/100.0f) * engineEfficiency) {
        currentCharge -= (km/100.0f) * engineEfficiency;
    }
    else {
        currentCharge = 0;
        cout << "Your car is out of energy" << endl;
    }
}
