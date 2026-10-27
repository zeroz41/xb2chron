#ifndef CLASSES_GF_GFMENUOBJENEMYSTATUS_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJENEMYSTATUS_MAINLISTENER_H

#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61D18
class GfMenuObjEnemyStatus::MainListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC that initialize zeroes after storing the table (the names are not the
    // original's)
    struct State {
        int m_open;            // 1 while open (case 0xC skips its work then; event 1 clears it)
        int m_labelCtrl;       // the "fadein"/"label" control of IMG_reaction_icon reciveEvent hooks (-1: none)
        int m_pulseCtrl;       // the "pulse" control of IMG_reaction_icon_eff (-1: none; suspended on reaction)
        unsigned char pad_C[4];
    };
    MainListener(GfMenuObjEnemyStatus* owner) : m_state(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    State m_state;
    GfMenuObjEnemyStatus* m_owner;  // 0x20
};
}  // namespace gf

#endif
