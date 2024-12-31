#include "ViewGUI.h"
#include "Controller.h"

using namespace nana;

ViewGUI::ViewGUI(window rootWin) : panel<false>(rootWin) {

    //Allow formatting for labels
    customersLabel.format(true);
    rentalsLabel.format(true);
    vehiclesLabel.format(true);

    //Layout
    viewPlc->div("<vert <weight=10% margin=[50,0,0,50] <weight=30% cLab><weight=30% rLab><weight=30% vLab><weight=10% margin=[50,50,0,0] advnc>>"
                  "<weight=90% margin=[50,0,0,50] <vert gap=5 arrange=[100,repeated] cust><vert gap=5 arrange=[30,repeated] rental><vert gap=5 arrange=[30,repeated] veh>>>");

    viewPlc->field("cLab") << customersLabel;
    viewPlc->field("advnc") << bAdvanceDay;
    viewPlc->field("rLab") << rentalsLabel;
    viewPlc->field("vLab") << vehiclesLabel;
}

ViewGUI::~ViewGUI() {}

void ViewGUI::initViewComponents(ReturnGUI& retrn, label& dayLab, int& day) {

    bAdvanceDay.events().click([this, &retrn, &dayLab, &day] {
        //Advance day
        dayLab.caption("<bold black size=14>Day: " + std::to_string(++day) + "</>");

        /**** Do for cars being rented *****/
        //1) Increment days rented for all cars being rented
        for(auto& veh : retrn.retrnVehList) {
            if(veh->getRentee()) {
                veh->incDaysRented();
            }
        }

        /**** Do for all cars *****/
        //1) Check for cars that are being serviced
        //2) Update labels indicating if car is overdue
        //3) If label is overdue but rental has since been returned, remove overdue label.
        for(int i = 0; i < Controller::vehicleList.size(); i++) {
            if(Controller::vehicleList.at(i)->getIsInService()) {
                Controller::vehicleList.at(i)->setIsInService(false);
            }
            if(Controller::vehicleList.at(i)->getDaysRented() > (Controller::vehicleList.at(i)->getRentalEndDate() - Controller::vehicleList.at(i)->getRentalStartDate())) {
                viewVehicles.at(i)->caption("* " + Controller::vehicleList.at(i)->getVehModel() + "<red> (!OVERDUE)</>");
            }
            if(Controller::vehicleList.at(i)->getDaysRented() == 0) //Should always be 0 when not being rented
                viewVehicles.at(i)->caption("* " + Controller::vehicleList.at(i)->getVehModel());
        }

        //Add pending rentees to return tab
        auto pendingVehicles = retrn.pendingVehicles.begin();
        auto pendingCustomers = retrn.pendingCustomers.begin();
        for(int i = 0; i < retrn.pendingVehicles.size(); i++, pendingVehicles++, pendingCustomers++) {
            if(retrn.pendingVehicles.at(i)->getRentalStartDate() == Controller::day) {
                retrn.customersBox.push_back(retrn.pendingCustomers.at(i)->getFullName());
                retrn.addCustomerProfile(retrn.pendingCustomers.at(i), retrn.pendingVehicles.at(i));
                retrn.pendingCustomers.erase(pendingCustomers);
                retrn.pendingVehicles.erase(pendingVehicles);
            }
        }

        //Calculate rental price after day's been incremented
        if(retrn.retrnCustList.size() > 0 && retrn.retrnVehList.size() > 0) {
            retrn.updateLabels(retrn.customersBox.option(), true);
        }

        refreshTab();
    });
}

void ViewGUI::refreshTab() {

    //Layout
    viewPlc = new place{*this};
    viewPlc->div("<vert <weight=10% margin=[50,0,0,50] <weight=30% cLab><weight=30% rLab><weight=30% vLab><weight=10% margin=[50,50,0,0] advnc>>"
                  "<weight=90% margin=[50,0,0,50] <vert gap=5 arrange=[100,repeated] cust><vert gap=5 arrange=[30,repeated] rental><vert gap=5 arrange=[30,repeated] veh>>>");

    viewPlc->field("cLab") << customersLabel;
    viewPlc->field("advnc") << bAdvanceDay;
    viewPlc->field("rLab") << rentalsLabel;
    viewPlc->field("vLab") << vehiclesLabel;

    for(auto& cust : viewCustomers)
        viewPlc->field("cust") << *cust;
    for(auto& rental : viewRentals)
        viewPlc->field("rental") << *rental;
    for(auto& veh : viewVehicles)
        viewPlc->field("veh") << *veh;

    viewPlc->collocate();
}

void ViewGUI::addCustomerGroup(Customer& cust) {
    label* custLab = new label{*this, "<green>* " + cust.getFullName() + "</>\n\tage: " + std::to_string(cust.getAge()) + "\n\taddress: " + cust.getAddress() + "\n\tpreferred? " + std::string(cust.isPreferred() ? " yes" : " no")};
    custLab->format(true);
    viewCustomers.push_back(custLab);
    viewPlc->field("cust") << *custLab;
}

void ViewGUI::addRentalGroup(RentalLocation& rental) {
    label* rentalLab = new label{*this, "* " + rental.getAddress()};
    rentalLab->format(true);
    viewRentals.push_back(rentalLab);
    viewPlc->field("rental") << *rentalLab;
}

void ViewGUI::addVehicleGroup(Vehicle& veh) {
    label* vehLab = new label{*this, "* " + veh.getVehModel()};
    vehLab->format(true);
    viewVehicles.push_back(vehLab);
    viewPlc->field("veh") << *vehLab;
}
