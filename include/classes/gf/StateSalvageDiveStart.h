#ifndef CLASSES_GF_STATESALVAGEDIVESTART_H
#define CLASSES_GF_STATESALVAGEDIVESTART_H

#include "classes/ai/State.h"

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfGameSalvage; }
namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B57268
class StateSalvageDiveStart : public ::ai::State {
public:
    virtual ~StateSalvageDiveStart();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions (out of line, in StateSalvageDiveStart's unit); the slots above hand them the game
    void enter(GfGameSalvage* salvage, ai::State* prev);
    void leave(GfGameSalvage* salvage, ai::State* next);
    void update(GfGameSalvage* salvage, const fw::UpdateInfo& info);
    // what GfComBehaviorSalvage calls on its animation's steps while the state is on
    void callback();

    // the button challenges: their menus' contexts, how many began, the current one's id, how many went well and
    // their ids (the names are not the original's)
    GfMenuCallContext* m_pContexts[3];
    int m_count;
    int m_currentId;
    int m_successCount;
    int m_ids[3];
};
}  // namespace gf

#endif
