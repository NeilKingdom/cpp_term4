#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/scroll.hpp>

#include <string>
#include "Customer.h"
#include "RentalLocation.h"
#include "Vehicle.h"

using namespace nana;

class ViewGUI : public panel<false> {

private:
    place* viewPlc = new place{*this};
    label customersLabel{*this, "<bold blue size=16>Customers:</>"};
    label rentalsLabel{*this, "<bold blue size=16>Rental Locations:</>"};
    label vehiclesLabel{*this, "<bold blue size=16>Vehicles:</>"};

    panel<false>* scrollPanel = new panel<false>(*this, true); //Panel dedicated to scroll bar
    panel<false>* mainPanel = new panel<false>(*this, true); //Panel used for everything other than scroll bar
    scroll<true>* vScrollBar = new scroll<true>(*this, true);
    //point* vScreenPos;

    std::string formatStr = "<bold=true, color=0xff0000, font=\"Consolas\">";

public:
    void addCustomerGroup(Customer& cust);
    void addRentalGroup(RentalLocation& rental);
    void addVehicleGroup(Vehicle& veh);

    ViewGUI(window rootWin);
    void initViewComponents();
};
