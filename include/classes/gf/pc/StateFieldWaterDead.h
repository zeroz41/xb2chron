#ifndef CLASSES_GF_PC_STATEFIELDWATERDEAD_H
#define CLASSES_GF_PC_STATEFIELDWATERDEAD_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgObjectNotifyHealHp; }
namespace gf { class MsgPcFieldRelaySurvive; }

namespace gf { namespace pc {
// table 0x7100B69398
class StateFieldWaterDead : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWaterDead; }
    virtual ~StateFieldWaterDead() {}  // slot 0: inline (the deleting destructor only frees the state)
    // slots 2-5 are inline (defined in StateFieldWaterNormal.cpp): recieveMessage is the key function, the
    // table and the inline slots are emitted with it in that unit
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own function; onEnter hands it the owner (1.0.0's name; 3.0.1's linker dropped it: the slot
    // inlines it)
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    // 1.0.0's (names from its symbols): recieveMessage inlines both procMsg functions; 3.0.1's linker dropped them
    void onAlive(GfComBehaviorPc* behavior, MsgObjectNotifyHealHp& msg);
    void procMsgObjectNotifyHealHp(GfComBehaviorPc* behavior, fw::MessageObject* sender, MsgObjectNotifyHealHp& msg);
    void procMsgPcFieldRelaySurvive(GfComBehaviorPc* behavior, fw::MessageObject* sender, MsgPcFieldRelaySurvive& msg);
};
}}  // namespace gf::pc

#endif
