#ifndef CLASSES_GF_GFMENUOBJBLADESWITCH_H
#define CLASSES_GF_GFMENUOBJBLADESWITCH_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuSequence.h"
#include "ui/EventData.h"

namespace gf {
// table 0x7100B603C0; the field prompt to change blades, attached under 0x22: update opens it while the leader can
// change blades, setActive turns that on and off
class GfMenuObjBladeSwitch : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjBladeSwitch(unsigned int handle);
    virtual ~GfMenuObjBladeSwitch();  // slot 0
    // its open (0x21) and close (0x22) events: 1.0.0's, inline here as 3.0.1 keeps no copy (update and the
    // listener inline them)
    static void open() {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x22));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
    static void close() {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x22));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
    // tells it (event 0x100) whether it may show
    static void setActive(bool active);
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // the names are not the original's: update opened it (it compares the leader's state with it), its open
    // event (0x21) ran and its close (0x22) not yet, setActive's last value
    bool m_shown;
    bool m_opened;
    bool m_active;
    GfMenuSequence<GfMenuObjBladeSwitch, 8> m_seq;  // no job uses it in 3.0.1
};
}  // namespace gf

#endif
