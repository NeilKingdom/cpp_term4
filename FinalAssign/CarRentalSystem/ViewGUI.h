#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/group.hpp>

#include <vector>
#include <string>
#include "ReturnGUI.h"
#include "Customer.h"
#include "RentalLocation.h"
#include "Vehicle.h"

using namespace nana;

class ViewGUI : public panel<false> {

private:
    place* viewPlc = new place{*this};
    button bAdvanceDay{*this, "Advance day"};
    label customersLabel{*this, "<bold blue size=16>Customers:</>"};
    label rentalsLabel{*this, "<bold blue size=16>Rental Locations:</>"};
    label vehiclesLabel{*this, "<bold blue size=16>Vehicles:</>"};
    std::string formatStr = "<bold=true, color=0xff0000, font=\"Consolas\">";

public:
    ViewGUI(window rootWin);
    ~ViewGUI();

    std::vector<label*> viewCustomers;
    std::vector<label*> viewRentals;
    std::vector<label*> viewVehicles;

    void initViewComponents(ReturnGUI& retrn, label& dayLab, int& day);
    void addCustomerGroup(Customer& cust);
    void addRentalGroup(RentalLocation& rental);
    void addVehicleGroup(Vehicle& veh);
    void refreshTab();
};
