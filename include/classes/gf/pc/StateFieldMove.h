#ifndef CLASSES_GF_PC_STATEFIELDMOVE_H
#define CLASSES_GF_PC_STATEFIELDMOVE_H

#include "mm/mtl/FixedQueue.h"
#include "mm/Vec2.h"
#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B68628
class StateFieldMove : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldMove; }
    virtual ~StateFieldMove() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    unsigned char pad_18[0x8];
    // the stick's recent directions update hands StateUtilField::isTurnRange (the name is not the original's)
    mm::mtl::FixedQueue<mm::Vec2, 2> m_inputQueue;
};
}}  // namespace gf::pc

#endif
