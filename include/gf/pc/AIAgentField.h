#ifndef GF_PC_AIAGENTFIELD_H
#define GF_PC_AIAGENTFIELD_H

#include "ai/BehaviorTree.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class Message; }
namespace fw { class ParamList; }
namespace navi { class NvmshAcObj; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }
namespace gf { class MsgPcFieldNotifyWall; }
namespace gf { class MsgPcFieldNotifyHighJump; }
namespace gf { class MsgPcFieldNotifyWaterWarp; }
namespace gf { class MsgPcFieldNotifyWaterWarpBuddy; }
namespace gf { class MsgPcFieldNotifyWallJumpStart; }

namespace gf { namespace pc {

// the field half of a character's AI (AIAgent's)
class AIAgentField {
public:
    AIAgentField();
    ~AIAgentField();
    void setup(gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);
    void update(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);
    void onActivate(gf::GfComPropertyPc& property);
    void onDeactivate(gf::GfComPropertyPc& property);
    bool recieveMessage(gf::GfComPropertyPc& property, fw::MessageObject* sender, fw::Message& message);
    void procMsgPcFieldNotifyWall(fw::MessageObject* sender, gf::MsgPcFieldNotifyWall& msg);
    void procMsgPcFieldHighJump(fw::MessageObject* sender, gf::MsgPcFieldNotifyHighJump& msg);
    void procMsgPcFieldNotifyWaterWarp(fw::MessageObject* sender, gf::MsgPcFieldNotifyWaterWarp& msg);
    void procMsgPcFieldNotifyWaterWarpBuddy(fw::MessageObject* sender, gf::MsgPcFieldNotifyWaterWarpBuddy& msg);
    // (2.0.0 has it out of line; 3.0.1's recieveMessage inlines it)
    void procMsgPcFieldNotifyWallJumpStart(fw::MessageObject* sender, gf::MsgPcFieldNotifyWallJumpStart& msg);

    // the field names are not the original's
    navi::NvmshAcObj* m_nvmshAcObj;  // setup's, from fw::NaviManager::createObject
    ai::BehaviorTree m_tree;           // the field AI's behavior tree, built by setup
    // the field AI's parameter list (fw::ParamManager's 16th), held while the AI is set up
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;
};

}}  // namespace gf::pc

#endif
