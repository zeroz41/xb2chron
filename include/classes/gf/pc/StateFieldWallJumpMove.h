#ifndef CLASSES_GF_PC_STATEFIELDWALLJUMPMOVE_H
#define CLASSES_GF_PC_STATEFIELDWALLJUMPMOVE_H

#include "classes/gf/GfStateBase.h"
#include "mm/Vec3.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B69208
class StateFieldWallJumpMove : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWallJumpMove; }
    virtual ~StateFieldWallJumpMove() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // enter's: the jump's time so far and its length (the distance over WallParam's m_jumpSpeed), where it lands (the
    // notice's position, lowered by m_climbJumpHeight, off the wall) and where it starts (the PC's position);
    // update moves the PC between them (the names are not the original's)
    float m_time;
    float m_duration;
    mm::Vec3 m_target;
    mm::Vec3 m_start;
};
}}  // namespace gf::pc

#endif
