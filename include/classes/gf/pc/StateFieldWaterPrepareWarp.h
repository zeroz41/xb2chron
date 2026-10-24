#ifndef CLASSES_GF_PC_STATEFIELDWATERPREPAREWARP_H
#define CLASSES_GF_PC_STATEFIELDWATERPREPAREWARP_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgPcFieldNotifyWarp; }

namespace gf { namespace pc {
// table 0x7100B69348
class StateFieldWaterPrepareWarp : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWaterPrepareWarp; }
    virtual ~StateFieldWaterPrepareWarp() {}  // slot 0: inline (the deleting destructor only frees the state)
    // slots 2-5 are inline (defined in StateFieldWaterNormal.cpp): recieveMessage is the key function, the
    // table and the inline slots are emitted with it in that unit
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // 1.0.0's (name from its symbols): recieveMessage inlines it; 3.0.1's linker dropped it
    void procMsgPcFieldNotifyWarp(GfComBehaviorPc* behavior, fw::MessageObject* sender, MsgPcFieldNotifyWarp& msg);
    // set once the warp notice came (procMsgPcFieldNotifyWarp; the name is not the original's)
    bool m_warpNotified;
    unsigned char pad_19[0x7];
};
}}  // namespace gf::pc

#endif
