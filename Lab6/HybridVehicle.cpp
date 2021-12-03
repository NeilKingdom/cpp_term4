#include <iostream>

#include "HybridVehicle.h"

using namespace std;

// HybridVehicle constructor

HybridVehicle::HybridVehicle(float maxGas, float gasEfficiency, float maxCharge, float electricEfficiency)
: GasolineVehicle(maxGas, gasEfficiency), ElectricVehicle(maxCharge, electricEfficiency) {}

// HybridVehicle destructor

HybridVehicle::~HybridVehicle() {
    cout << "In Hybrid Destructor" << endl;
}

// ElectricVehicle virtual function definitions

float HybridVehicle::calculateRange() const {
    return (GasolineVehicle::calculateRange() + ElectricVehicle::calculateRange());
}

float HybridVehicle::percentEnergyRemaining() const {
    return ((ElectricVehicle::percentEnergyRemaining()
    + GasolineVehicle::percentEnergyRemaining())
    /2);
}

void HybridVehicle::drive(const float km) {
    ElectricVehicle::drive(km);
    GasolineVehicle::drive(km - ElectricVehicle::calculateRange());
}