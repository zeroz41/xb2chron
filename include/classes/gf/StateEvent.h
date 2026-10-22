#ifndef CLASSES_GF_STATEEVENT_H
#define CLASSES_GF_STATEEVENT_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B564B0
class StateEvent : public ::ai::State {
public:
    virtual ~StateEvent();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
