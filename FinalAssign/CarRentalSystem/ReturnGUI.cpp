#include "ReturnGUI.h"
#include "Controller.h"

using namespace nana;

ReturnGUI::ReturnGUI(window rootWin) : panel<false>(rootWin) {

    //Add placeholder customer to customer groups vector
    customerProfiles.push_back(new ReturnGroup(*this, "<color=red bold=true>No Customers are Currently Renting Vehicles</>", true));
    customerProfile = customerProfiles.back();

    //Layout
    returnPlc->div("<vert <<weight=25% margin=[50,0,0,100] <vert arrange=[75] combox>>"
                  "<><weight=70% margin=[50,100,0,0] cGrp>>"
                  "<vert weight=5% margin=[50,0,0,0] <<weight=50%><gap=100 buttons><weight=25%>>>"
                  "<>>");

    returnPlc->field("combox") << customersBox;
    returnPlc->field("cGrp") << *customerProfile;
    returnPlc->field("buttons") << bPrev << bNext;
}

void ReturnGUI::addCustomerProfile(Customer* prevSelectedCustomer, Vehicle* prevSelectedVehicle) {

    retrnCustList.push_back(prevSelectedCustomer);
    retrnVehList.push_back(prevSelectedVehicle);
    customersBox.option(retrnCustList.size()-1); //Select combox for safety
    customerProfiles.push_back(new ReturnGroup(*this, "<color=red bold=true>" + prevSelectedCustomer->getFullName() + "</>", true));
    customerProfile = customerProfiles.back();

    //Generate labels
    vehicleLab = new label{*customerProfile, "Vehicle: " + prevSelectedVehicle->getVehModel()};
    returnVehLab = new label{*customerProfile, "Return Vehicle: "};
    bReturn = new button{*customerProfile, "Return"};
    daysRentedLab = new label{*customerProfile, "Days Rented: " + std::to_string(prevSelectedVehicle->getDaysRented())};
    rentalStartLab = new label{*customerProfile, "Rental Start Day: " + std::to_string(prevSelectedVehicle->getRentalStartDate())};
    rentalEndLab = new label{*customerProfile, "Rental End Day: " + std::to_string(prevSelectedVehicle->getRentalEndDate())};
    totalPriceLab = new label{*customerProfile, "Rental Cost: $" + std::to_string(calcPrice(prevSelectedCustomer, prevSelectedVehicle))};
    amountOwingLab = new label{*customerProfile, "Customer Owes Company: $" + std::to_string(prevSelectedCustomer->getAmountOwing())};

    //Action listener for button
    bReturn->events().click([this, prevSelectedCustomer, prevSelectedVehicle] {

        bool cancel;
        msgbox mb(*this, ("Question"), msgbox::yes_no);
        mb.icon(mb.icon_question) <<  ("Are you sure you would like to return the vehicle\nfor customer " + prevSelectedCustomer->getFullName());
        cancel = (mb() == mb.pick_no);

        if(!cancel) {
            std::cout << "Returning vehicle " << prevSelectedVehicle->getVehModel() << std::endl;
            prevSelectedVehicle->returnVehicle();
            prevSelectedVehicle->setIsInService(true);
            prevSelectedVehicle->setAmountOwing(0.0f);
            prevSelectedVehicle->setDaysRented(0);

            //Remove customer and vehicle from any vectors or lists
            retrnVehList.erase(retrnVehList.begin() + (int)(customersBox.option()));
            retrnCustList.erase(retrnCustList.begin() + (int)(customersBox.option()));
            customerProfiles.erase(customerProfiles.begin() + (int)(customersBox.option()));
            customersBox.erase(customersBox.option());

            //If customers are remaining, display the previous one
            if(customersBox.the_number_of_options() > 0) {
                customersBox.option((customersBox.option()-1) % customersBox.the_number_of_options());
                updateLabels(((customersBox.option()) % customersBox.the_number_of_options()), false);
                return;
            }
            //Otherwise display placeholder
            else {
                refreshTab(*(new ReturnGroup(*this, "<color=red bold=true>No Customers are Currently Renting Vehicles</>", true)));
                return;
            }
        }
        else {
            std::cout << "Cancelling return..." << std::endl;
        }
    });

    //Layout
    customerProfile->groupPlc.field("vehicle") << *vehicleLab;
    customerProfile->groupPlc.field("return") << *returnVehLab;
    customerProfile->groupPlc.field("button") << *bReturn;
    customerProfile->groupPlc.field("other") << *daysRentedLab << *rentalStartLab << *rentalEndLab << *totalPriceLab << *amountOwingLab;

    refreshTab(*customerProfile);
}

float ReturnGUI::calcPrice(Customer* prevSelectedCustomer, Vehicle* prevSelectedVehicle) {

    int daysRented, rentalStartDate, rentalEndDate, daysOverdue, rentalPrice;
    daysRented = prevSelectedVehicle->getDaysRented();
    rentalStartDate = prevSelectedVehicle->getRentalStartDate();
    rentalEndDate = prevSelectedVehicle->getRentalEndDate();
    rentalPrice = prevSelectedVehicle->getRentalPrice();

    //Calculate how much customer owes from start date to end date
    float amountOwing = prevSelectedVehicle->getAmountOwing();
    if(daysRented > (rentalEndDate - rentalStartDate)) {
        amountOwing += amountOwing;
    }
    else {
        if(prevSelectedCustomer->isPreferred())
            amountOwing = daysRented * rentalPrice * 0.8f; //20% off
        else if(prevSelectedCustomer->getAge() <= 25)
            amountOwing = daysRented * rentalPrice * 1.2f; //20% extra
        else
            amountOwing = daysRented * rentalPrice;
    }

    prevSelectedVehicle->setAmountOwing(amountOwing);

    //Calculate total that customer owes company
    if(prevSelectedVehicle->getDaysRented() > 0) {
        amountOwing = prevSelectedCustomer->getAmountOwing();
        if(daysRented > (rentalEndDate - rentalStartDate)) {
            prevSelectedCustomer->addAmountOwing(amountOwing);
        }
        else {
            if(prevSelectedCustomer->isPreferred())
                prevSelectedCustomer->addAmountOwing(rentalPrice * 0.8f); //20% off
            else if(prevSelectedCustomer->getAge() <= 25)
                prevSelectedCustomer->addAmountOwing(rentalPrice * 1.2f); //20% extra
            else
                prevSelectedCustomer->addAmountOwing(rentalPrice);
        }
    }

    return prevSelectedVehicle->getAmountOwing();
}

void ReturnGUI::refreshTab(ReturnGroup& customerProfile) {

    returnPlc = new place{*this};
    returnPlc->div("<vert <<weight=25% margin=[50,0,0,100] <vert arrange=[75] combox>>"
                  "<><weight=70% margin=[50,100,0,0] cGrp>>"
                  "<vert weight=5% margin=[50,0,0,0] <<weight=50%><gap=100 buttons><weight=25%>>>"
                  "<>>");

    returnPlc->field("combox") << customersBox;
    returnPlc->field("cGrp") << customerProfile;
    returnPlc->field("buttons") << bPrev << bNext;

    returnPlc->collocate();
    customerProfile.groupPlc.collocate();
}

void ReturnGUI::updateLabels(int index, bool calc_price=false) {

    Customer* prevSelectedCustomer = retrnCustList.at(index);
    Vehicle* prevSelectedVehicle = retrnVehList.at(index);

    customerProfile = new ReturnGroup(*this, "<color=red bold=true>" + prevSelectedCustomer->getFullName() + "</>", true);

    vehicleLab = new label{*customerProfile, "Vehicle: " + prevSelectedVehicle->getVehModel()};
    returnVehLab = new label{*customerProfile, "Return Vehicle: "};
    bReturn = new button{*customerProfile, "Return"};
    daysRentedLab = new label{*customerProfile, "Days Rented: " + std::to_string(prevSelectedVehicle->getDaysRented())};
    rentalStartLab = new label{*customerProfile, "Rental Start Day: " + std::to_string(prevSelectedVehicle->getRentalStartDate())};
    rentalEndLab = new label{*customerProfile, "Rental End Day: " + std::to_string(prevSelectedVehicle->getRentalEndDate())};

    if(calc_price)
        totalPriceLab = new label{*customerProfile, "Rental Cost: $" + std::to_string(calcPrice(prevSelectedCustomer, prevSelectedVehicle))};
    else
        totalPriceLab = new label{*customerProfile, "Rental Cost: $" + std::to_string(prevSelectedVehicle->getAmountOwing())};

    amountOwingLab = new label{*customerProfile, "Customer Owes Company: $" + std::to_string(prevSelectedCustomer->getAmountOwing())};

    //Action listener for button
    bReturn->events().click([this, prevSelectedCustomer, prevSelectedVehicle] {

        bool cancel;
        msgbox mb(*this, ("Question"), msgbox::yes_no);
        mb.icon(mb.icon_question) <<  ("Are you sure you would like to return the vehicle\nfor customer " + prevSelectedCustomer->getFullName());
        cancel = (mb() == mb.pick_no);

        if(!cancel) {
            std::cout << "Returning vehicle " << prevSelectedVehicle->getVehModel() << std::endl;
            prevSelectedVehicle->returnVehicle();
            prevSelectedVehicle->setIsInService(true);
            prevSelectedVehicle->setAmountOwing(0.0f);
            prevSelectedVehicle->setDaysRented(0);

            //Remove customer and vehicle from any vectors or lists
            retrnVehList.erase(retrnVehList.begin() + (int)(customersBox.option()));
            retrnCustList.erase(retrnCustList.begin() + (int)(customersBox.option()));
            customerProfiles.erase(customerProfiles.begin() + (int)(customersBox.option()));
            customersBox.erase(customersBox.option());

            if(customersBox.the_number_of_options() > 0) {
                customersBox.option((customersBox.option()-1) % customersBox.the_number_of_options());
                updateLabels(((customersBox.option()) % customersBox.the_number_of_options()), false);
                return;
            }
            else {
                refreshTab(*(new ReturnGroup(*this, "<color=red bold=true>No Customers are Currently Renting Vehicles</>", true)));
                return;
            }
        }
        else {
            std::cout << "Cancelling return..." << std::endl;
        }
    });

    //Layout
    customerProfile->groupPlc.field("vehicle") << *vehicleLab;
    customerProfile->groupPlc.field("return") << *returnVehLab;
    customerProfile->groupPlc.field("button") << *bReturn;
    customerProfile->groupPlc.field("other") << *daysRentedLab << *rentalStartLab << *rentalEndLab << *totalPriceLab << *amountOwingLab;

    refreshTab(*customerProfile);
}

void ReturnGUI::initReturnComponents() {
    bPrev.events().click([this] {
        if(customersBox.the_number_of_options() > 0) {
            customersBox.option((customersBox.option()-1) % customersBox.the_number_of_options());
            updateLabels((customersBox.option()) % customersBox.the_number_of_options(), false);
        }
    });

    bNext.events().click([this] {
        if(customersBox.the_number_of_options() > 0) {
            customersBox.option((customersBox.option()+1) % customersBox.the_number_of_options());
            updateLabels((customersBox.option()) % customersBox.the_number_of_options(), false);
        }
    });

    customersBox.events().selected([this] {
        updateLabels(customersBox.option(), false);
    });
}
