#ifndef CLASSES_GF_STATESALVAGERESULT_H
#define CLASSES_GF_STATESALVAGERESULT_H

#include "classes/ai/State.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfGameSalvage; }
namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B57460
class StateSalvageResult : public ::ai::State {
public:
    // what GfGameSalvage::initialize registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateSalvageResult; }
    virtual ~StateSalvageResult() {}  // slot 0: inline (no unit defines it; GfGameSalvage::initialize makes the state, so its destructors are emitted there)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions (out of line, in StateSalvageDiveStart's unit); the slots above hand them the game
    void enter(GfGameSalvage* salvage, ai::State* prev);
    void leave(GfGameSalvage* salvage, ai::State* next);
    void update(GfGameSalvage* salvage, const fw::UpdateInfo& info);

    long m_clock;  // when it began (the names are not the original's)
    bool m_vibrated;
};
}  // namespace gf

#endif
