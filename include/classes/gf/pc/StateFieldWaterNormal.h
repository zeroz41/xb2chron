#ifndef CLASSES_GF_PC_STATEFIELDWATERNORMAL_H
#define CLASSES_GF_PC_STATEFIELDWATERNORMAL_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgObjectNotifyDead; }
namespace gf { class MsgPcFieldRelaySurvive; }
namespace gf { class MsgPcFieldWaterWarp; }
namespace gf { class MsgPcFieldWaterWarpBuddy; }

namespace gf { namespace pc {
// table 0x7100B692A8
class StateFieldWaterNormal : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWaterNormal; }
    virtual ~StateFieldWaterNormal() {}  // slot 0: inline (the deleting destructor only frees the state)
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
    // 1.0.0's (names from its symbols): recieveMessage inlines all but procMsgObjectNotifyDead; 3.0.1's linker
    // dropped the others
    void onDead(GfComBehaviorPc* behavior, MsgObjectNotifyDead& msg);
    void procMsgPcFieldWaterWarp(GfComBehaviorPc* behavior, fw::MessageObject* sender, MsgPcFieldWaterWarp& msg);
    void procMsgPcFieldWaterWarpBuddy(GfComBehaviorPc* behavior, fw::MessageObject* sender,
                                      MsgPcFieldWaterWarpBuddy& msg);
    void procMsgObjectNotifyDead(GfComBehaviorPc* behavior, fw::MessageObject* sender, MsgObjectNotifyDead& msg);
    void procMsgPcFieldRelaySurvive(GfComBehaviorPc* behavior, fw::MessageObject* sender, MsgPcFieldRelaySurvive& msg);
};
}}  // namespace gf::pc

#endif
