#ifndef CLASSES_GF_NPC_STATEIDLE_H
#define CLASSES_GF_NPC_STATEIDLE_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }

namespace gf { namespace npc {
// table 0x7100B66900
class StateIdle : public ::gf::GfStateBase {
public:
    virtual ~StateIdle();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}}  // namespace gf::npc

#endif
