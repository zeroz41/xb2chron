#ifndef CLASSES_GF_PC_AIAGENT_H
#define CLASSES_GF_PC_AIAGENT_H

#include "mm/mtl/RTTI.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B69480
class AIAgent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~AIAgent();  // slot 1
    virtual void setup(gf::GfComPropertyPc&);  // slot 3
    virtual void cleanup(gf::GfComPropertyPc&);  // slot 4
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 5
    virtual void testFiledAI() const;  // slot 6
    virtual void setFieldAI(gf::GfComPropertyPc&, bool);  // slot 7
    virtual void testBattleAI() const;  // slot 8
    virtual void setBattleAI(gf::GfComPropertyPc&, bool);  // slot 9
    virtual void recieveMessage(gf::GfComPropertyPc&, fw::MessageObject*, fw::Message&);  // slot 10
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
