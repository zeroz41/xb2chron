#ifndef CLASSES_TL_TITLESTATEPLAYGAME_H
#define CLASSES_TL_TITLESTATEPLAYGAME_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"

namespace ai { class State; }
namespace gf { enum GEV : int; }

namespace tl {
// table 0x7100B40610
class TitleStatePlayGame : public ::ai::State, public ::gf::IGfEvent {
public:
    virtual ~TitleStatePlayGame() {}  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 7
};
}  // namespace tl

#endif
