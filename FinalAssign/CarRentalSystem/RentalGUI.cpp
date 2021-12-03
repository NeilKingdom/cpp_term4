#include "RentalGUI.h"

using namespace nana;

RentalGUI::RentalGUI(window rootWin) : panel<false>(rootWin) {

    //Layout
    rentalPlc.div("<vert <weight=5% gap=100 margin=[50,100,0,100] buttons>"
                  "<weight=5% gap=100 margin=[50,100,0,100] comboxes><weight=15%>"
                  "<vert weight=9% <weight=20%><weight=60% gap=100 margin=[50,200,0,200] rental><weight=20%>>"
                  "<weight=5% arrange=[200] margin=[50,0,0,100] finalize><>>");

    rentalPlc.field("buttons") << bAddCustomer << bAddRentalLocation << bAddVehicle;
    rentalPlc.field("comboxes") << *customersBox << *rentalLocationsBox << *vehiclesBox;
    rentalPlc.field("rental") << rentalStartLab << rentalStartField << rentalEndLab << rentalEndField;
    rentalPlc.field("finalize") << bFinalize;
}

//void RentalGUI::initRentalComponents(std::vector<Customer*>& custList, std::vector<RentalLocation*>& rentalList, std::vector<Vehicle*>& vehicleList, ViewGUI view, ReturnGUI rent) {
void RentalGUI::initRentalComponents(std::vector<Customer*>& custList, std::vector<RentalLocation*>& rentalList, std::vector<Vehicle*>& vehicleList) {

    /*********** Action Listeners For Buttons ************/

    //Add Customer Button
    //bAddCustomer.events().click([this, &custList, view] {
    bAddCustomer.events().click([this, &custList] {
        form addCustForm(API::make_center(300, 200), appear::decorate<appear::sizable>());
        place addCustPlc{addCustForm};
        textbox fNameField{addCustForm, "Enter First Name"};
        textbox lNameField{addCustForm, "Enter Last Name"};
        textbox addressField{addCustForm, "Enter Address"};
        textbox ageField{addCustForm, "Enter Age"};
        button bPreferredCustomer{addCustForm, "Preferred"};

        bool preferred = false;
        std::string fNameText = "";
        std::string lNameText = "";
        std::string addressText = "";
        std::string ageText = "";

        //Action Listeners
        bPreferredCustomer.events().click([&preferred] { preferred = true; });

        addCustForm.events().unload([&] {
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
                std::cerr << "Age entered was invalid. Customer will not be added to the system" << std::endl;
                return;
            }

            //Add customer data to list in Controller
            Customer* newCust = new Customer(fNameText, lNameText, addressText, std::stoi(ageText), preferred);
            custList.push_back(newCust);

            //Add customer name to combox in Rental Tab
            std::string custName = newCust->getFullName();
            customersBox->push_back(custName);

            //Add new customer group to View Tab
            //view.addCustomerGroup(*newCust);
        });

        addCustPlc.div("<vert gap=10 all>");
        addCustPlc.field("all") << fNameField << lNameField << addressField << ageField << bPreferredCustomer;
        addCustPlc.collocate();

        addCustForm.show();
        exec();
    });

    //Add Rental Location Button
    bAddRentalLocation.events().click([this, &rentalList] {
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
            rentalList.push_back(newRental);

            //Add rental location to combox in Rental Tab
            rentalLocationsBox->push_back(addressText);
        });

        addRentalPlc.div("<vert address>");
        addRentalPlc.field("address") << addressField;
        addRentalPlc.collocate();

        addRentalForm.show();
        exec();
    });

    //Add Vehicle Button
    bAddVehicle.events().click([this, &vehicleList] {
        form addVehicleForm(API::make_center(300, 200), appear::decorate<appear::sizable>());
        place addVehiclePlc{addVehicleForm};
        textbox brandField{addVehicleForm, "Enter Car's Brand"};
        textbox makeField{addVehicleForm, "Enter Car's Make"};

        std::string brandText = "";
        std::string makeText = "";

        //Action Listeners
        addVehicleForm.events().unload([&] {
            size_t lineNum = brandField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                brandText.append(brandField.getline(i).value());

            lineNum = makeField.display_line_count();
            for(size_t i = 0; i < lineNum; i++)
                makeText.append(makeField.getline(i).value());

            //Add the vehicle to the rental location associated with it
            if(lastRentalSelected == NULL) {
                std::cerr << "An associated rental location must be selected first. Vehicle will not be added to system" << std::endl;
            }
            else {
                //Add vehicle data to list in Controller
                Vehicle* newVehicle = new Vehicle(brandText, makeText);
                vehicleList.push_back(newVehicle);

                //Add vehicle model to combox in Rental Tab
                std::string vehicleModel = newVehicle->getVehModel();
                vehiclesBox->push_back(vehicleModel);

                //Add vehicle to the most recently selected rental location
                lastRentalSelected->addVehicle(*newVehicle);
            }
        });

        addVehiclePlc.div("<vert gap=10 fields>");
        addVehiclePlc.field("fields") << brandField << makeField;
        addVehiclePlc.collocate();

        addVehicleForm.show();
        exec();
    });

    /*********** Action listeners For Comboxes ************/

    //Customer combox
    rentalLocationsBox->events().selected([this, &custList] {
        lastCustSelected = custList.back();
    });

    //Rental Location combox
    rentalLocationsBox->events().selected([this, &rentalList] {
        lastRentalSelected = rentalList.back();
    });

    //Vehicle combox
    vehiclesBox->events().selected([this, &vehicleList] {
        lastVehicleSelected = vehicleList.back();
    });

    /*********** Action listeners For Finalize Button ************/
    bFinalize.events().click([this] {

        std::string rentalStartText = "";
        std::string rentalEndText = "";

        size_t lineNum = rentalStartField.display_line_count();
        for(size_t i = 0; i < lineNum; i++)
            rentalStartText.append(rentalStartField.getline(i).value());

        lineNum = rentalEndField.display_line_count();
        for(size_t i = 0; i < lineNum; i++)
            rentalEndText.append(rentalEndField.getline(i).value());

        if(lastCustSelected != NULL && lastRentalSelected != NULL && lastVehicleSelected != NULL
           && rentalStartText.compare("") != 0 && rentalEndText.compare("") != 0) {
            std::cout << "Successfully added entry" << std::endl;
            //lastVehicleSelected.setRentee(*lastCustSelected);
        }
        else {
            std::cout << "Failed to add entry" << std::endl;
        }
    });
}
