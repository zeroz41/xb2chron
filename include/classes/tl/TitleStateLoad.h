#ifndef CLASSES_TL_TITLESTATELOAD_H
#define CLASSES_TL_TITLESTATELOAD_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace tl {
// table 0x7100B40178
class TitleStateLoad : public ::ai::State {
public:
    virtual ~TitleStateLoad();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace tl

#endif
