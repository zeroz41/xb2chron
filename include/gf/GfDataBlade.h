#ifndef GF_GFDATABLADE_H
#define GF_GFDATABLADE_H

#include "gf/AchievQuest.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class SDataBlade; enum ActivateType : int; enum CLOUD_SEA : int; }
namespace gf { struct BladeArtsSlot; }
namespace gf { struct BladeSkillSlot; }
namespace gf { struct SDataIdea; }
namespace gf { class SDataGame; }
namespace gf { enum FAVORITE : int; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedArray; }}

namespace gf {

// a blade's affinity chart line: its quests by level (0x90 bytes; 1.0.0's GfDataBlade::setupAchievInfo names the
// class). The field names are not the original's.
struct AchievInfo {
    unsigned short m_achievementId;  // zero: the line has no chart (setupAchievInfo fills it only when set)
    unsigned char pad_2[0x2];
    AchievQuest m_quests[5];
};

// the blades' game data (functions, by its symbols)
class GfDataBlade {
public:
    // the blade's slot in the game data's blades (SDataGame::m_blades): the regular blades, then the rare ones,
    // then the common ones; 0 for any other id. Inline: every accessor carries its code (1.0.0's too), so the name
    // is not the original's.
    static unsigned int getBladeIndex(unsigned int blade) {
        if (blade - 1001 < 13) {
            return blade - 1001;
        }
        if (blade - 1014 < 176) {
            return blade - 994;
        }
        if (blade - 1197 < 226) {
            return blade - 1001;
        }
        return 0;
    }
    // the blade's creator (a 16-bit field of its SDataGame entry, 0x8A4 bytes each, at 0x5A2E)
    static int getCreator(unsigned int blade);
    // fills list with the party's blades (SCOM_ACHIEV_INC::createParty and createCrystal)
    static void getListPartyAll(mm::mtl::FixedVector<unsigned short, 422>& list);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions. What it does: GfGameFlag::getLocal of the game data's flags (GfDataManager::getDataGame
    // + 0xFBBC4), width 16, index 1; TUnk_B64F08::fn_71004944B8 compares it with 2000.
    static unsigned short fn_7100231884();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's fld plugin has no setNpcMeet). A
    // member because its address is in GfDataBlade's unit. What it does: for an id above 2000, looks the id up with
    // GfBdatRsc::fn_7100219CE0 and answers whether that local flag (type 1) is set; false otherwise. Callers: the fld
    // plugin's setNpcMeet (before and after fn_710024DDDC), GfMenuManager::fn_710035A764.
    static bool fn_710024DE6C(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit. What it does: for an id above 2000 with a GfBdatRsc::fn_7100219CE0 flag, sets that local
    // flag (type 1) to the bool; when the flag changed and fn_7100219C58 answers nonzero, records that value - 0xED02
    // in the first free one of the 256 type-8 local flags from 0x10C4 (unless already there). Caller: setNpcMeet (id, true).
    static void fn_710024DDDC(unsigned int id, bool set);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfGameUtil::setTrustPointForDebug
    // calls setTrustPoint instead). A member because it lives in GfDataBlade's unit among its functions (no this).
    // What it does: for drivers 17-25 only (else 0), GfBdatChrDr::getChrDrDefBlade(driver, 0) of the driver itself
    // (slot other than 0/1), or of the first (slot 0) / second (slot 1) id fn_71002416B4 lists for it, 0 when the
    // list is too short. GfGameUtil::setTrustPointForDebug passes (driver, -1) and adds the trust to the result.
    static unsigned int fn_7100237B70(unsigned int driver, int slot);
    // whether a blade is one of the dummy blades (ids 1012-1013, 1073, 1110, 1124-1132); the symbols spell it
    // fn_7100237D28, 1.0.0's GfGameUtil::isDummyBlade calls GfDataBlade::isDummyBlade at the same place
    static bool isDummyBlade(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: stores (cloudSea != 0) at 0x1C of the record fn_710024E1C8
    // returns for the map; GfGameUtilCloudSea::setInnCloudSea passes (GfGameManager::getMapID(), its cloud sea),
    // GfPlayComPlayerDead::update calls it too.
    static void fn_710024E8F4(unsigned int map, CLOUD_SEA cloudSea);
    // Placeholder name: nothing names it (1.0.0's GfGameUtil::execActivateMercenaryTeamForBlade calls
    // isActivateMercenaryTeam at its place, but 3.0.1 keeps that function at 0x71002398D8, reading another field).
    // A member because it lives in GfDataBlade's unit among its functions (no this). What it does: false for blade 0,
    // else whether the short at 0x5A2C of the blade's game data slot (getDataGame + slot * 0x8A4, the slot mapping
    // isActivateMercenaryTeam uses) is 2; execActivateMercenaryTeamForBlade does nothing when it holds.
    static bool fn_71002383C8(unsigned int blade);
    static ActivateType getBladeActivateType(const SDataBlade& blade);
    static bool isActivateReserver(unsigned int blade);
    static bool setActivateReserver(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: sets local game flag 0xBDCD (width 1) of the game data's
    // GameFlag (game + 0xFBBC4) to flag; GfGameUtil::incGameClearCount passes getDataGame() and true.
    static void fn_71002320AC(SDataGame* game, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: counts an enemy (arrange id) up by one: below 1500 local
    // flag type 0x10 (16 bits) index enemy + 0x2E, else the short at 0x11C084 + enemy * 2 of the game data; capped
    // at 0xFFFF; false for enemy 0 or a full count, else true. GfGameUtil::incEnemySuppress passes its enemy.
    static bool fn_7100234998(unsigned int enemy);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: the count fn_7100234998 raises (0 for enemy 0);
    // GfGameUtil::incEnemySuppress, GmkEnemyInsts::PopInfo and GmkGrave::update read it.
    static unsigned int fn_7100234940(unsigned int enemy);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: counts local game flag type 8 index 0x874 up by one, up to
    // 0xFF (GfGameFlag::getLocal/setLocal); GfGameUtil::incEnemySuppress calls it for a named enemy counted the
    // first time.
    static void fn_71002355AC();
    static bool getTaskSkillMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line);
    static bool getTaskResultMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                     unsigned int level);
    static unsigned int getSkillLineId(unsigned int blade, unsigned int line);
    // whether the blade is in the battle party (1.0.0's GfQuestInfo::incSuppressCount calls it on the quest's blade)
    static bool isBattleMember(unsigned int blade);
    static unsigned int getKizunaringCompleteNum(unsigned int blade);
    static unsigned int getKizunaringMax(unsigned int blade);
    // the scale of a blade's weapon (GfGameMount::attach scales the weapon's models by it at option 3)
    static float getWpnScale(unsigned int blade);
    static bool isRareBlade(unsigned int blade);
    // a game flag: Pyra's name shown as Mythra's (GfMenuObjNameSelect sets it from the name picked)
    static void setHomuriNameHikari(bool hikari);
    static bool isHomuriNameHikari();  // the flag setHomuriNameHikari sets (local flag 0x89FB, 1 bit)
    static bool isActivateUnuse(unsigned int blade);
    static bool isUnselect(unsigned int blade);
    // the driver the blade is set to, 0 for none
    static unsigned int getSetDriver(unsigned int blade);
    static AchievInfo* getAchievInfo(unsigned int blade, unsigned int line);
    // the blades with an affinity chart
    static void getListForAchievement(mm::mtl::FixedVector<unsigned short, 422>& list);
    static unsigned int getKeyReleaseLevel(unsigned int blade);
    static void setSkillLineLevel(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getBladeWpnType(unsigned int blade);
    static const char* getName(unsigned int blade, unsigned int kind);
    // the message table and row of the blade's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    static unsigned int getQuestRace(unsigned int blade);
    static SDataBlade* getSDataBlade(unsigned int blade);
    static unsigned int getHpMaxRev(unsigned int blade);
    static unsigned int getStrengthRev(unsigned int blade);
    static unsigned int getPowerEtherRev(unsigned int blade);
    static unsigned int getDexRev(unsigned int blade);
    static unsigned int getAgilityRev(unsigned int blade);
    static unsigned int getLuckRev(unsigned int blade);
    static bool getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>& orbs, unsigned int blade);
    static unsigned int getFootStep(unsigned int blade);
    static unsigned int getFootStepEffect(unsigned int blade);
    static unsigned int getRole(unsigned int blade);
    static const char* getVoiceStr(unsigned int blade);
    static const BladeArtsSlot* getArts(unsigned int blade, unsigned int index);
    static unsigned int getArtsEnhance(unsigned int blade, unsigned int index);
    static const BladeArtsSlot* getNArts(unsigned int blade, unsigned int index);
    static unsigned int getFavorite(unsigned int blade, FAVORITE favorite);
    static int getOffsetID(unsigned int blade);  // its menu offset id
    static unsigned int getBladePower(unsigned int blade);
    static bool isMale(unsigned int blade);
    static bool isFemale(unsigned int blade);
    static bool isAnimal(unsigned int blade);
    static unsigned int getAttribute(unsigned int blade);
    static bool getExtraParts(const SDataBlade& data, unsigned int part);
    static unsigned int getBladePower(SDataBlade& data);
    static unsigned int getRoleByWpnType(unsigned int wpnType);
    static bool isHikariCurrent();
    static void setHikariCurrent(bool value);
    static unsigned int getStartCommonBlade();
    static unsigned int getEndCommonBlade();
    static unsigned int getStartUiCommonBlade();
    static bool isCommonBlade(unsigned int blade);
    static bool isRegularBlade(unsigned int blade);
    static bool isValid(unsigned int blade);
    static bool isBladeID(unsigned int blade);
    static bool isNeedChangeWeapon(unsigned int blade);
    static unsigned int getActBlade2CommonBlade(unsigned int blade);
    static bool isEnableEngageRex(unsigned int blade);
    static unsigned int getBornTime(unsigned int blade);
    static SDataIdea* getSDataIdea(unsigned int blade);
    static bool isAttachedParty(unsigned int blade);
    static bool isActivateDriver(unsigned int blade);
    static const char* getResourceNameModel(unsigned int blade);
    static bool isKizunaringComplete(unsigned int blade);
    static bool isReleasedRareBlade(unsigned int blade);
    static unsigned int getTrustRank(unsigned int blade);
    static bool isSetBlade(unsigned int blade);
    static unsigned int getBladeWeapon(unsigned int blade);
    static const char* getResourceNameMotion(unsigned int blade);
    static const char* getResourceNameAddMotion(unsigned int blade);
    static unsigned int getRace(unsigned int blade);
    static float getScale(unsigned int blade);
    static unsigned int getSize(unsigned int blade);
    static unsigned int getEquipOrbMax(unsigned int blade);
    // the orb in a blade's slot (GfEquipUtil::getEquipBladeOrb returns it, zero-extended)
    static unsigned short getEquipOrb(unsigned int blade, unsigned int slot);
    static unsigned int getCreateEvent(unsigned int blade);
    static unsigned int getNormalTalk(unsigned int blade);
    static unsigned int getTrustPoint(unsigned int blade);
    static bool isReleaseLock(unsigned int blade);
    static const char* getSePack(unsigned int blade);
    static void setEnableEngageRex(unsigned int blade, bool enable);
    static void setKizunaringComplete(unsigned int blade);
    static bool setActivateMercenaryTeam(unsigned int blade);
    static void setBladeWeapon(unsigned int blade, unsigned int weapon);
    // the weapon a blade gets from a weapon chip (GfEquipUtil::equipBladeChip sets it)
    static unsigned int getBladeWeaponByRank(unsigned int blade, unsigned int chip);
    static void setUnselect(unsigned int blade, bool unselect);
    static void setTrustPoint(unsigned int blade, unsigned int point);
    static bool getExtraParts(unsigned int blade, unsigned int part);
    static const BladeSkillSlot* getSkill(unsigned int blade, unsigned int index);
    // (appended by chardata) 1.0.0's name: its GfMenuCharDataAdapter::update_BL_InMercenry calls it at the same site
    // (the symbols call it fn_71002398D8)
    static bool isActivateMercenaryTeam(unsigned int blade);
    static bool isNeedAttributeResource(unsigned int blade);
    // the reserve blades (GfDataMercenaries::getReserver fills its list with them)
    static void getListReserver(mm::mtl::FixedVector<unsigned short, 422>& list);
    static unsigned int getBladeRelativeID(unsigned int blade);  // getBladeIndex
};

}  // namespace gf

#endif
