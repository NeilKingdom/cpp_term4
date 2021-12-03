#pragma once

class Vehicle {

private:
    int numWheels;
    int numDoors;

protected:
    float engineEfficiency;

public:
    // Constructors
    Vehicle(int, int);
    Vehicle(int);
    Vehicle();

    // Copy constructors
    Vehicle(Vehicle&);
    Vehicle(Vehicle*);

    // Destructor
    ~Vehicle();

    // Functions
    void setNumWheels(int);
    void setNumDoors(int);
    int getNumWheels() const;
    int getNumDoors() const;

    // Operator Overloads
    Vehicle& operator=(const Vehicle&);
    bool operator==(const Vehicle&) const;
    bool operator!=(const Vehicle&) const;
    Vehicle& operator++();
    Vehicle& operator++(int);
    Vehicle& operator--();
    Vehicle& operator--(int);
    friend std::ostream& operator<<(std::ostream&, const Vehicle&);
};
