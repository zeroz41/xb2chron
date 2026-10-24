#ifndef CLASSES_GF_GFMENUFIELDSKILL_STATEDISPTOTAL_H
#define CLASSES_GF_GFMENUFIELDSKILL_STATEDISPTOTAL_H

#include <new>

#include "classes/ai/State.h"
#include "classes/gf/GfMenuFieldSkill.h"

namespace ai { class State; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5E6A0
class GfMenuFieldSkill::StateDispTotal : public ::ai::State {
public:
    // what GfMenuFieldSkill::build registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateDispTotal; }
    virtual ~StateDispTotal() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the menu
    void enter(GfMenuFieldSkill* menu, ai::State* prev);
    void update(GfMenuFieldSkill* menu, const fw::UpdateInfo& info);
};
}  // namespace gf

#endif
