#pragma once

#include <string>

class Customer {

private:
    std::string m_FName;
    std::string m_LName;
    std::string m_address;
    int m_age;
    bool m_preferred;

public:
    //Constructors/Destructor
    Customer(std::string FName, std::string LName, std::string address, int age, bool preferred);
    ~Customer();

    //Member Functions
    std::string getFullName() const;
    void makePreferred();

    //Getters/Setters
    std::string getFName() const;
    std::string getLName() const;
    std::string getAddress() const;
    int getAge() const;
    bool getPreferred() const;
};

