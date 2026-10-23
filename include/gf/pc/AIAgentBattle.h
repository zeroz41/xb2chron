#ifndef GF_PC_AIAGENTBATTLE_H
#define GF_PC_AIAGENTBATTLE_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }
namespace navi { class NvmshAcObj; }

namespace gf { namespace pc {

// the battle half of a character's AI (AIAgent's)
class AIAgentBattle {
public:
    AIAgentBattle();
    ~AIAgentBattle();
    void setup(gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);
    void update(const fw::UpdateInfo& info, gf::GfComPropertyPc& property);

    // setup's: the navigation object fw::NaviManager makes for it, released by cleanup (the name is not the original's)
    navi::NvmshAcObj* m_naviObject;
};

}}  // namespace gf::pc

#endif
