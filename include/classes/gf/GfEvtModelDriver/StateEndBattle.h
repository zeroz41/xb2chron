#ifndef CLASSES_GF_GFEVTMODELDRIVER_STATEENDBATTLE_H
#define CLASSES_GF_GFEVTMODELDRIVER_STATEENDBATTLE_H

#include "classes/ai/State.h"
#include "classes/gf/GfEvtModelDriver.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B541C0
class GfEvtModelDriver::StateEndBattle : public ::ai::State {
public:
    virtual ~StateEndBattle();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
