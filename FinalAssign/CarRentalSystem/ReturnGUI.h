#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/group.hpp>

#include "Customer.h"

using namespace nana;

class ReturnGUI : public panel<false> {

private:
    place returnPlc{*this};
    group customerGroup{*this, "Select Customer", true};
    combox customersBox{*this, "Customer"};
    button bReturn{customerGroup, "Return Vehicle"};
    button bPrev{*this, "prev: <<"};
    button bNext{*this, "next: >>"};

public:
    ReturnGUI(window rootWin);
    void addCustomer(Customer& cust);
    void initReturnComponents();
};
