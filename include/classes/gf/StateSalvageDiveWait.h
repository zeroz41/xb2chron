#ifndef CLASSES_GF_STATESALVAGEDIVEWAIT_H
#define CLASSES_GF_STATESALVAGEDIVEWAIT_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B572B0
class StateSalvageDiveWait : public ::ai::State {
public:
    virtual ~StateSalvageDiveWait();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
