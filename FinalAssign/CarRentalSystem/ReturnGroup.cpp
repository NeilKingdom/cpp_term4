#include "ReturnGroup.h"

using namespace nana;

ReturnGroup::ReturnGroup(window rootWin, std::string header, bool format, int gap, rectangle r)
: panel<true>(rootWin), m_header(*this, header) {

    m_header.format(format);
    nana::size sz = m_header.measure(1000);
    divText = "vertical margin=[0," + std::to_string(gap) + "," + std::to_string(gap) + "," + std::to_string(gap) + "]" + " <weight=" + std::to_string(sz.height) + " <weight=5><header weight=" + std::to_string(sz.width+1) + ">>"
            "<vert margin=[50,0,0,50] gap=10 <vert gap=10 vehicle><vert weight=10% <<weight=65% return><weight=35% margin=[0,50,0,0] button>>><vert gap=10 other>>";
    groupPlc.field("header") << m_header;

    //Draw border manually
    color bkgrnd = this->bgcolor();
    color frgnd = colors::blue;
    bgcolor(bkgrnd);

    drawing dw(*this);
    dw.draw([gap,sz,frgnd,bkgrnd](paint::graphics& graph) {
        graph.rectangle(true, bkgrnd);
        graph.round_rectangle(rectangle(point(gap-1, sz.height/2), nana::size(graph.width()-2*(gap-1), graph.height()-sz.height/2-(gap-1))), 3,3, colors::gray_border, true, bkgrnd);
    });

    groupPlc.div(divText.c_str());
}

ReturnGroup::~ReturnGroup() {}
