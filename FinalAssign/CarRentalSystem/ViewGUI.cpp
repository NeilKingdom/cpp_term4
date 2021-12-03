#include "ViewGUI.h"

using namespace nana;

ViewGUI::ViewGUI(window rootWin) : panel<false>(rootWin) {

    //Allow formatting for labels
    customersLabel.format(true);
    rentalsLabel.format(true);
    vehiclesLabel.format(true);

    //Layout
    viewPlc->div("<weight=95% main><weight=5% scroll>");
    mainPanel->div("<vert"
                "<weight=5% margin=[50,0,0,50] cLab><<vert gap=10 margin=[0,0,0,100] cGrp><weight=60%>>"
                "<weight=5% margin=[50,0,0,50] rLab><<vert gap=10 margin=[0,0,0,100] rGrp><weight=60%>>"
                "<weight=5% margin=[50,0,0,50] vLab><<vert gap=10 margin=[0,0,0,100] vGrp><weight=60%>>>");

    viewPlc->field("main") << mainPanel;
    viewPlc->field("scroll") << vScrollBar;

    mainPanel->field("cLab") << customersLabel;
    mainPanel->field("rLab") << rentalsLabel;
    mainPanel->field("vLab") << vehiclesLabel;
}

void ViewGUI::addCustomerGroup(Customer& cust) {
    std::string customerHeader = cust.getFullName();
    group* customerGroup = new group(*this, formatStr + customerHeader + "</>", true);

    viewPlc->field("cGrp") << *customerGroup;
}

void ViewGUI::addRentalGroup(RentalLocation& rental) {
    std::string rentalHeader = "Rental Location ";
    group* rentalGroup = new group(*this, formatStr + rentalHeader + "</>", true);

    viewPlc->field("rGrp") << *rentalGroup;
}

void ViewGUI::addVehicleGroup(Vehicle* veh) {
    std::string vehicleHeader = veh.getVehModel();
    group* vehicleGroup = new group(*this, formatStr + vehicleHeader + "</>", true);

    viewPlc->field("vGrp") << *vehicleGroup;
}

void ViewGUI::initViewComponents() {
    vScrollBar->events().value_changed([this] {
        //vScreenPos.y = -static_cast<int>(vScrollBar.value());
        move(-vScrollBar->value());
        API::refresh_window(*this);
    });
}
