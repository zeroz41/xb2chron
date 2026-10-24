#ifndef CLASSES_GF_PC_STATEFIELDWATERSINK_H
#define CLASSES_GF_PC_STATEFIELDWATERSINK_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68B28
class StateFieldWaterSink : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWaterSink; }
    virtual ~StateFieldWaterSink() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // the time spent in the state: update adds each frame's delta (the name is not the original's)
    float m_time;
    unsigned char pad_1c[0x4];
};
}}  // namespace gf::pc

#endif
