// not proven yet: its table differs from the original's (word 7: _ZN2gf27GfGamePlayerUniqueScheduler3vf1Ev where the original has =-8)
#ifndef CLASSES_GF_GFGAMEPLAYERUNIQUESCHEDULER_H
#define CLASSES_GF_GFGAMEPLAYERUNIQUESCHEDULER_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"

namespace gf {
// a base of gf::GfGamePlayerUniqueScheduler no evidence names yet
class TUnk_B55930 {
public:
    virtual ~TUnk_B55930();
    virtual void gevPartyMemberOK(bool) = 0;
    virtual void vf3();
    virtual void vf4();
};
// table 0x7100B55930; base at 0x0 unknown (TUnk_B55930)
class GfGamePlayerUniqueScheduler : public TUnk_B55930, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    virtual ~GfGamePlayerUniqueScheduler();  // slot 0
    virtual void vf1();  // slot 1
    virtual void gevPartyMemberOK(bool);  // slot 2
    virtual void vf3();  // slot 3
    virtual void vf4();  // slot 4
};
}  // namespace gf

#endif
