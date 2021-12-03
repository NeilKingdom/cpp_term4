#include "Controller.h"

using namespace nana;

Controller::Controller() {

    plc.div("vert <weight=5% tabbar><weight=95% tabpage>");

    //Initialize action listeners
    viewTabPage.initViewComponents();
    //rentalTabPage.initRentalComponents(custList, rentalList, vehicleList, viewTabPage, rentalTabPage);
    rentalTabPage.initRentalComponents(custList, rentalList, vehicleList);
    returnTabPage.initReturnComponents();

    this->events().unload([this](const arg_unload& e) {
        msgbox mb(*this,  ("Question"), msgbox::yes_no);
        mb.icon(mb.icon_question) <<  ("Would you like to exit the Car Rental System?");
        e.cancel = (mb() == mb.pick_no);
    });

    //TODO: Add color to background
    //daysPanel.bgcolor(API::);
    plc.field("tabbar") << tabBar << daysPanel;
    plc.field("tabpage").fasten(viewTabPage).fasten(rentalTabPage).fasten(returnTabPage); //Fasten tab pages

    //Tabbar labels and corresponding layouts
    tabBar.append("View", viewTabPage);
    tabBar.append("Rentals", rentalTabPage);
    tabBar.append("Return", returnTabPage);

    //Place components where the belong
    plc.collocate();

    //Manually click first tab
    size_t i = 0;
    tabBar.activated(i);
};

Controller::~Controller() {}

void start() {

    Controller program;
    program.show();
    exec();

    //Delete all allocated objects
    //for(int i = 0; i < ViewGUI::customerGroups.size(); i++)
        //delete ViewGUI::customerGroups[i];
    //for(int i = 0; i < ViewGUI::rentalGroups.size(); i++)
        //delete ViewGUI::rentalGroups[i];
    //for(int i = 0; i < ViewGUI::vehicleGroups.size(); i++)
        //delete ViewGUI::vehicleGroups[i];
}

int main() {
    start();
}
