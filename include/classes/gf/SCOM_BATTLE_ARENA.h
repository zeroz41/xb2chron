#ifndef CLASSES_GF_TUNK_B6AD28_H
#define CLASSES_GF_TUNK_B6AD28_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B6AD28 (no RTTI name): a type-0x55 request whose exec sends the arena game mode (GfGameArena) a
// MsgGameBtlArena carrying m_type and m_param; five create placeholders queue it with a fixed type and parameter 0
class SCOM_BATTLE_ARENA : public ::gf::SCOM {
public:
    explicit SCOM_BATTLE_ARENA(unsigned int type) : SCOM(SCOM_TYPE(0x55)), m_type(type), m_param(0) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long createWin();
    static unsigned long createLose();
    static unsigned long createRetry();
    static unsigned long createGiveUp();
    static unsigned long createLoseStart();
    // 2.0.0's symbols name the next three. When the arena exists, sends it MsgGameBtlArena type 0x12 with a and b
    // in pad_34/pad_38 and id in pad_3C. Caller: btl::ChallengeBattleManager::UpdateProc
    static void createPlayJingle(unsigned int id, float a, float b);
    // GfGameVoice::playVoice(6, 0xDC3, table 0x7100B6AD58[row][ml::mtRand(4)], CV_PRIO 3).
    // Caller: GfArenaReward::playVoice
    static void createAfterVoice(unsigned int row);
    // for the first count handles that are valid drivers of BDAT id 1..6 or 9, plays one of two voices from tables
    // at 0x7100B6ADD8. Caller: GfArenaReward::playReturnVoice
    static void createReturnVoice(GF_OBJ_HANDLE** handles, unsigned int count, bool flag);

    // the names are not the original's: the message's type and its first parameter word
    unsigned int m_type;
    unsigned int m_param;
};
}  // namespace gf

#endif
