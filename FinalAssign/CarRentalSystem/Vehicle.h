#pragma once

#include <string>
#include "Customer.h"

class Vehicle {

private:
    std::string m_brand;
    std::string m_make;
    Customer* m_rentee;
    int m_rentalStartDate, m_rentalEndDate;

public:
    //Constructors/Destructors
    Vehicle(std::string brand, std::string make);
    ~Vehicle();

    //Member Functions
    std::string getVehModel() const;
    void returnVehicle();

    //Getters/Setters
    Customer* getRentee() const;
    std::string getBrand() const;
    std::string getMake() const;
    int getRentalStartDate() const;
    int getRentalEndDate() const;

    void setRentee(Customer* newRentee);
    void setRentalStartDate(int rentalStartDate);
    void setRentalEndDate(int rentalEndDate);
};

