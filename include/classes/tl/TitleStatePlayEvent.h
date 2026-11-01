#ifndef CLASSES_TL_TITLESTATEPLAYEVENT_H
#define CLASSES_TL_TITLESTATEPLAYEVENT_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }
namespace gf { class RQ_SETUP_PARTY; }

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
    // gevPlayEvent sets it for GEV 0xD with a non-zero argument (the name is not the original's)
    bool m_endArg;
    unsigned char pad_22[0x6];
};

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its only caller,
// TitleStatePlayEvent::enter, hands it the RQ_SETUP_PARTY it builds on its stack (then passed to
// GfGameParty::setupRequestData) and nothing else. What it does: unless the driver is 0 or already in the party,
// puts it in the first empty driver slot with its blade (GfDataDriver::fn_7100241640(driver, 0) when 0 is
// passed) in blade slot 0 and the engaged index 0; does nothing when all ten slots are taken.
void fn_710015678C(gf::RQ_SETUP_PARTY& party, unsigned int driver, unsigned int blade);
}  // namespace tl

#endif
