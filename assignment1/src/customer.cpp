#include "Customer.h"

//Constructors/Destructor
Customer::Customer(std::string FName, std::string LName, std::string address, int age, bool preferred)
: m_FName(FName), m_LName(LName), m_address(address), m_age(age), m_preferred(preferred) {}
Customer::~Customer() {
    m_amountOwing = 0.0f;
}

//Member Functions
std::string Customer::getFullName() const { return m_FName + " " + m_LName; }
void Customer::makePreferred() { m_preferred = true; }

//Getters/Setters
std::string Customer::getFName() const { return m_FName; }
std::string Customer::getLName() const { return m_LName; }
std::string Customer::getAddress() const { return m_address; }
int Customer::getAge() const { return m_age; }
bool Customer::isPreferred() const { return m_preferred; }
void Customer::addAmountOwing(float amount) { m_amountOwing += amount; }
float Customer::getAmountOwing() const { return m_amountOwing; }

bool Customer::operator==(const Customer& cust) {

    if(cust.getFullName() == this->getFullName()
       && cust.getAddress() == this->getAddress()
       && cust.getAge() == this->getAge()
       && cust.isPreferred() == this->isPreferred())
        return true;
    else
        return false;
}
