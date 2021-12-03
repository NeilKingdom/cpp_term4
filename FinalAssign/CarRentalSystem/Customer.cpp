#include "Customer.h"

//Constructors/Destructor
Customer::Customer(std::string FName, std::string LName, std::string address, int age, bool preferred=false)
: m_FName(FName), m_LName(LName), m_address(address), m_age(age), m_preferred(preferred) {}
Customer::~Customer() {}

//Member Functions
std::string Customer::getFullName() const { return m_FName + " " + m_LName; }
void Customer::makePreferred() { m_preferred = true; }

//Getters/Setters
std::string Customer::getFName() const { return m_FName; }
std::string Customer::getLName() const { return m_LName; }
std::string Customer::getAddress() const { return m_address; }
int Customer::getAge() const { return m_age; }
bool Customer::getPreferred() const { return m_preferred; }
