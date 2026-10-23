#ifndef CLASSES_TL_TITLESTATESAVEDATA_H
#define CLASSES_TL_TITLESTATESAVEDATA_H

#include "classes/ai/State.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }

namespace tl {
class TitleMain;

// table 0x7100B401C0; the name is its getName string's, "TitleStateSaveData" (new in 3.0.1; its symbols are unnamed)
class TitleStateSaveData : public ::ai::State {
public:
    // what TitleMain::initialize registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TitleStateSaveData; }
    // inline: the deleting destructor only frees it
    virtual ~TitleStateSaveData() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the state's onStep
    // tail-calls it with its own this, the title and the step's argument (the other states' update shape).
    void fn_710015359C(TitleMain* title, const fw::UpdateInfo& info);
};
}  // namespace tl

#endif
