#ifndef CLASSES_GF_GFMENUOBJENEMYSTATUS_ELEMLISTENER_H
#define CLASSES_GF_GFMENUOBJENEMYSTATUS_ELEMLISTENER_H

#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61D40
class GfMenuObjEnemyStatus::ElemListener : public ::ui::UIObjectListener {
public:
    // a 4-aligned aggregate at 0xC that initialize zeroes after storing the table, as MainListener's (the name is not
    // the original's)
    struct State {
        unsigned int pad_0[4];  // nothing in this unit reads it
    };
    ElemListener(GfMenuObjEnemyStatus* owner) : m_state(), m_owner(owner) {}
    virtual ~ElemListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    State m_state;
    GfMenuObjEnemyStatus* m_owner;  // 0x20
};
}  // namespace gf

#endif
