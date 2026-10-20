#ifndef CLASSES_GF_GFGAMEPLAYERUNIQUESCHEDULER_H
#define CLASSES_GF_GFGAMEPLAYERUNIQUESCHEDULER_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGamePlayerUniqueScheduler; }

namespace gf {
// table 0x7100B55930
class GfGamePlayerUniqueScheduler : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerUniqueScheduler>, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    virtual ~GfGamePlayerUniqueScheduler();  // slot 0
    virtual void gevPartyMemberOK(bool);  // slot 2
    virtual void vf3();  // slot 3
    virtual void vf4();  // slot 4
};
}  // namespace gf

#endif
