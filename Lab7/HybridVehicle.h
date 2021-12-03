#pragma once

#include "ElectricVehicle.h"
#include "GasolineVehicle.h"

template<class T>
class HybridVehicle: public ElectricVehicle<T>, public GasolineVehicle<T> {
public:

    HybridVehicle(T maxGas, T gasEfficiency, T maxCharge, T electricEfficiency)
            : GasolineVehicle<T>(maxGas, gasEfficiency), ElectricVehicle<T>(maxCharge, electricEfficiency) {}

    ~HybridVehicle() {
        std::cout << "In Hybrid Destructor" << std::endl;
    }

    // Inline Functions
    inline T calculateRange() const {
        return (GasolineVehicle<T>::calculateRange() + ElectricVehicle<T>::calculateRange());
    }

    inline T percentEnergyRemaining() const {
        return ((ElectricVehicle<T>::percentEnergyRemaining()
                 + GasolineVehicle<T>::percentEnergyRemaining())
                /2);
    }

    inline void drive(const T km) {
        ElectricVehicle<T>::drive(km);
        GasolineVehicle<T>::drive(km - ElectricVehicle<T>::calculateRange());
    }
};