#ifndef GF_GFSELECTIRA_H
#define GF_GFSELECTIRA_H

#include "gf/GfReqParam.h"

namespace fw { class UpdateInfo; }

namespace gf {
// 2.0.0's symbols name it (gf::GfSelectIra: its constructor, update, setupBattleStart, setupBattleEnd,
// restorePartyMember, isNeedResetBlade; 3.0.1 keeps update and restorePartyMember out of line and inlines the
// rest into GfGameParty's gevBattleStart, gevBattleEnd and isNeedResetBladeForIra). GfGameParty holds the one
// instance at 0x130 (2.0.0's constructor builds the RQ_SETUP_PARTY at 0 and clears the byte at 0x240).
class GfSelectIra {
public:
    GfSelectIra() : m_currentPartyValid(false) {}

    // 2.0.0's symbols name it. GfGameParty::update calls it; while m_currentPartyValid is set and no destroy, game
    // over, dead sequence, battle, map jump, event or fade is under way it works on the party
    void update(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. GfGameParty::gevPlayEvent calls it for GEV 10. What it does: unless
    // m_currentPartyValid is clear, fills a local RQ_SETUP_PARTY with GfGameParty::getCurrentPartyInfo and compares
    // it with m_currentParty, working on the members' objects through GfObjUtil::getObj.
    void restorePartyMember();

    RQ_SETUP_PARTY m_currentParty;  // what getCurrentPartyInfo fills (the name is not the original's)
    bool m_currentPartyValid;  // set once m_currentParty is filled (the name is not the original's)
};
}  // namespace gf

#endif
