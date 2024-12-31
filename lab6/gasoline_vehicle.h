#pragma once

#include "Vehicle.h"

class GasolineVehicle: public Vehicle {
protected:
    float currentGasoline;
    float maximumGasoline;

public:
    GasolineVehicle(float, float);
    virtual ~GasolineVehicle();

    virtual float calculateRange() const;
    virtual float percentEnergyRemaining() const;
    virtual void drive(float);
};
