#ifndef CLASSES_GF_PC_AIAGENT_H
#define CLASSES_GF_PC_AIAGENT_H

#include "classes/gf/pc/Agent.h"
#include "gf/pc/AIAgentBattle.h"
#include "gf/pc/AIAgentField.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B69480
class AIAgent : public ::gf::pc::Agent {
public:
    AIAgent();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~AIAgent();  // slot 1
    virtual void setup(gf::GfComPropertyPc& property);  // slot 3
    virtual void cleanup(gf::GfComPropertyPc& property);  // slot 4
    virtual void update(fw::UpdateInfo const& info, gf::GfComPropertyPc& property);  // slot 5
    virtual bool testFiledAI() const { return m_aiFlags & 1; }  // slot 6
    virtual void setFieldAI(gf::GfComPropertyPc& property, bool enable);  // slot 7
    virtual bool testBattleAI() const { return (m_aiFlags >> 1) & 1; }  // slot 8
    virtual void setBattleAI(gf::GfComPropertyPc& property, bool enable);  // slot 9
    virtual bool recieveMessage(gf::GfComPropertyPc& property, fw::MessageObject* sender,
                                fw::Message& message) {  // slot 10
        if (testFiledAI()) {
            return m_field.recieveMessage(property, sender, message);
        }
        return false;
    }

    static mm::mtl::RTTI m_rtti;
    unsigned int m_aiFlags;  // bit 0: the field AI runs (testFiledAI), bit 1: the battle AI runs (testBattleAI)
    AIAgentField m_field;
    AIAgentBattle m_battle;
};
}}  // namespace gf::pc

#endif
