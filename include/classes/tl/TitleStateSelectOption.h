#ifndef CLASSES_TL_TITLESTATESELECTOPTION_H
#define CLASSES_TL_TITLESTATESELECTOPTION_H

#include "classes/ai/State.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }

namespace tl {
class TitleMain;

// table 0x7100B40298
class TitleStateSelectOption : public ::ai::State {
public:
    // what TitleMain::initialize registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TitleStateSelectOption; }
    // inline: the deleting destructor only frees it
    virtual ~TitleStateSelectOption() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    void enter(TitleMain* title, ai::State* prev);
    void update(TitleMain* title, const fw::UpdateInfo& info);
};
}  // namespace tl

#endif
