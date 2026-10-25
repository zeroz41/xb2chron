#ifndef CLASSES_GF_PC_STATEFIELDWATERIDLETURN_H
#define CLASSES_GF_PC_STATEFIELDWATERIDLETURN_H

#include "classes/gf/GfStateBase.h"
#include "mm/Vec3.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68A38
class StateFieldWaterIdleTurn : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWaterIdleTurn; }
    virtual ~StateFieldWaterIdleTurn() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    unsigned char pad_18[0x8];
    // the direction to turn to: enter sets it from the stick (else the move direction), update turns along it
    // until StateUtilField::isTurnEndRangeCacheInput (the name is not the original's)
    mm::Vec3 m_dir;  // 16 bytes on a 16-byte boundary: it ends the state at 0x30
};
}}  // namespace gf::pc

#endif
