#ifndef CLASSES_GF_PC_STATEFIELDWALLADSORPTIONUNDERGROUND_H
#define CLASSES_GF_PC_STATEFIELDWALLADSORPTIONUNDERGROUND_H

#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68FD8
class StateFieldWallAdsorptionUnderGround : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWallAdsorptionUnderGround; }
    virtual ~StateFieldWallAdsorptionUnderGround() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    float m_startBlend;   // enter's copy of the field property's m_wallBlend (the names are not the original's)
    unsigned char pad_1c[0x4];
    mm::Vec3 m_offset;    // enter: zero
    mm::Quat m_rot;       // enter: identity
};
}}  // namespace gf::pc

#endif
