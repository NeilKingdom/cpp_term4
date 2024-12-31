#pragma once

class Vehicle {

private:
    int numWheels;
    int numDoors;

public:
    // Constructors
    Vehicle(int, int);
    Vehicle(int);
    Vehicle();

    // Copy constructors
    Vehicle(Vehicle&);
    Vehicle(Vehicle*);

    // Destructor
    virtual ~Vehicle();

    // Functions
    void printVehicle() const;
    void setNumWheels(int);
    void setNumDoors(int);
    int getNumWheels() const;
    int getNumDoors() const;

    // Operator Override
    Vehicle& operator=(const Vehicle&);
    bool operator==(const Vehicle&) const;
    bool operator!=(const Vehicle&) const;
    Vehicle& operator++();
    Vehicle& operator++(int);
    Vehicle& operator--();
    Vehicle& operator--(int);
    friend std::ostream& operator<<(std::ostream&, const Vehicle&);
};
