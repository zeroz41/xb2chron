#ifndef CLASSES_GF_STATESALVAGEDIVEFADEIN_H
#define CLASSES_GF_STATESALVAGEDIVEFADEIN_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace gf {
// table 0x7100B573D0
class StateSalvageDiveFadeIn : public ::ai::State {
public:
    virtual ~StateSalvageDiveFadeIn();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
