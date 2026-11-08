#ifndef CLASSES_GF_PC_STATEFIELDONWALL_H
#define CLASSES_GF_PC_STATEFIELDONWALL_H

#include "classes/gf/GfStateBase.h"
#include "gf/EnviromentSensor.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgPcFieldWallJump; }

namespace gf { namespace pc {
// table 0x7100B68268
class StateFieldOnWall : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldOnWall; }
    virtual ~StateFieldOnWall() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: recieveMessage is the key function (the unit emits the table and these slots' weak copies)
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void leave(GfComBehaviorPc* behavior, ai::State* next);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    // the message recieveMessage hands on (1.0.0's symbol; 3.0.1 inlines it, its linker dropped the copy)
    void procMsgPcFieldWallJump(GfComBehaviorPc* behavior, fw::MessageObject* from, MsgPcFieldWallJump& msg);
    unsigned char pad_18[0x8];
    // enter's copy of the field property's wall, the plane leave tells the wall's children of (the name is not the
    // original's)
    gf::EnviromentSensor::WallInfo m_wallInfo;
};
}}  // namespace gf::pc

#endif
