#ifndef CLASSES_GF_PC_STATEFIELDTALK_H
#define CLASSES_GF_PC_STATEFIELDTALK_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MsgGameTalkAction; }
namespace gf { class MsgGameLipAction; }

namespace gf { namespace pc {
// table 0x7100B680D8
class StateFieldTalk : public ::gf::GfStateBase {
public:
    // what registerFieldStates registers with the player's Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldTalk; }
    virtual ~StateFieldTalk() {}  // slot 0: inline (the deleting destructor only frees the state)
    // inline: its slot is emitted with the class's table (the key function is recieveMessage)
    virtual inline const char* getName() const;  // slot 2
    virtual inline void onEnter(void*, ai::State*);  // slot 3
    // inline: the original's slot holds the state's own code (ends the talk)
    virtual inline void onLeave(void*, ai::State*);  // slot 4
    virtual inline void onStep(void*, void const*);  // slot 5
    virtual bool recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    // the state's own functions; the slots above hand them the owner
    void enter(GfComBehaviorPc* behavior, ai::State* prev);
    void update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info);
    void procMsgGameTalkAction(GfComBehaviorPc* behavior, fw::MessageObject* from, gf::MsgGameTalkAction& msg);
    void procMsgGameLipAction(GfComBehaviorPc* behavior, fw::MessageObject* from, gf::MsgGameLipAction& msg);
    // the object talked to: onLeave tells it the PC's action ended (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_target;
};
}}  // namespace gf::pc

#endif
