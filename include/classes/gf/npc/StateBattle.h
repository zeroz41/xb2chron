#ifndef CLASSES_GF_NPC_STATEBATTLE_H
#define CLASSES_GF_NPC_STATEBATTLE_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }

namespace gf { namespace npc {
// a template: 2 instances in the module
template <typename T0>
class StateBattle : public ::gf::GfStateBase {
public:
    virtual ~StateBattle();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}}  // namespace gf::npc

#endif
