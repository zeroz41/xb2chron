#ifndef CLASSES_GF_GFGAMETARGET_STATEENEMYTARGET_H
#define CLASSES_GF_GFGAMETARGET_STATEENEMYTARGET_H

#include "classes/ai/State.h"
#include "classes/gf/GfGameTarget.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B56A20
class GfGameTarget::StateEnemyTarget : public ::ai::State {
public:
    static ai::State* create(void* buffer) { return new (buffer) StateEnemyTarget(); }
    virtual ~StateEnemyTarget() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    void update(GfGameTarget* owner, const fw::UpdateInfo& info);
};
}  // namespace gf

#endif
