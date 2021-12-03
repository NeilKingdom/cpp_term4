#include "Vehicle.h"

//Constructors/Destructors
Vehicle::Vehicle(std::string brand, std::string make)
: m_brand(brand), m_make(make) {}
Vehicle::~Vehicle() {}

//Member Functions
std::string Vehicle::getVehModel() const { return m_brand + " " + m_make; }
void Vehicle::returnVehicle() { m_rentee = NULL; }

//Getters/Setters
Customer* Vehicle::getRentee() const { return m_rentee; }
std::string Vehicle::getBrand() const { return m_brand; }
std::string Vehicle::getMake() const { return m_make; }
int Vehicle::getRentalStartDate() const { return m_rentalStartDate; }
int Vehicle::getRentalEndDate() const { return m_rentalEndDate; }

void Vehicle::setRentee(Customer* newRentee) { m_rentee = newRentee; }
void Vehicle::setRentalStartDate(int rentalStartDate) { m_rentalStartDate = rentalStartDate; }
void Vehicle::setRentalEndDate(int rentalEndDate) { m_rentalEndDate = rentalEndDate; }
