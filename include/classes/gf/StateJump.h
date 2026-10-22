#ifndef CLASSES_GF_STATEJUMP_H
#define CLASSES_GF_STATEJUMP_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B56390
class StateJump : public ::ai::State {
public:
    virtual ~StateJump();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
