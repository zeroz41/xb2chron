#ifndef CLASSES_EVENT_EFFECTPLAYEFF_H
#define CLASSES_EVENT_EFFECTPLAYEFF_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E808
class EffectPlayEff : public ::event::ICmd {
public:
    virtual ~EffectPlayEff() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned char pad_8[0x18];
    float pad_20;  // term: -1
};
}  // namespace event

#endif
