#ifndef GF_PC_AIAGENTFIELD_H
#define GF_PC_AIAGENTFIELD_H

namespace fw { class Message; }
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

    alignas(8) unsigned char pad_0[0x90];  // fields: AIAgent's layout gives the size, the pointer at 0 the alignment
};

}}  // namespace gf::pc

#endif
