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
    button bFinalize{*this, "Finalize"};
    combox* customersBox = new combox{*this, "Customers"};
    combox* rentalLocationsBox = new combox{*this, "Rental Locations"};
    combox* vehiclesBox = new combox{*this, "Vehicles"};
    label rentalStartLab{*this, "Rental Period Start: "};
    label rentalEndLab{*this, "Rental Period End: "};
    textbox rentalStartField{*this};
    textbox rentalEndField{*this};

    Customer* lastCustSelected = NULL;
    RentalLocation* lastRentalSelected = NULL;
    Vehicle* lastVehicleSelected = NULL;

public:
    RentalGUI(window rootWin);
    //void initRentalComponents(std::vector<Customer*>& custList, std::vector<RentalLocation*>& rentalList, std::vector<Vehicle*>& vehicleList, ViewGUI view, RentalGUI rent);
    void initRentalComponents(std::vector<Customer*>& custList, std::vector<RentalLocation*>& rentalList, std::vector<Vehicle*>& vehicleList);
};
