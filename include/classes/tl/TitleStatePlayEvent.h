#ifndef CLASSES_TL_TITLESTATEPLAYEVENT_H
#define CLASSES_TL_TITLESTATEPLAYEVENT_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }

namespace tl {
class TitleMain;

// table 0x7100B40868
class TitleStatePlayEvent : public ::ai::State, public ::gf::IGfEvent {
public:
    // what TitleMain::initialize registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TitleStatePlayEvent; }
    // inline: the deleting destructor only frees it
    virtual ~TitleStatePlayEvent() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    void enter(TitleMain* title, ai::State* prev);
    void update(TitleMain* title, const fw::UpdateInfo& info);
    // its table's slot 7 and IGfEvent's slot 36 (thunk) hold it: gevPlayEvent (new in 3.0.1's table)
    virtual void gevPlayEvent(gf::GEV gev, unsigned int arg);  // slot 7

    bool m_openBtlModelView;  // onLeave closes the battle model view when set (the name is not the original's)
    unsigned char pad_21[0x7];
};
}  // namespace tl

#endif
