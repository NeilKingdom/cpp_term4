#pragma once

#include "Vehicle.h"

template <class T>
class ElectricVehicle: public Vehicle {
private:
    T currentCharge;
    T maximumCharge;

public:
    ElectricVehicle(T maxCharge, T efficiency)
            : maximumCharge(maxCharge), currentCharge(maxCharge) {
        engineEfficiency = efficiency;
    }

    ~ElectricVehicle() {
        std::cout << "In Electric Destructor" << std::endl;
    }

    // Inline functions
    inline T calculateRange() const {
        return ((currentCharge * 100)/engineEfficiency);
    }

    inline T percentEnergyRemaining() const {
        return ((currentCharge/maximumCharge) * 100);
    }

    inline void drive(const T km) {
        if(currentCharge > (km/100) * engineEfficiency) {
            currentCharge -= (km/100) * engineEfficiency;
        }
        else {
            currentCharge = 0;
            std::cout << "Your car is out of gas" << std::endl;
        }
    }
};