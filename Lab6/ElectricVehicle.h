#pragma once

#include "Vehicle.h"

class ElectricVehicle: public Vehicle {
protected:
    float currentCharge;
    float maximumCharge;

public:
    ElectricVehicle(float, float);
    virtual ~ElectricVehicle();

    virtual float calculateRange() const;
    virtual float percentEnergyRemaining() const;
    virtual void drive(float);
};