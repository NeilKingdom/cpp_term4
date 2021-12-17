#include "Vehicle.h"

//Constructors/Destructors
Vehicle::Vehicle(std::string brand, std::string make, float rentalPrice)
: m_brand(brand), m_make(make), m_rentee(nullptr) {
    m_daysRented = 0;
    m_inService = false;
    m_amountOwing = 0.0f;
    m_rentalPrice = rentalPrice;
}
Vehicle::~Vehicle() {}

//Member Functions
std::string Vehicle::getVehModel() const { return m_brand + " " + m_make; }
void Vehicle::returnVehicle() { m_rentee = nullptr; }

//Getters/Setters
Customer* Vehicle::getRentee() const { return m_rentee; }
std::string Vehicle::getBrand() const { return m_brand; }
std::string Vehicle::getMake() const { return m_make; }
bool Vehicle::getIsInService() const { return m_inService; }
int Vehicle::getRentalStartDate() const { return m_rentalStartDate; }
int Vehicle::getRentalEndDate() const { return m_rentalEndDate; }
int Vehicle::getDaysRented() const { return m_daysRented; }
float Vehicle::getRentalPrice() const { return m_rentalPrice; }
float Vehicle::getAmountOwing() const { return m_amountOwing; }

void Vehicle::setIsInService(bool inService) { m_inService = inService; }
void Vehicle::setRentee(Customer* newRentee) { m_rentee = newRentee; }
void Vehicle::setRentalStartDate(int rentalStartDate) { m_rentalStartDate = rentalStartDate; }
void Vehicle::setRentalEndDate(int rentalEndDate) { m_rentalEndDate = rentalEndDate; }
void Vehicle::incDaysRented() { m_daysRented++; }
void Vehicle::setRentalPrice(float rentalPrice) { m_rentalPrice = rentalPrice; }
void Vehicle::setAmountOwing(float amountOwing) { m_amountOwing = amountOwing; }
void Vehicle::setDaysRented(int days) { m_daysRented = days; }
