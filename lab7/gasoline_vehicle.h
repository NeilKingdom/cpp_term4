#pragma once

#include <iostream>
#include "Vehicle.h"

template<class T>
class GasolineVehicle: public Vehicle {
private:
    T currentGasoline;
    T maximumGasoline;

public:
    GasolineVehicle(T maxGas, T efficiency)
            : maximumGasoline(maxGas), currentGasoline(maxGas) {
        engineEfficiency = efficiency;
    }

    ~GasolineVehicle() {
        std::cout << "In Gasoline Destructor" << std::endl;
    }

    // Inline functions
    inline T calculateRange() const {
        return ((currentGasoline * 100)/engineEfficiency);
    }

    inline T percentEnergyRemaining() const {
        return ((currentGasoline/maximumGasoline) * 100);
    }

    inline void drive(const T km) {
        if(currentGasoline > (km/100) * engineEfficiency) {
            currentGasoline -= (km/100) * engineEfficiency;
        }
        else {
            currentGasoline = 0;
            std::cout << "Your car is out of gas" << std::endl;
        }
    }
};
