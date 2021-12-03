#pragma once

#include <string>
#include <vector>
#include <initializer_list>
#include "Vehicle.h"

class RentalLocation {

private:
    std::string m_address;
    std::vector<Vehicle> m_vehicles;

public:
    //Constructors/Destructors
    RentalLocation();
    RentalLocation(std::string address);
    RentalLocation(std::string address, std::initializer_list<Vehicle> vehicles);
    ~RentalLocation();

    //Member Functions
    void addVehicle(const Vehicle vehicle);
    void addVehicles(std::initializer_list<Vehicle> vehicles);

    //Getters/Setters
    std::string getAddress() const;
    std::vector<Vehicle> getVehicles() const;
};
