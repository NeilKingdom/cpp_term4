#pragma once

#include "ElectricVehicle.h"
#include "GasolineVehicle.h"

class HybridVehicle: public ElectricVehicle, public GasolineVehicle {
public:
    HybridVehicle(float, float, float, float);
    virtual ~HybridVehicle();

    virtual float calculateRange() const;
    virtual float percentEnergyRemaining() const;
    virtual void drive(float);
};