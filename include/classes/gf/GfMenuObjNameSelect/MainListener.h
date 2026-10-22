#ifndef CLASSES_GF_GFMENUOBJNAMESELECT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJNAMESELECT_MAINLISTENER_H

#include "classes/gf/GfMenuObjNameSelect.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63A20
class GfMenuObjNameSelect::MainListener : public ::ui::UIObjectListener {
public:
    // where the picking is: event 1 sets both fields with one 8-byte store, so they are one object
    struct Selection {
        int m_opened;  // 1 once the opening animation's end (event 0xC) enabled the selection
        int m_select;  // the name picked (event 8), -1 for none or when the confirmation was declined
    };
    // the names offered and the selection: one object at 0xC, whose alignment (4) keeps the code from reading
    // m_opened and m_select with one 8-byte load (the names here are not the original's)
    struct Work {
        int m_nameCount;  // the count of LAY_select_name@%02d children (event 1)
        Selection m_selection;
    };
    MainListener(GfMenuObjNameSelect* owner) : m_work(), pad_18(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    Work m_work;
    unsigned char pad_18[4];
    GfMenuObjNameSelect* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
