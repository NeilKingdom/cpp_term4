#include <iostream>

#include "HybridVehicle.h"

using namespace std;

Vehicle* testVehicle(Vehicle* pVehicle, const char* vehicleName) {
    cout << vehicleName << "'s range is now: " << pVehicle->calculateRange() << endl;
    pVehicle->drive(150); // Drive 150km
    cout << vehicleName << "'s energy left is: " << pVehicle->percentEnergyRemaining() << endl;
    cout << vehicleName << "'s range is now: " << pVehicle->calculateRange() << endl;
    return pVehicle;
}

int main(int argc, char **argv) {

    // 50L of gas, 7.1L/100km
    delete testVehicle(new GasolineVehicle(50,7.1), "Corolla");

    // 42L of gas, 4.3L/100km, 8.8kWh, 22kWh/100km
    delete testVehicle(dynamic_cast<GasolineVehicle*>(new HybridVehicle(42, 4.3, 8.8, 22.0)), "Prius");

    // 75 kWh, 16 kWh/100km
    delete testVehicle(new ElectricVehicle(75, 16), "Tesla 3");

    return 0;
}