#ifndef CLASSES_GF_ENEMY_STATEFIELDSQUADMEMBER_H
#define CLASSES_GF_ENEMY_STATEFIELDSQUADMEMBER_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }

namespace gf { namespace enemy {
// table 0x7100B65D28
class StateFieldSquadMember : public ::gf::GfStateBase {
public:
    virtual ~StateFieldSquadMember();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}}  // namespace gf::enemy

#endif
