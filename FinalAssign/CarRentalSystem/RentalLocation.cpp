#include "RentalLocation.h"

//Constructors/Destructors
RentalLocation::RentalLocation() {}

RentalLocation::RentalLocation(std::string address)
: m_address(address) {}

RentalLocation::RentalLocation(std::string address, std::initializer_list<Vehicle> vehicles)
: m_address(address) {
     for(auto veh : vehicles) {
        m_vehicles.push_back(veh);
    }
}

RentalLocation::~RentalLocation() {}

//Member functions
void RentalLocation::addVehicle(const Vehicle vehicle) {

    m_vehicles.push_back(vehicle);
}

void RentalLocation::addVehicles(std::initializer_list<Vehicle> vehicles) {

    for(auto veh : vehicles) {
        m_vehicles.push_back(veh);
    }
}

//Getters/Setters
std::string RentalLocation::getAddress() const { return m_address; }
std::vector<Vehicle> RentalLocation::getVehicles() const { return m_vehicles; }
