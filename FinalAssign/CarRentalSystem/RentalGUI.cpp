#include "RentalGUI.h"
#include "Controller.h"

using namespace nana;

RentalGUI::RentalGUI(window rootWin) : panel<false>(rootWin) {

    //Add "all" selection to rental locations to view all vehicles
    rentalLocationsBox.push_back("All");

    //Layout
    rentalPlc.div("<vert <weight=5% gap=100 margin=[50,100,0,100] add><weight=5% gap=100 margin=[50,100,0,100] delete>"
                  "<weight=5% gap=100 margin=[50,100,0,100] comboxes><weight=15%>"
                  "<vert weight=9% <weight=20%><weight=60% gap=100 margin=[50,200,0,200] rental><weight=20%>>"
                  "<weight=5% arrange=[200] margin=[50,0,0,100] finalize><>>");

    rentalPlc.field("add") << bAddCustomer << bAddRentalLocation << bAddVehicle;
    rentalPlc.field("delete") << bDelCustomer << bDelRentalLocation << bDelVehicle;
    rentalPlc.field("comboxes") << customersBox << rentalLocationsBox << vehiclesBox;
    rentalPlc.field("rental") << rentalStartLab << rentalStartField << rentalEndLab << rentalEndField;
    rentalPlc.field("finalize") << bFinalize;
}

void RentalGUI::initRentalComponents(ViewGUI& view, RentalGUI& rent, ReturnGUI& retrn) {

    /*********** Action Listeners For Add Buttons ************/

    //Add Customer Button
    bAddCustomer.events().click([this, &view] {
        form addCustForm(API::make_center(300, 200), appear::decorate<appear::sizable>());
        place addCustPlc{addCustForm};
        textbox fNameField{addCustForm, "Enter First Name"};
        textbox lNameField{addCustForm, "Enter Last Name"};
        textbox addressField{addCustForm, "Enter Address"};
        textbox ageField{addCustForm, "Enter Age"};
        button bPreferredCustomer{addCustForm, "Preferred"};

        bool preferred = false;

        //Action Listeners
        bPreferredCustomer.events().click([&] {
            int testAge;
            std::string ageText = "";

            size_t lineNum = ageField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                ageText.append(ageField.getline(i).value());

            try{
                testAge = std::stoi(ageText);
                if(testAge > 25)
                    preferred = true;
                else
                    std::cout << "Customers 25 or under cannot be preferred customers" << std::endl;

            } catch(std::exception& e) {
                std::cerr << "Age entered was invalid." << std::endl;
            }
        });

        addCustForm.events().unload([&] {
            std::string fNameText = "";
            std::string lNameText = "";
            std::string addressText = "";
            std::string ageText = "";

            size_t lineNum = fNameField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                fNameText.append(fNameField.getline(i).value());

            lineNum = lNameField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                lNameText.append(lNameField.getline(i).value());

            lineNum = addressField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                addressText.append(addressField.getline(i).value());

            lineNum = ageField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                ageText.append(ageField.getline(i).value());

            try{
                int testAge = std::stoi(ageText);
            } catch(std::exception& e) {
                std::cerr << "Age entered was invalid. Not adding customer to system" << std::endl;
                return;
            }

            //Add customer data to list in Controller
            Customer* newCust = new Customer(fNameText, lNameText, addressText, std::stoi(ageText), preferred);
            Controller::custList.push_back(newCust);

            //Add customer name to combox in Rental Tab
            std::string custName = newCust->getFullName();
            customersBox.push_back(custName);

            //Add new customer group to view tab
            view.addCustomerGroup(*newCust);
        });

        addCustPlc.div("<vert gap=10 all>");
        addCustPlc.field("all") << fNameField << lNameField << addressField << ageField << bPreferredCustomer;
        addCustPlc.collocate();

        addCustForm.show();
        exec();
    });

    //Add Rental Location Button
    bAddRentalLocation.events().click([this, &view] {
        form addRentalForm(API::make_center(300, 200), appear::decorate<appear::sizable>());
        place addRentalPlc{addRentalForm};
        textbox addressField{addRentalForm, "Enter Address"};

        std::string addressText = "";

        //Action Listeners
        addRentalForm.events().unload([&] {

            size_t lineNum = addressField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                addressText.append(addressField.getline(i).value());

            //Add rental location data to list in Controller
            RentalLocation* newRental = new RentalLocation(addressText);
            Controller::rentalList.push_back(newRental);

            //Add rental location to combox in Rental Tab
            rentalLocationsBox.push_back(addressText);

            //Add rental location group to view tab
            view.addRentalGroup(*newRental);
        });

        addRentalPlc.div("<vert address>");
        addRentalPlc.field("address") << addressField;
        addRentalPlc.collocate();

        addRentalForm.show();
        exec();
    });

    //Add Vehicle Button
    bAddVehicle.events().click([this, &view] {
        form addVehicleForm(API::make_center(300, 200), appear::decorate<appear::sizable>());
        place addVehiclePlc{addVehicleForm};
        textbox brandField{addVehicleForm, "Enter Vehicle's Brand"};
        textbox makeField{addVehicleForm, "Enter Vehicle's Make"};
        textbox priceField{addVehicleForm, "Enter the Daily Payment Price of the Vehicle"};

        std::string brandText = "";
        std::string makeText = "";
        std::string priceText = "";

        //Action Listeners
        addVehicleForm.events().unload([&](const arg_unload& arg) {
            float testPrice;
            size_t lineNum = brandField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                brandText.append(brandField.getline(i).value());

            lineNum = makeField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                makeText.append(makeField.getline(i).value());

            lineNum = priceField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                priceText.append(priceField.getline(i).value());

            try{
                testPrice = std::stof(priceText);
            } catch(std::exception& e) {
                std::cerr << "Price entered was invalid. Vehicle will not be added to the system" << std::endl;
                return;
            }

            if(lastRentalSelected == nullptr) {
                msgbox mb(*this,  ("Question"), msgbox::yes_no);
                mb.icon(mb.icon_question) <<  "No Rental location is currently selected.\nPress yes if you would like to add vehicle anyways";
                arg.cancel = (mb() == mb.pick_no);

                //Cancel operation
                if(arg.cancel) {
                    std::cout << "Vehicle was not added" << std::endl;
                    addVehicleForm.modality();
                    API::close_window(addVehicleForm);
                    return;
                }
                //Add the vehicle to the rental location associated with it
                else {
                    //Add vehicle data to list in Controller
                    Vehicle* newVehicle = new Vehicle(brandText, makeText, testPrice);
                    Controller::vehicleList.push_back(newVehicle);

                    //Add vehicle model to combox in Rental Tab
                    std::string vehicleModel = newVehicle->getVehModel();
                    vehiclesBox.push_back(vehicleModel);

                    //Add rental location group to View Tab
                    view.addVehicleGroup(*newVehicle);
                }
            }
            else {
                //Add vehicle data to list in Controller
                Vehicle* newVehicle = new Vehicle(brandText, makeText, testPrice);
                Controller::vehicleList.push_back(newVehicle);

                //Add vehicle model to combox in Rental Tab
                std::string vehicleModel = newVehicle->getVehModel();
                vehiclesBox.push_back(vehicleModel);

                //Add rental location group to View Tab
                view.addVehicleGroup(*newVehicle);
            }
        });

        addVehiclePlc.div("<vert gap=10 fields>");
        addVehiclePlc.field("fields") << brandField << makeField << priceField;
        addVehiclePlc.collocate();

        addVehicleForm.show();
        exec();
    });

    /*********** Action Listeners For Delete Buttons ************/

    //Delete customers
    bDelCustomer.events().click([this, &retrn, &view] {

        if(Controller::custList.size() == 0) {
            std::cout << "No customers to delete" << std::endl;
        }
        else if(customersBox.option() < 0 || customersBox.option() > customersBox.the_number_of_options()) {
            std::cerr << "Something went wrong with the selection of customer combox" << std::endl;
        }
        else {

            bool cancel;
            msgbox mb(*this, ("Question"), msgbox::yes_no);
            mb.icon(mb.icon_question) <<  ("Are you sure you would like to delete customer " + lastCustSelected->getFullName());
            cancel = (mb() == mb.pick_no);

            if(!cancel) {

                //Delete label from view tab
                delete view.viewCustomers.at((int)(customersBox.option()));
                view.viewCustomers.erase(view.viewCustomers.begin() + (int)(customersBox.option()));
                view.refreshTab();

                //Delete entirely
                delete Controller::custList.at((int)(customersBox.option()));
                Controller::custList.erase(Controller::custList.begin() + (int)(customersBox.option()));

                //Delete from rental tab combox
                customersBox.erase(customersBox.option());

                std::cout << "Customer deleted" << std::endl;
            }
            else {
                std::cout << "Delete operation cancelled" << std::endl;
            }
        }
    });

    //Delete rental locations
    bDelRentalLocation.events().click([this, &view] {

        if(Controller::rentalList.size() == 0) {
            std::cout << "No rental location selected" << std::endl;
        }
        else if(rentalLocationsBox.option() == 0) {
            std::cout << "Cannot delete \"All\" option for rental locations" << std::endl;
        }
        else if(rentalLocationsBox.option() < 0 || rentalLocationsBox.option() > rentalLocationsBox.the_number_of_options()) {
            std::cerr << "Something went wrong with the selection of rental location combox" << std::endl;
        }
        else {

            bool cancel;
            msgbox mb(*this, ("Question"), msgbox::yes_no);
            mb.icon(mb.icon_question) <<  ("Are you sure you would like to delete rental location " + lastRentalSelected->getAddress());
            cancel = (mb() == mb.pick_no);

            if(!cancel) {

                //Delete label from view tab
                delete view.viewRentals.at((int)(rentalLocationsBox.option() -1));
                view.viewRentals.erase(view.viewRentals.begin() + (int)(rentalLocationsBox.option() -1));
                view.refreshTab();

                //Delete entirely
                delete Controller::rentalList.at((int)(rentalLocationsBox.option() -1));
                Controller::rentalList.erase(Controller::rentalList.begin() + (int)(rentalLocationsBox.option() -1));

                //Delete from rental tab combox
                rentalLocationsBox.erase(rentalLocationsBox.option());

                std::cout << "Rental location deleted" << std::endl;
            }
            else {
                std::cout << "Delete operation cancelled" << std::endl;
            }
        }
    });

    //Delete vehicles
    bDelVehicle.events().click([this, &view] {

        if(Controller::vehicleList.size() == 0) {
            std::cout << "No vehicles to delete" << std::endl;
        }
        else if(vehiclesBox.option() < 0 || vehiclesBox.option() > vehiclesBox.the_number_of_options()) {
            std::cerr << "Something went wrong with the selection of vehicle combox" << std::endl;
        }
        else {

            bool cancel;
            msgbox mb(*this, ("Question"), msgbox::yes_no);
            mb.icon(mb.icon_question) <<  ("Are you sure you would like to delete vehicle " + lastVehicleSelected->getVehModel());
            cancel = (mb() == mb.pick_no);

            if(!cancel) {

                //Delete label from view tab
                delete view.viewVehicles.at((int)(vehiclesBox.option()));
                view.viewVehicles.erase(view.viewVehicles.begin() + (int)(vehiclesBox.option()));
                view.refreshTab();

                //Delete entirely
                delete Controller::vehicleList.at((int)(vehiclesBox.option()));
                Controller::vehicleList.erase(Controller::vehicleList.begin() + (int)(vehiclesBox.option()));

                //Delete from rental tab combox
                vehiclesBox.erase(vehiclesBox.option());

                std::cout << "Vehicle deleted" << std::endl;
            }
            else {
                std::cout << "Delete operation cancelled" << std::endl;
            }
        }
    });

    /*********** Action listeners For Comboxes ************/

    //Customer combox
    customersBox.events().selected([this] {
        lastCustSelected = Controller::custList.at(customersBox.option());
    });

    //Rental Location combox
    rentalLocationsBox.events().selected([this] {

        vehiclesBox.clear();

        //Check if user selected "all" option
        if(rentalLocationsBox.option() == 0) {
            lastRentalSelected = nullptr;
            for(auto& veh : Controller::vehicleList) {
                vehiclesBox.push_back(veh->getVehModel());
            }
        }
        //Otherwise, only populate vehicles that belong to the selected rental location
        else {
            lastRentalSelected = Controller::rentalList.at(rentalLocationsBox.option()-1);
            for(auto& veh : lastRentalSelected->getVehicles()) {
                vehiclesBox.push_back(veh->getVehModel());
            }
        }
    });

    //Vehicle combox
    vehiclesBox.events().selected([this] {
        //If rental location is selected
        if(rentalLocationsBox.option() > 0) {
            int i = 0, j = 0;
            for(; i < Controller::rentalList.size(); i++) {
                for(; j < Controller::rentalList.at(i)->getVehicles().size(); j++) {
                    if(j == vehiclesBox.option())
                        break;
                }
                if(i == rentalLocationsBox.option())
                    break;
            }
            lastVehicleSelected = Controller::vehicleList.at((i-1) + j);
        }

        //If all option is selected
        else if(rentalLocationsBox.option() == 0) {
            lastVehicleSelected = Controller::vehicleList.at(vehiclesBox.option());
        }
    });

    /*********** Action listeners For Finalize Button ************/

    bFinalize.events().click([this, &retrn] {

        std::string rentalStartText = "";
        std::string rentalEndText = "";
        int testRentalStart, testRentalEnd;
        bool rentalStartSuccess = false, rentalEndSuccess = false;

        //Check that rentalStartField and rentalEndField are valid dates
        size_t lineNum = rentalStartField.display_line_count();
        for(size_t i = 0; i < lineNum; i++)
            rentalStartText.append(rentalStartField.getline(i).value());

        lineNum = rentalEndField.display_line_count();
        for(size_t i = 0; i < lineNum; i++)
            rentalEndText.append(rentalEndField.getline(i).value());

        try{
            testRentalStart = std::stoi(rentalStartText);
            if(testRentalStart >= Controller::day) {
                rentalStartSuccess = true;
            }
            else {
                std::cerr << "Rental Start Date is invalid. Please try again..." << std::endl;
                return;
            }
        } catch(std::exception& e) {
            std::cerr << "Rental Start Date is invalid. Please try again..." << std::endl;
            return;
        }

        try{
            testRentalEnd = std::stoi(rentalEndText);
            if(testRentalEnd > testRentalStart) {
                rentalEndSuccess = true;
            }
            else {
                std::cerr << "Rental End Date is invalid. Please try again..." << std::endl;
                return;
            }
        } catch(std::exception& e) {
            std::cerr << "Rental End Date is invalid. Please try again..." << std::endl;
            return;
        }

        if(lastCustSelected != nullptr && lastRentalSelected != nullptr && lastVehicleSelected != nullptr) {

            /******** Vehicle Check/Setup *********/

            //Check if car is already being rented
            if(lastVehicleSelected->getRentee()) {
                std::cout << "Vehicle is already being rented by " << lastVehicleSelected->getRentee()->getFullName() << std::endl;
                int daysRented = lastVehicleSelected->getDaysRented();
                int rentalStartDate = lastVehicleSelected->getRentalStartDate();
                int rentalEndDate = lastVehicleSelected->getRentalEndDate();

                if(daysRented > (rentalEndDate - rentalStartDate))
                    std::cout << "It is overdue by " << daysRented - (rentalEndDate - rentalStartDate) << " days" << std::endl;
                else
                    std::cout << "The vehicle will be available on day " << lastVehicleSelected->getRentalEndDate()+1 << std::endl;
                return;
            }

            //Check if car is in service
            if(lastVehicleSelected->getIsInService()) {
                std::cout << "Vehicle was returned today and needs servicing. It will be available tomorrow" << std::endl;
                return;
            }

            //Set vehicle start and end
            lastVehicleSelected->setRentalStartDate(testRentalStart);
            lastVehicleSelected->setRentalEndDate(testRentalEnd);

            //Add vehicle to the most recently selected rental location
            lastRentalSelected->addVehicle(lastVehicleSelected);

            //Set rentee of car to the selected customer
            lastVehicleSelected->setRentee(lastCustSelected);

            //Add vehicle to pending return tab
            retrn.pendingVehicles.push_back(lastVehicleSelected);

            /******** Customer Check/Setup *********/

            //Add customer to pending return tab
            retrn.pendingCustomers.push_back(lastCustSelected);

            //Check if customer is renting day one
            if(lastVehicleSelected->getRentalStartDate() == Controller::day) {
                retrn.customersBox.push_back(lastCustSelected->getFullName());
                retrn.addCustomerProfile(lastCustSelected, lastVehicleSelected);
                //Remove from pending list
                retrn.pendingCustomers.erase(retrn.pendingCustomers.begin());
                retrn.pendingVehicles.erase(retrn.pendingVehicles.begin());
            }

            /**************** Other **************/

            vehiclesBox.clear();

            //Check if user selected "all" option
            if(rentalLocationsBox.option() == 0) {
                lastRentalSelected = nullptr;
                for(auto& veh : Controller::vehicleList) {
                    vehiclesBox.push_back(veh->getVehModel());
                }
            }
            //Otherwise, only populate vehicles that belong to the selected rental location
            else {
                lastRentalSelected = Controller::rentalList.at(rentalLocationsBox.option()-1);
                for(auto& veh : lastRentalSelected->getVehicles()) {
                    vehiclesBox.push_back(veh->getVehModel());
                }
            }

            std::cout << "Customer " << lastCustSelected->getFullName() << " is now renting " << lastVehicleSelected->getVehModel() << " from day " << testRentalStart << " to day " << testRentalEnd << std::endl;
        }
        else {
            std::cerr << "All forms and selections must be filled out before the rental can be finalized..." << std::endl;
        }
    });
}
