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
    label dayLab{*this, "<bold black size=14>Day: 0</>"};
    tabbar<std::string> tabBar{*this};
    ViewGUI viewTabPage{*this};
    RentalGUI rentalTabPage{*this};
    ReturnGUI returnTabPage{*this};

public:
    static std::vector<Customer*> custList;
    static std::vector<RentalLocation*> rentalList;
    static std::vector<Vehicle*> vehicleList;
    static int day;

    Controller();
    ~Controller();

    void start();
};
