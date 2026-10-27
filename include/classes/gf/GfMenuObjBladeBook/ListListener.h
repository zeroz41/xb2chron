#ifndef CLASSES_GF_GFMENUOBJBLADEBOOK_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADEBOOK_LISTLISTENER_H

#include "classes/gf/GfMenuObjBladeBook.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5FE28
class GfMenuObjBladeBook::ListListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC that initialize zeroes after storing the table
    struct State {
        unsigned char pad_0[0x10];
    };
    ListListener(GfMenuObjBladeBook* owner) : m_state(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    State m_state;
    GfMenuObjBladeBook* m_owner;  // 0x20
};
}  // namespace gf

#endif
