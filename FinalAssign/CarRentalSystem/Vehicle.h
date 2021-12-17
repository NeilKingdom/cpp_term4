#pragma once

#include <string>
#include "Customer.h"

//TODO: Add cost of rental for car

class Vehicle {

private:
    bool m_inService;
    std::string m_brand;
    std::string m_make;
    Customer* m_rentee;
    int m_rentalStartDate, m_rentalEndDate, m_daysRented;
    float m_rentalPrice, m_amountOwing;

public:
    //Constructors/Destructors
    Vehicle(std::string brand, std::string make, float rentalPrice);
    ~Vehicle();

    //Member Functions
    std::string getVehModel() const;
    void returnVehicle();

    //Getters/Setters
    Customer* getRentee() const;
    std::string getBrand() const;
    std::string getMake() const;
    bool getIsInService() const;
    int getRentalStartDate() const;
    int getRentalEndDate() const;
    int getDaysRented() const;
    float getRentalPrice() const;
    float getAmountOwing() const;

    void setIsInService(bool inService);
    void setRentee(Customer* newRentee);
    void setRentalStartDate(int rentalStartDate);
    void setRentalEndDate(int rentalEndDate);
    void setDaysRented(int days);
    void incDaysRented();
    void setRentalPrice(float rentalPrice);
    void setAmountOwing(float amountOwing);
};

