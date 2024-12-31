#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include <vector>
#include <string>
#include <iostream>
#include "ReturnGroup.h"
#include "Customer.h"
#include "Vehicle.h"

using namespace nana;

class ReturnGUI : public panel<false> {

private:
    place* returnPlc = new place{*this};
    button bPrev{*this, "prev: <<"};
    button bNext{*this, "next: >>"};
    ReturnGroup* customerProfile = nullptr;

    label* vehicleLab;
    label* returnVehLab;
    button* bReturn;
    label* daysRentedLab;
    label* rentalStartLab;
    label* rentalEndLab;
    label* totalPriceLab;
    label* amountOwingLab;

public:
    combox customersBox{*this, "Customer"};
    std::vector<ReturnGroup*> customerProfiles;
    std::vector<Customer*> pendingCustomers;
    std::vector<Customer*> retrnCustList;
    std::vector<Vehicle*> retrnVehList;
    std::vector<Vehicle*> pendingVehicles;

    ReturnGUI(window rootWin);
    void addCustomerProfile(Customer* prevSelectedCustomer, Vehicle* prevSelectedVehicle);
    void initReturnComponents();
    void refreshTab(ReturnGroup& customerProfile);
    float calcPrice(Customer* prevSelectedCustomer, Vehicle* prevSelectedVehicle);
    void updateLabels(int index, bool calcPrice);
};
