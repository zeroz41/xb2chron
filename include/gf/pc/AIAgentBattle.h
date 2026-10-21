#ifndef GF_PC_AIAGENTBATTLE_H
#define GF_PC_AIAGENTBATTLE_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {

// the battle half of a character's AI (AIAgent's)
class AIAgentBattle {
public:
    AIAgentBattle();
    ~AIAgentBattle();
    void setup(gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);
    void update(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);

    alignas(8) unsigned char pad_0[0x8];  // fields: its constructor clears a pointer at 0
};

}}  // namespace gf::pc

#endif
