#ifndef CLASSES_GF_ENEMY_STATEFIELDHOME_H
#define CLASSES_GF_ENEMY_STATEFIELDHOME_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }

namespace gf { namespace enemy {
// table 0x7100B65C38
class StateFieldHome : public ::gf::GfStateBase {
public:
    virtual ~StateFieldHome();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}}  // namespace gf::enemy

#endif
