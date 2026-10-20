#ifndef CLASSES_GF_STATEGRAVE_H
#define CLASSES_GF_STATEGRAVE_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B56348
class StateGrave : public ::ai::State {
public:
    virtual ~StateGrave();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
