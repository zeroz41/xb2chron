#ifndef CLASSES_GF_PC_STATEFIELDMOVECOMMON_H
#define CLASSES_GF_PC_STATEFIELDMOVECOMMON_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B685D8
class StateFieldMoveCommon : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldMoveCommon; }
    virtual ~StateFieldMoveCommon() {}  // slot 0: inline (the deleting destructor only frees the state)
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // update counts the frames without stick input (0 while there is some) and hands the count to
    // StateUtilField::isStop; enter clears it (the name is not the original's)
    unsigned int m_noInputFrames;
    unsigned char pad_1c[0x4];
};
}}  // namespace gf::pc

#endif
