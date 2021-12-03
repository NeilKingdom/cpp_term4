#include "ReturnGUI.h"

using namespace nana;

ReturnGUI::ReturnGUI(window rootWin) : panel<false>(rootWin) {

    //customerGroup.div("<vert renting<<vehicle><return>>other>");
    //customerGroup["renting"] << rentingLab;
    //customerGroup["vehicle"] << vehicleLab;
    //customerGroup["return"] << bReturn;
    //customerGroup["other"] << daysRentedLab << rentalStartLab << rentalEndLab << totalPriceLab;

    //Layout
    returnPlc.div("<vert <<weight=25% margin=[50,0,0,100] <vert arrange=[75] combox>>"
                  "<><weight=70% margin=[50,100,0,0] cGrp>>"
                  "<vert weight=5% margin=[50,0,0,0] <<weight=50%><gap=100 buttons><weight=25%>>>"
                  "<>>");

    returnPlc.field("combox") << customersBox;
    returnPlc.field("cGrp") << customerGroup;
    returnPlc.field("buttons") << bPrev << bNext;
}

void ReturnGUI::addCustomer(Customer& cust) {

    //TODO: Needs to be checked with vehicleList
    label rentingLab{customerGroup};
    label vehicleLab{customerGroup};
    label daysRentedLab{customerGroup};
    label rentalStartLab{customerGroup};
    label rentalEndLab{customerGroup};
    label totalPriceLab{customerGroup};
}

void ReturnGUI::initReturnComponents() {

}
