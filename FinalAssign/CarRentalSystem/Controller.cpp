#include "Controller.h"

using namespace nana;

std::vector<Customer*> Controller::custList;
std::vector<RentalLocation*> Controller::rentalList;
std::vector<Vehicle*> Controller::vehicleList;
int Controller::day = 0;

Controller::Controller() {

    dayLab.format(true);
    plc.div("vert <weight=5% <weight=90% tabbar><weight=10% margin=[50,0,0,0] day>><weight=95% tabpage>");

    //Initialize action listeners
    viewTabPage.initViewComponents(returnTabPage, dayLab, day);
    rentalTabPage.initRentalComponents(viewTabPage, rentalTabPage, returnTabPage);
    returnTabPage.initReturnComponents();

    this->events().unload([this](const arg_unload& e) {
        msgbox mb(*this,  ("Question"), msgbox::yes_no);
        mb.icon(mb.icon_question) <<  ("Would you like to exit the Car Rental System?");
        e.cancel = (mb() == mb.pick_no);
    });

    //Layout
    plc.field("tabbar") << tabBar;
    plc.field("day") << dayLab;
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
    for(int i = 0; i < Controller::custList.size(); i++)
        delete Controller::custList[i];
    for(int i = 0; i < Controller::rentalList.size(); i++)
        delete Controller::rentalList[i];
    for(int i = 0; i < Controller::vehicleList.size(); i++)
        delete Controller::vehicleList[i];
}

int main() {
    start();
}
