#ifndef CLASSES_GF_STATESALVAGERESULTUI_H
#define CLASSES_GF_STATESALVAGERESULTUI_H

#include "classes/ai/State.h"

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfGameSalvage; }
namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B574A8
class StateSalvageResultUi : public ::ai::State {
public:
    virtual ~StateSalvageResultUi();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions (out of line, in StateSalvageDiveStart's unit); the slots above hand them the game
    void enter(GfGameSalvage* salvage, ai::State* prev);
    void leave(GfGameSalvage* salvage, ai::State* next);
    void update(GfGameSalvage* salvage, const fw::UpdateInfo& info);

    GfMenuCallContext* m_pContext;  // the result menu's (the name is not the original's)
};
}  // namespace gf

#endif
