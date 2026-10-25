#ifndef CLASSES_GF_PC_STATEFIELDWALLADSORPTIONAIR_H
#define CLASSES_GF_PC_STATEFIELDWALLADSORPTIONAIR_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68F88
class StateFieldWallAdsorptionAir : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWallAdsorptionAir; }
    virtual ~StateFieldWallAdsorptionAir() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // the PC field parameter list's entry 15 as update reads it (the names are not the original's)
    struct Param {
        unsigned char pad_0[0x14];
        float m_blendTime;  // update blends m_wallBlend to its target over it
    };

    float m_time;         // update adds the frame time; enter zeroes it (the name is not the original's)
    float m_startBlend;   // enter's copy of the field property's m_wallBlend (the name is not the original's)
};
}}  // namespace gf::pc

#endif
