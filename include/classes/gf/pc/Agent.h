#ifndef CLASSES_GF_PC_AGENT_H
#define CLASSES_GF_PC_AGENT_H

#include "mm/mtl/RTTI.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table none (its derived classes')
class Agent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;  // slot 0
    virtual ~Agent();  // slot 1
    virtual void setup(gf::GfComPropertyPc&) = 0;  // slot 3
    virtual void cleanup(gf::GfComPropertyPc&) = 0;  // slot 4
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&) = 0;  // slot 5
    virtual bool testFiledAI() const { return false; }  // slot 6
    virtual void setFieldAI(gf::GfComPropertyPc&, bool) {}  // slot 7
    virtual bool testBattleAI() const { return false; }  // slot 8
    virtual void setBattleAI(gf::GfComPropertyPc&, bool) {}  // slot 9
    virtual bool recieveMessage(gf::GfComPropertyPc&, fw::MessageObject*, fw::Message&) { return false; }  // slot 10
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
