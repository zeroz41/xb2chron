#ifndef CLASSES_GF_STATESALVAGEWAIT_H
#define CLASSES_GF_STATESALVAGEWAIT_H

#include "classes/ai/State.h"

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfGameSalvage; }
namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B56FE0
class StateSalvageWait : public ::ai::State {
public:
    virtual ~StateSalvageWait();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions (out of line, in StateSalvageDiveStart's unit); the slots above hand them the game
    void enter(GfGameSalvage* salvage, ai::State* prev);
    void leave(GfGameSalvage* salvage, ai::State* next);
    void update(GfGameSalvage* salvage, const fw::UpdateInfo& info);
};
}  // namespace gf

#endif
