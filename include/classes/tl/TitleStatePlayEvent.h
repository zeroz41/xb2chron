#ifndef CLASSES_TL_TITLESTATEPLAYEVENT_H
#define CLASSES_TL_TITLESTATEPLAYEVENT_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"

namespace ai { class State; }

namespace tl {
// table 0x7100B40868
class TitleStatePlayEvent : public ::ai::State, public ::gf::IGfEvent {
public:
    virtual ~TitleStatePlayEvent();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void vf7();  // slot 7
};
}  // namespace tl

#endif
