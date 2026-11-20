#ifndef GF_GFDATABLADE_H
#define GF_GFDATABLADE_H

#include "gf/AchievQuest.h"
#include "mm/mtl/FixedVector.h"
#include "gf/SDataWeather.h"

namespace gf { class SDataBlade; enum ActivateType : int; enum CLOUD_SEA : int; enum WEATYPE : int; enum WEATHERID : int; }
namespace gf { struct BladeArtsSlot; }
namespace gf { struct BladeSkillSlot; }
namespace gf { struct SDataIdea; }
namespace gf { class DataParamAcc; }
namespace gf { class SDataGame; }
namespace gf { struct GfItemHandle; }
namespace gf { enum FAVORITE : int; }
namespace gf { enum GfIdea : int; }  // the type of GfDataBlade::setTrustRank's rank (symbols)
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
    // fills an affinity chart quest from its chart (GfQuestTask::setupOrderTask passes GfDataQuest::getAchievQuest's)
    static void setupAchievQuest(AchievQuest& quest);
    // the ids of the blades with field skills (GfFieldCollect::seqWaitDo checks each one's skills)
    static void getListForFieldSkill(mm::mtl::FixedVector<unsigned short, 422>& list);
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
    // 1.0.0's setCreator (0x71002959B0, called by 1.0.0's pt setBladeCreator with its two script arguments); it
    // sits next to getCreator and stores that 16-bit field (and a second copy for blade 1050)
    static void setCreator(unsigned int blade, unsigned int creator);
    static unsigned int getBladeID(unsigned int index);  // the blade in list slot index (0..421), 0 for none
    // fills list with the party's blades (SCOM_ACHIEV_INC::createParty and createCrystal)
    // whether the list is not empty
    static bool getListPartyAll(mm::mtl::FixedVector<unsigned short, 422>& list);
    // fills list with the party's blades (the flags' meaning is not known: GfAchievManager::incAchiev passes true,
    // false); whether the list is non-empty
    static bool getListParty(mm::mtl::FixedVector<unsigned short, 422>& list, bool, bool);
    // fills list with the regular blades 1001 to 1011 (not 1012, 1013); false when it stays empty
    static bool getListRegular(mm::mtl::FixedVector<unsigned short, 422>& list);
    // 2.0.0's symbols name it. What it does: appends blades 1014..1050 and 1104, returns whether the list is not empty.
    // Callers: GfGameUtil::setPartyChange10010, GfItemUtil::getEquipChar, GfMenuItemUtil::searchEquipOrb and
    // searchEquipHanaParts.
    static bool getListRare(mm::mtl::FixedVector<unsigned short, 422>& list);
    // fills list with the common blades 1197 to 1396 that are in use or unselectable
    static bool getListCommon(mm::mtl::FixedVector<unsigned short, 422>& list);
    // 2.0.0's symbols name it. What it does: walks the blade rows (local game flag 0xD860 picks the walk) adding blades
    // to the list; returns a bool. Callers: SCOM_ACHIEV_INC::fn_71005645F0 (when GfDataUtil::isIra is false),
    // GfMenuBladeList::setupFromDriver/setupFromReleasble/setupFromTeam, GfMenuObjUtil.
    static bool getListParty(mm::mtl::FixedVector<unsigned short, 422>& list);
    // 2.0.0's symbols name it. What it does: for the blades 0x464-0x46C returns blade - 0x453 (the DLC drivers
    // 0x11-0x19), 0 for any other blade.
    static unsigned int getIraDriver(unsigned int blade);
    // appends the blades 1124 to 1132 (the DLC drivers' blades, getIraDriver); whether the list is not empty
    static bool getListIraBlade(mm::mtl::FixedVector<unsigned short, 422>& list);
    // whether a blade is one of the dummy blades (ids 1012-1013, 1073, 1110, 1124-1132); the symbols spell it
    // isDummyBlade, 1.0.0's GfGameUtil::isDummyBlade calls GfDataBlade::isDummyBlade at the same place
    static bool isDummyBlade(unsigned int blade);
    // the blade's voice actor (getMenuCastName) and illustrator (getMenuIlustName) name ids, in the messages of
    // BDAT tables 0x137 and 0x138 (GfMenuCharDataAdapter::update_BL_CVName/update_BL_IlustName); 0 for none
    static unsigned int getMenuCastName(unsigned int blade);
    static unsigned int getMenuIlustName(unsigned int blade);
    // the blade's menu voice file name in voice slot slot (GfBdatChrBl::getChrBlMnuVoice; GfMenuObjBladeBook's preview)
    static const char* getMenuVoiceName(unsigned int blade, unsigned int slot);
    // how many blades the crystal can still create (CrystalSelectListener refuses one at 0)
    static unsigned int getEnableCountForCreateBlade(unsigned int crystal);
    // 2.0.0's symbols name it. What it does: false for blade 0, else whether the short at 0x5A2C of the blade's game
    // data slot (getDataGame + slot * 0x8A4, the slot mapping isBladeLock uses) is 2;
    // GfGameUtil::execActivateMercenaryTeamForBlade does nothing when it holds.
    static bool isActivateMercenaryTeam(unsigned int blade);
    static ActivateType getBladeActivateType(const SDataBlade& blade);
    static ActivateType getBladeActivateType(unsigned int blade);
    static unsigned int addRareBlade(const SDataBlade& data);  // (symbols) the new blade, 0 for none
    // (1.0.0's symbols: its GfGameUtil::execAddCommonBlade calls addCommonBlade(data) where 3.0.1's execAddCommonBlade
    // calls this function, followed by the same code; 2.0.0's symbols name it) the new blade, 0 for none
    static unsigned int addCommonBlade(const SDataBlade& data);
    static bool isActivateReserver(unsigned int blade);
    static bool setActivateReserver(unsigned int blade);
    // (1.0.0's symbols: its GfGameUtil::execEquipMercenariesBlade calls setActivateDriver(blade, -1, driver, 0) where
    // 3.0.1's calls this function with the same arguments; 2.0.0's symbols name it) activates the
    // blade for the driver; 3.0.1's code returns a bool
    static bool setActivateDriver(unsigned int blade, int slot, unsigned int driver, unsigned int type);
    // no symbol in any build: setActivateDriver and setActivateReserver end with it (a blade's data is set to type 1,
    // the blade is placed in the game's blade list). A member because it lives in GfDataBlade's unit among its
    // functions and only GfDataBlade's activate functions call it.
    static bool fn_710023AEA4(unsigned int blade);
    // 2.0.0's symbols name it. A member because it lives in GfDataBlade's unit among its functions (before
    // GfDataParty::isExistBlade) and takes a blade. What it does: false unless blades 1001 and 1002 are both or neither
    // in the party (GfDataParty::isExistBlade); then for 1001 whether isHikariCurrent, for 1002 whether not, false for
    // others. Caller: GfGameScene::requestFieldBladeChange.
    static bool isDisableHomuraHikari(unsigned int blade);
    static bool getTaskSkillMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line);
    static bool getTaskTitleMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                    unsigned int level);
    // the LinkChNum of the blade's KizunaLinkSet row, 0 for none
    static unsigned int getLinkChNum(unsigned int blade);
    static bool getTaskResultMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                     unsigned int level);
    static unsigned int getSkillLineId(unsigned int blade, unsigned int line);
    // whether the blade is in the battle party (1.0.0's GfQuestInfo::incSuppressCount calls it on the quest's blade)
    static bool isBattleMember(unsigned int blade);
    // whether the blade (data type 1) is set to a driver in a party slot below 3 (GfDataParty::getDriverPartyID)
    static bool isActivateParty(unsigned int blade);
    static unsigned int getKizunaringCompleteNum(unsigned int blade);
    static unsigned int getKizunaringMax(unsigned int blade);
    // 5 for the regular and rare blades; for a common blade 1 + how many of the BTL wildcard values 0x3F-0x42 its
    // kizuna ring maximum exceeds (at most 4), 1 for any other blade
    static unsigned int getCrownPoint(unsigned int blade);
    // the scale of a blade's weapon (GfGameMount::attach scales the weapon's models by it at option 3)
    static float getWpnScale(unsigned int blade);
    static bool isRareBlade(unsigned int blade);
    // a game flag: Pyra's name shown as Mythra's (GfMenuObjNameSelect sets it from the name picked)
    static void setHomuriNameHikari(bool hikari);
    static bool isHomuriNameHikari();  // the flag setHomuriNameHikari sets (local flag 0x89FB, 1 bit)
    static bool isActivateUnuse(unsigned int blade);
    static bool setActivateUnuse(unsigned int blade);  // (symbols; returns whether the blade changed state)
    static void resetAttachedParty(unsigned int blade);  // (symbols)
    static bool isUnselect(unsigned int blade);
    // the driver the blade is set to, 0 for none
    static unsigned int getSetDriver(unsigned int blade);
    // the driver's slot (0..4) the blade is set in; SCOM_CURRENT_BLADE::exec passes it to GfDataDriver::setEquipBlade
    static unsigned int getDriverSetID(unsigned int blade);
    static AchievInfo* getAchievInfo(unsigned int blade, unsigned int line);
    // the blades with an affinity chart
    static bool getListForAchievement(mm::mtl::FixedVector<unsigned short, 422>& list);  // whether the list is not empty
    static unsigned int getKeyReleaseLevel(unsigned int blade);
    // 2.0.0's symbols name it. What it does: 0 for blade 0, else the blade's SDataBlade::m_gender (game data slot via
    // getBladeIndex); fn_710028AF64 calls it.
    static unsigned int getGender(unsigned int blade);
    // GfBdatChrBl::isChrBlFlagFreeEngage(blade) for a blade row below getChrBlEnd, else false (GfMenuBladeList, the blade
    // set and release menus ask it)
    static bool isFreeEngage(unsigned int blade);
    // GfBdatChrBl::isChrBlFlagNoMapRev(blade) for a blade row below getChrBlEnd, else false (btl::PlayerParameter::Initialize)
    static bool isNoMapRev(unsigned int blade);
    // 2.0.0's symbols name it. What it does: stores the flag into the blade's SDataBlade::m_bladeLock (the
    // byte isBladeLock reads); GfGameUtil::changeKubira and setBladeFavorite call it.
    static void setBladeLock(unsigned int blade, bool flag);
    // the release level of a skill line: lines 0-2 the arts, 3-5 the skills, 6-8 the field skills, 9 the key
    static unsigned int getAchievReleaseLevel(unsigned int blade, unsigned int line);
    static bool setAchievReleaseLevel(unsigned int blade, unsigned int line, unsigned int level);  // (symbols)
    static unsigned int getAchievementID(unsigned int blade, unsigned int line, unsigned int level);  // (symbols)
    static void setSkillLineLevel(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getBladeWpnType(unsigned int blade);
    // the voice name a blade says when it starts field skill skill, or null (SCOM_FIELD_VOICE::createFieldSkillStart)
    static const char* getFieldSkillVoice(unsigned int blade, unsigned int skill);
    // the weapon name suffix of the blade's weapon type ("" for blade 0; "_01".."_49" by type)
    static const char* getDeathBlowWeaponName(unsigned int blade);
    // the same suffix for the blades with their own base weapon effect/animation files (Hana's forms, the common
    // blades, 1051-1072, 1082 and up but 1103; getBaseEfbWeaponName also 1004 and 1010), else ""
    static const char* getBaseEabWeaponName(unsigned int blade);
    static const char* getBaseEfbWeaponName(unsigned int blade);
    static const char* getName(unsigned int blade, unsigned int kind);
    // the blade's name from its data: kind 0 its own name rows (SDataBlade::m_nameMsg/m_nameMsgAlt), else that
    // row of table 423 (blade rows below CHR_Bl's end) or 396; "" for none
    static const char* getName(const SDataBlade& data, unsigned int kind);
    // a common blade's debug name when one is set (else getName(blade, 0)); other blades' CHR_Bl DebugName
    static const char* getDebugName(unsigned int blade);
    // the message table and row of the blade's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    // the message table and row of a blade data's name (getName passes the blade's game data slot)
    static bool getNameWithMsgID(unsigned char*& bdat, unsigned int& id, const SDataBlade& data);
    static unsigned int getQuestRace(unsigned int blade);
    static SDataBlade* getSDataBlade(unsigned int blade);
    // (symbols) the enhances of a blade's data; true when any (DataObjBlade's armor/rate getters sum them)
    static bool getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, SDataBlade& data, bool flag);
    // no symbol in any build (it follows getValidEnhance(enhances, data, flag)): removes the enhances whose
    // GfBdatBtl enhance effect has the condition flag (isBTL_EnhanceEffFlagCondition) unless keep is set.
    // GfDataEnemy::getValidEnhance carries it inline with keep set; GfDataDriver::getValidEnhance and the weapon
    // and skill enhance helpers call it.
    static void fn_710024121C(mm::mtl::FixedVector<unsigned short, 64>& enhances, bool keep);
    // no symbol in any build (between GfDataEnemy::getValidEnhance and setupSDataBladeAchievement): appends the
    // GfBdatItem enhance of the blade's equipped weapon (weapon 0 for blade 0), filtered by fn_710024121C(keep).
    // Callers: GfDataEnemy::getValidEnhance, GfDataDriver::getValidEnhance.
    static void fn_7100234FF8(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int blade, bool keep);
    // no symbol in any build (follows fn_7100234FF8): appends the BTL skill enhances of the blade's three skills at
    // their levels, filtered by fn_710024121C(keep). Callers: the three getValidEnhance functions.
    static void fn_710023510C(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int blade, bool keep);
    // the blade's physical and ether defense bonus (Hana's from her role part); 0 for no blade
    static unsigned int getParmor(unsigned int blade);
    static unsigned int getEarmor(unsigned int blade);
    static unsigned int getHpMaxRev(unsigned int blade);
    static unsigned int getStrengthRev(unsigned int blade);
    static unsigned int getPowerEtherRev(unsigned int blade);
    static unsigned int getDexRev(unsigned int blade);
    static unsigned int getAgilityRev(unsigned int blade);
    static unsigned int getLuckRev(unsigned int blade);
    static bool getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>& orbs, unsigned int blade);
    // the item handles of the blade's equipped orbs, by slot (empty past getEquipOrbMax or for no blade)
    static GfItemHandle getEquipOrbHandle(unsigned int blade, unsigned int slot);
    // whether every orb slot up to getEquipOrbMax holds an orb (false for no blade; symbols)
    static bool isEquipOrbFull(unsigned int blade);
    static bool setEquipOrbHandle(unsigned int blade, GfItemHandle handle, unsigned int slot);
    // the enhancements of the blade's equipped orbs (false for no blade)
    static bool getEquipOrbEnance(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int blade);
    static bool getEquipOrbEnance(mm::mtl::FixedVector<unsigned short, 64>& enhances, SDataBlade& data);
    // copies a blade's data into the blade's game data slot and gives it the blade's row
    static void setUiCommonBlade(const SDataBlade& data, unsigned int blade);
    static unsigned int getFootStep(unsigned int blade);
    static unsigned int getFootStepEffect(unsigned int blade);
    static unsigned int getRole(unsigned int blade);
    static const char* getVoiceStr(unsigned int blade);
    static const BladeArtsSlot* getArts(unsigned int blade, unsigned int index);
    static unsigned int getArtsEnhance(unsigned int blade, unsigned int index);
    static unsigned int getBladeWeaponRank(unsigned int blade);  // its weapon's rank, 0 for none
    static unsigned int getVoiceID(unsigned int blade);  // its personality's voice id, 0 for none
    // the normal-talk message for a personality's voice id (0 when the id is outside the table)
    static unsigned int makeNormalTalkByPersonality(unsigned int personality);
    static const BladeArtsSlot* getNArts(unsigned int blade, unsigned int index);
    static unsigned int getFavorite(unsigned int blade, FAVORITE favorite);
    // whether the item's category is one of the blade's two favorite categories (symbols)
    static bool isFavoriteCategory(unsigned int blade, unsigned int item);
    // whether the item is one of the blade's two favorite items (symbols)
    static bool isFavoriteItem(unsigned int blade, unsigned int item);
    static bool isUsedFavorite(unsigned int blade, FAVORITE favorite);  // whether the favorite has been used (seen)
    static int getOffsetID(unsigned int blade);  // its menu offset id
    static unsigned int getBladePower(unsigned int blade);
    static bool isMale(unsigned int blade);
    static bool isFemale(unsigned int blade);
    static bool isAnimal(unsigned int blade);
    // the attribute suffix of a blade's base effect file ("_fire" .. "_dark", "" for none): `attribute`'s, or when it
    // is 0 the blade's own (getAttribute) for a Hana or a common blade, "" for any other
    static const char* getBaseEfbAttributeName(unsigned int blade, unsigned int attribute);
    static unsigned char getAttribute(unsigned int blade);
    // the idea type of the blade's attribute (getAttribute): 0 for 1 and 2, 1 for 3 and 6, 2 for 4 and 5, 3 for 7 and
    // 8, else 0 (symbols)
    static unsigned int getIdeaTypeByAttribute(unsigned int blade);
    // whether the idea type of the blade's attribute (as getIdeaTypeByAttribute maps it) is `idea`; false for no attribute
    static bool isMatchIdeaAttribute(unsigned int blade, unsigned int idea);
    static bool getExtraParts(const SDataBlade& data, unsigned int part);
    static unsigned int getBladePower(SDataBlade& data);
    static unsigned int getRoleByWpnType(unsigned int wpnType);
    static bool isHikariCurrent();
    static void setHikariCurrent(bool value);
    static unsigned int getStartCommonBlade();
    // 2.0.0's symbols name it (the same 1401; its one caller is TitleStatePlayEvent::enter in both builds)
    static unsigned int getStartActCommonBlade();
    static unsigned int getStartUiCommonBlade();
    static bool isCommonBlade(unsigned int blade);
    static bool isRegularBlade(unsigned int blade);
    static bool isValid(unsigned int blade);
    static bool isBladeID(unsigned int blade);
    static bool isNeedChangeWeapon(unsigned int blade);
    static unsigned int getActBlade2CommonBlade(unsigned int blade);
    // a common blade's row in BLD_NameList (GfMenuBdat::getBladeDataFP reads its name sort key there)
    static unsigned int getBLD_NameList(unsigned int blade);
    static bool isEnableEngageRex(unsigned int blade);
    static unsigned int getBornTime(unsigned int blade);
    static SDataIdea* getSDataIdea(unsigned int blade);
    static bool isAttachedParty(unsigned int blade);
    static bool isActivateDriver(unsigned int blade);
    static const char* getResourceNameModel(unsigned int blade);
    static bool isKizunaringComplete(unsigned int blade);
    static bool isReleasedRareBlade(unsigned int blade);
    // whether the blade has completed its affinity chart (GfGameUtil::addTrustPoint raises its trust rank only then)
    static bool isCompleteAchievement(unsigned int blade);
    static unsigned int getTrustRank(unsigned int blade);
    // named by the symbols (its second parameter's type GfIdea too); GfGameUtil::addTrustRankForKizunaRing passes the
    // rank above getTrustRank's
    static void setTrustRank(unsigned int blade, GfIdea rank);
    static bool isSetBlade(unsigned int blade);
    static unsigned int getBladeWeapon(unsigned int blade);
    static const char* getResourceNameMotion(unsigned int blade);
    static const char* getResourceNameAddMotion(unsigned int blade);
    static unsigned int getRace(unsigned int blade);
    static float getScale(unsigned int blade);
    static void setupSDataBlade(SDataBlade& data, unsigned int blade, bool flag);
    // the symbols name them: initSaveData sets every listed blade's game entry up afresh
    static void initSaveData(SDataGame& game);
    static void setupSDataBladeAchievement(SDataBlade& data, bool flag);
    static unsigned int getSize(unsigned int blade);
    static unsigned int getEquipOrbMax(unsigned int blade);
    // the orb in a blade's slot (GfEquipUtil::getEquipBladeOrb returns it, zero-extended)
    static unsigned short getEquipOrb(unsigned int blade, unsigned int slot);
    static bool setEquipOrb(unsigned int blade, unsigned short orb, unsigned int slot);
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
    // 2.0.0's symbols name it (1.0.0 called this code isActivateMercenaryTeam). What it does: whether the blade's
    // m_bladeLock byte (setBladeLock) is set.
    static bool isBladeLock(unsigned int blade);
    static bool isNeedAttributeResource(unsigned int blade);
    // the reserve blades (GfDataMercenaries::getReserver fills its list with them)
    // whether the list is not empty
    static bool getListReserver(mm::mtl::FixedVector<unsigned short, 422>& list);
    // the symbols name it. What it does: getListReserver's blades less the ones set to a driver (isActivateDriver);
    // whether the list is not empty
    static bool getListReserverWithSolo(mm::mtl::FixedVector<unsigned short, 422>& list);
    // drops the list's repeated blades (GfAchievStats's blade counts call it after getListReserver; returns nothing
    // its caller reads)
    static void removeSameBlade(mm::mtl::FixedVector<unsigned short, 422>& list);
    // Placeholder name: the symbols leave it unnamed. A member because removeSameBlade, its only caller, passes it the
    // list it was given and a local group of blade ids. What it does: when the list holds any of the group's blades,
    // erases the first copy of each of the group's other blades from it.
    static void fn_7100239560(mm::mtl::FixedVector<unsigned short, 422>& list,
                              const mm::mtl::FixedVector<unsigned short, 422>& group);
    static unsigned int getBladeRelativeID(unsigned int blade);  // getBladeIndex
    // named by the symbols (not written yet); GfDataDriver::getDefaultWpnType keeps the weapon types it finds a
    // blade for
    static unsigned int getBladeByWeaponType(unsigned int weaponType, unsigned int driver, bool);
    // whether a model path names a common blade (it starts with "bl/bl2")
    static bool getCommonBladeName(const char* path);
    // a blade's mercenary name message (none for the common blades' ids 1197-1422)
    static bool getMercenaryName(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    // a common blade's name text ("" for none)
    static const char* getCommonBladeName(unsigned int blade);
    // 2.0.0's symbols name it. What it does: whether local flag 0x89FB (type 1) of game's GameFlag is set
    // (isHomuriNameHikari's flag).
    static bool isHomuriNameHikari(const SDataGame& game);
    // 2.0.0's symbols name it (right after getStartCommonBlade in both builds). What it does: returns 1397
    // (GfAchievManager::getBladeByAchievementSet and GfGameUtil::setupPoweredNewGameParam call it).
    static unsigned int getEndCommonBlade();
    // 2.0.0's symbols name it. What it does: whether blade is in 1124-1132 (DataObjBlade::getNorAtkDmgMin/Max pass a
    // blade id).
    static bool isIra(unsigned int blade);
    // symbol 0x71002400C4; GfPouchUtil::setPouch passes each engaged blade and the pouch's item
    static void setUsedFavoriteItemForPouch(unsigned int blade, unsigned int item);
    // 2.0.0's symbols name it. What it does: getCreator on the given game data: the blade's 16-bit m_creator, 0 for
    // blade 0 (tl::TitleStatePlayEvent::enter calls it).
    static int getCreator(const SDataGame& game, unsigned int blade);
};


}  // namespace gf

#endif
