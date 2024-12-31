#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/drawing.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include <string>

using namespace nana;

class ReturnGroup : public panel<true> {

public:
    place groupPlc{*this};
    label m_header;
    std::string divText;

    ReturnGroup(window rootWin, std::string header={}, bool format=false, int gap=2, rectangle r={});
    ~ReturnGroup();
};
