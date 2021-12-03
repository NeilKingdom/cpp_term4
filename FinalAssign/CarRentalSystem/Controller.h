#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/tabbar.hpp>

#include <vector>
#include "ViewGUI.h"
#include "RentalGUI.h"
#include "ReturnGUI.h"
#include "Customer.h"
#include "RentalLocation.h"
#include "Vehicle.h"

using namespace nana;

class Controller : public form {

private:
    place plc{*this};
    tabbar<std::string> tabBar{*this};
    panel<false> daysPanel{*this};
    ViewGUI viewTabPage{*this};
    RentalGUI rentalTabPage{*this};
    ReturnGUI returnTabPage{*this};

    //TODO: Could possibly be static + public?
    std::vector<Customer*> custList;
    std::vector<RentalLocation*> rentalList;
    std::vector<Vehicle*> vehicleList;

public:
    Controller();
    ~Controller();

    void start();
};
