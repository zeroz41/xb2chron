#ifndef GF_GFARENAUTIL_H
#define GF_GFARENAUTIL_H

#include "gf/ArenaBattleStart.h"
#include "gf/ArenaChanged.h"
#include "gf/ArenaMenuInfo.h"
#include "gf/ChBtlInfo.h"
#include "gf/SaveChBtl.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gf {

// 2.0.0's symbols name it and its functions (all static: none reads an object of its own). The arena's helpers; their
// code is in unit_710028EBB0's, GfDataBlade_710029064C's and unit_7100290CC4's ranges.
class GfArenaUtil {
public:
    // GfGameArena::getMenuInfo calls it on the record with the challenge id. What it does: clears the record and fills
    // its header from GfBdatBtl's row for the id.
    static void setupMenuInfoForChBtl(ArenaMenuInfo& info, unsigned int id);
    // GfArenaBattle::procMsgGameBtlArena calls them on its m_best (+0xB0) with the arena's record. What they do:
    // setupMenuInfoForCube keeps a larger value in m_value8, sets the record's m_value2C to the value and its
    // m_ratios from GfBdatBtl's getBTL_ChBtlTresureNeed thresholds 0..2; setupMenuInfoForScore keeps a larger value in
    // m_value4 and sets the record's m_value28; setupMenuInfoForClearTime keeps a smaller one in m_value0 (0 counts as
    // none) and sets the record's m_value30.
    static void setupMenuInfoForCube(ChBtlInfo::ChBtlDiff& diff, ArenaMenuInfo& info, unsigned int value);
    static void setupMenuInfoForScore(ChBtlInfo::ChBtlDiff& diff, ArenaMenuInfo& info, unsigned int value);
    static void setupMenuInfoForClearTime(ChBtlInfo::ChBtlDiff& diff, ArenaMenuInfo& info, unsigned int value);
    // GfGameArena::setupGame calls it on SDataGame's table with the arena's m_ids.
    static void setupSaveData(SaveChBtl& save, const ::mm::mtl::FixedVector<unsigned short, 128>& ids);
    // StateArenaField's onEnter calls it on SDataGame's table with the arena's m_ids. What it does: for each id's row,
    // sets m_flag3E once GfGameCond::isGameCond(GfBdatBtl::getBTL_ChBtlCondition(id)) holds; a row without m_flag3C
    // gets m_flag3C and m_flag3E then and the id goes to createChBtlNewChallenge.
    static void applyChallengeStatus(SaveChBtl& save, const ::mm::mtl::FixedVector<unsigned short, 128>& ids);
    // It fills the arena's m_ids (called only by the arena's initialize). What it does: clears the vector, then pushes
    // every ID from GfBdatBtl::getBTL_ChBtlStart() up to (not including) GfBdatBtl::getBTL_ChBtlEnd().
    static void setupChBtlList(::mm::mtl::FixedVector<unsigned short, 128>& ids);
    // GfGameArena::procMsgGameBtlArena calls it on SDataGame's table (0x11A8CC) with the message's id. What it does:
    // stores 2 in the row's m_flag3C.
    static void setChallengeOK(SaveChBtl& save, unsigned int id);
    // GfGameArena::getMenuInfo calls both on the record's lists with its ArenaBattleStart. What they do:
    // setupLevelForBattleStart clears m_list38 and fills it from GfBdatBtl's rows for the start's id,
    // setupRankForBattleStart the same for m_listE0.
    static void setupLevelForBattleStart(ArenaChanged& changed, const ArenaBattleStart& start);
    static void setupRankForBattleStart(ArenaChanged& changed, const ArenaBattleStart& start);
    // setupRankForBattleStart and GfArenaParty::getWeaponDamage call it with a blade ID. What it does: reads
    // GfBdatBtl's rows for the start's id against the blade's weapon rank and weapon type.
    static unsigned int getWeaponDamage(const ArenaBattleStart& start, unsigned int blade);
    // GfGameArena::procMsgGameBtlArena tail-calls it with message type 0x13's pad_40. What it does: finds the
    // GfBdatBtl challenge whose condition (type 0xD) resolves to the value and, unless its row's m_flag3E is set, sets
    // it and shows SCOM_POPUP::createChBtlNewChallenge.
    static void createPopupForKillEnemy(unsigned int value);
    // GfArenaBattle::mapjumpForBattleStart calls it with the BTL_ChBtl row id. What it does: when GfBdatBtl's
    // getBTL_ChBtlMapJump gives the row's map, sets that map's WeatherParam weather id from getBTL_ChBtlWeather (+1, at
    // most 5), time 0, length 100.
    static void setupBattleMapWeather(unsigned int id);
    // GfGameArena::procMsgGameBtlArena (message type 13) and StateArenaEvent test it against 0. What it does: the
    // BTL_ChBtl row's Event (GfBdatBtl::getBTL_ChBtlEvent); 0 for id 0.
    static unsigned int getPlayEvent(unsigned int id);
    // GfGameArena::procMsgGameBtlArena calls them on SDataGame's rows with the message's id. What they do: isPlayEvent
    // answers bit 1 of byte 10 of row id (0 for id 0), setPlayEvent sets that bit (not for id 0).
    static void setPlayEvent(::mm::mtl::FixedArray<ChBtlInfo, 48>& infos, unsigned int id);
    static bool isPlayEvent(const ::mm::mtl::FixedArray<ChBtlInfo, 48>& infos, unsigned int id);
};

}  // namespace gf

#endif
