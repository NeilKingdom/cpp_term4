#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "ViewGUI.h"
#include "RentalGUI.h"
#include "ReturnGUI.h"

#include "Customer.h"
#include "RentalLocation.h"
#include "Vehicle.h"

using namespace nana;

class RentalGUI : public panel<false> {

private:
    place rentalPlc{*this};
    button bAddCustomer{*this, "Add Customer"};
    button bAddRentalLocation{*this, "Add Rental Location"};
    button bAddVehicle{*this, "Add Vehicle"};
    button bDelCustomer{*this, "Delete Customer"};
    button bDelRentalLocation{*this, "Delete Rental Location"};
    button bDelVehicle{*this, "Delete Vehicle"};
    button bFinalize{*this, "Finalize"};
    combox customersBox{*this, "Customers"};
    combox rentalLocationsBox{*this, "Rental Locations"};
    combox vehiclesBox{*this, "Vehicles"};
    label rentalStartLab{*this, "Rental Period Start: "};
    label rentalEndLab{*this, "Rental Period End: "};
    textbox rentalStartField{*this};
    textbox rentalEndField{*this};

    Customer* lastCustSelected = nullptr;
    RentalLocation* lastRentalSelected = nullptr;
    Vehicle* lastVehicleSelected = nullptr;

public:
    RentalGUI(window rootWin);
    void initRentalComponents(ViewGUI& view, RentalGUI& rent, ReturnGUI& retrn);
};
