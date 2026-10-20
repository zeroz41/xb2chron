#ifndef CLASSES_GF_PC_AGENT_H
#define CLASSES_GF_PC_AGENT_H

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table none (its derived classes')
class Agent {
public:
    virtual void getRTTI() const = 0;  // slot 0
    virtual ~Agent();  // slot 1
    virtual void setup(gf::GfComPropertyPc&) = 0;  // slot 3
    virtual void cleanup(gf::GfComPropertyPc&) = 0;  // slot 4
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&) = 0;  // slot 5
    virtual void testFiledAI() const;  // slot 6
    virtual void setFieldAI(gf::GfComPropertyPc&, bool);  // slot 7
    virtual void testBattleAI() const;  // slot 8
    virtual void setBattleAI(gf::GfComPropertyPc&, bool);  // slot 9
    virtual void recieveMessage(gf::GfComPropertyPc&, fw::MessageObject*, fw::Message&);  // slot 10
};
}}  // namespace gf::pc

#endif
