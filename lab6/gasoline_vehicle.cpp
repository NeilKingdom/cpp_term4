#include <iostream>

#include "GasolineVehicle.h"

using namespace std;

// GasolineVehicle constructor

GasolineVehicle::GasolineVehicle(float maxGas, float efficiency)
: maximumGasoline(maxGas), currentGasoline(maxGas) {
    engineEfficiency = efficiency;
}

// GasolineVehicle destructor

GasolineVehicle::~GasolineVehicle() {
    cout << "In Gasoline Destructor" << endl;
}

// GasolineVehicle virtual function definitions

float GasolineVehicle::calculateRange() const {
    return ((currentGasoline * 100.0f)/engineEfficiency);
}

float GasolineVehicle::percentEnergyRemaining() const {
    return ((currentGasoline/maximumGasoline) * 100.0f);
}

void GasolineVehicle::drive(const float km) {
    if(currentGasoline > (km/100.0f) * engineEfficiency) {
        currentGasoline -= (km/100.0f) * engineEfficiency;
    }
    else {
        currentGasoline = 0;
        cout << "Your car is out of gas" << endl;
    }
}