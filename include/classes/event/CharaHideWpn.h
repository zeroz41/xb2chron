#ifndef CLASSES_EVENT_CHARAHIDEWPN_H
#define CLASSES_EVENT_CHARAHIDEWPN_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E728
class CharaHideWpn : public ::event::ICmd {
public:
    // no destructor of its own: slot 0 holds ICmd::~ICmd, so update is the key function
    CharaHideWpn() : m_flags(0) {}
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4

    // CharaObj holds one at 0x938, the next command at +0x18; the names are not the original's
    // bit 0: update acts at all; bit 1: passed on to setHideWeapon; bit 2: the weapon is hidden (update sets it,
    // term shows the weapon again while it is set); bit 3: the time was not positive (hidden until term)
    unsigned int m_flags;  // 0x8
    unsigned int m_id;  // 0xc: the bdat id of the character (GfObjAcc::getBdatId)
    float m_time;  // 0x10: the frames left (val(1)); counted down by FrameInfo::m_step
    unsigned int pad_14;
};
}  // namespace event

#endif
