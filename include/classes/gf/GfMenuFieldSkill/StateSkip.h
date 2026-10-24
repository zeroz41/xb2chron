#ifndef CLASSES_GF_GFMENUFIELDSKILL_STATESKIP_H
#define CLASSES_GF_GFMENUFIELDSKILL_STATESKIP_H

#include <new>

#include "classes/ai/State.h"
#include "classes/gf/GfMenuFieldSkill.h"

namespace ai { class State; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5E7C0
class GfMenuFieldSkill::StateSkip : public ::ai::State {
public:
    // what GfMenuFieldSkill::build registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateSkip; }
    virtual ~StateSkip() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the menu
    void update(GfMenuFieldSkill* menu, const fw::UpdateInfo& info);

    unsigned int m_step;  // 0x18: onEnter clears it (the name is not the original's)
};
}  // namespace gf

#endif
