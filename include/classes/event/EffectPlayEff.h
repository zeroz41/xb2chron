#ifndef CLASSES_EVENT_EFFECTPLAYEFF_H
#define CLASSES_EVENT_EFFECTPLAYEFF_H

#include "classes/event/ICmd.h"

namespace event {
class EffectCtrl;

// table 0x7100B3E808
class EffectPlayEff : public ::event::ICmd {
public:
    virtual ~EffectPlayEff() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // EffectObj holds one at 0x960; update starts m_ctrl's effect and kills it when the time runs out (the names are
    // not the original's)
    unsigned int m_flags;  // 0x8; bit 0: the time is not counted down (Ira game type, scene state 2, no time)
    unsigned char pad_c[0xc];
    EffectCtrl* m_ctrl;  // 0x18: update does nothing without it
    float m_time;  // 0x20: frames left, val(1) at the start (term: -1)
};
}  // namespace event

#endif
