#ifndef CLASSES_GF_GFMENUOBJBLADEBOOK_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADEBOOK_MAINLISTENER_H

#include "classes/gf/GfMenuObjBladeBook.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FE00
class GfMenuObjBladeBook::MainListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC that initialize zeroes after storing the table
    struct State {
        unsigned char pad_0[0x10];
    };
    MainListener(GfMenuObjBladeBook* owner) : m_state(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    State m_state;
    GfMenuObjBladeBook* m_owner;  // 0x20
};
}  // namespace gf

#endif
