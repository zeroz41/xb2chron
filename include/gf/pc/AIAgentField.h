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

    // the field names are not the original's
    navi::NvmshAcObj* m_nvmshAcObj;  // setup's, from fw::NaviManager::createObject
    ai::BehaviorTree m_tree;           // the field AI's behavior tree, built by setup
    // the field AI's parameter list (fw::ParamManager's 16th), held while the AI is set up
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;
};

}}  // namespace gf::pc

#endif
