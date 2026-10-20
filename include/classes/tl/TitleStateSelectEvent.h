#ifndef CLASSES_TL_TITLESTATESELECTEVENT_H
#define CLASSES_TL_TITLESTATESELECTEVENT_H

#include "classes/ai/State.h"

namespace ai { class State; }

namespace tl {
// table 0x7100B40250
class TitleStateSelectEvent : public ::ai::State {
public:
    virtual ~TitleStateSelectEvent();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace tl

#endif
