#ifndef GF_GFDATABLADE_H
#define GF_GFDATABLADE_H

#include "gf/AchievQuest.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class SDataBlade; enum ActivateType : int; enum CLOUD_SEA : int; enum WEATYPE : int; enum WEATHERID : int; }
namespace gf { struct BladeArtsSlot; }
namespace gf { struct BladeSkillSlot; }
namespace gf { struct SDataIdea; }
namespace gf { class DataParamAcc; }
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
// a map's record in the game data (0x20 bytes; GfDataBlade's fn_710024E1C8 finds it by m_mapId; GfFieldWeather keeps
// each map's weather in it). The names are not the original's.
struct MapEnvData {
    char m_resource[8];  // GfBdatMaplist::getMaplistresource's name (GfFieldWeather::setupGame copies it in)
    WEATYPE m_type;  // the map's weather, its id, time and length (GfFieldWeather's fn_7100280F84 saves them)
    WEATHERID m_id;
    float m_time;
    float m_timeMax;
    unsigned int m_mapId;
    unsigned int m_cloudSea;  // fn_710024E8F4 stores (cloudSea != 0); GfFieldWeather::getCloudSea reads it
};

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
    static void getListPartyAll(mm::mtl::FixedVector<unsigned short, 422>& list);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions. What it does: GfGameFlag::getLocal of the game data's flags (GfDataManager::getDataGame
    // + 0xFBBC4), width 16, index 1; TUnk_B64F08::fn_71004944B8 compares it with 2000.
    static unsigned short fn_7100231884();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among its functions. What it does: true for the enemy of BDAT ID 0x3F1 (object type 4) or the
    // blade of BDAT ID 0x18 (object type 3), read through acc; SCOM_OBJ_VFADE's constructor then uses effect 16.
    static bool fn_7100232660(const DataParamAcc& acc);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit (its tail, before gf_game_flag). What it does: takes nothing; constructs (guarded, __cxa_atexit)
    // two function-static lists (guards 0x7100C339F0/F8) and zeroes their counts (0x7100C33C68, 0x7100C33E70).
    // GfDataManager's constructor calls it.
    static void fn_71002550E8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does: the
    // same code as fn_71002550E8 (the same two lists, counts zeroed); GfDataManager::destroy calls it.
    static void fn_7100255190();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // walks GfBdatRsc's NPC list (getRscNpcListStart..End, fn_7100219C58) into the same function-static lists;
    // GfDataManager::setupGame and gevReloadBdat (type 1) call it.
    static void fn_7100255238();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they sit in GfDataBlade's
    // unit after its fn_7100255238 (no class of their own; no this). What they do: for an id above 2000 with a
    // GfBdatRsc::fn_7100219C58 value v, the 1-based slot i of the 8-bit local flags 0x10C4 + i (fn_71002557C8) or
    // 0x11C5 + i (fn_7100255848), i < 256, that holds v - 0xED02; 0 when none.
    static unsigned int fn_71002557C8(unsigned int id);
    static unsigned int fn_7100255848(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit. What it does: true when local flag 0xBDCD (type 1) of game's flags (+0xFBBC4) is set, else
    // whether flag 0xD880 is; GfGameManager::isClearGame passes the title's save buffer's game data.
    static bool fn_7100232054(const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit. What it does: fn_7100232054's test on GfDataManager::getDataGame()'s flags; GfGameManager::
    // isClearGame tail-calls it.
    static bool fn_7100231FF8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfComBehaviorNpc::BdatInfo::
    // isIconTalkBonus called GfGameFlag::getLocal itself, with other arguments). A member because its address is in
    // GfDataBlade's unit and it takes no object. What it does: whether local flag (type 1) id is set, an id above
    // 43877 moved up by 11651 first (GfGameFlag::getLocal(1, id)). Caller: GfComBehaviorNpc::BdatInfo::
    // isIconTalkBonus, with its talk event's row in BDAT sheet 0xeb + 41878.
    static bool fn_710024D890(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's caller called GfGameFlag::setLocal
    // itself). A member for the same reason as fn_710024D890. What it does: sets local flag (type 1) id, moved as in
    // fn_710024D890, to value (GfGameFlag::setLocal(1, id, value)). Caller: GfComBehaviorNpc::BdatInfo::
    // setTalkBonusFlag, with fn_710024D890's id and 1.
    static void fn_710024D86C(unsigned int id, unsigned int value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's fld plugin has no setNpcMeet). A
    // member because its address is in GfDataBlade's unit. What it does: for an id above 2000, looks the id up with
    // GfBdatRsc::fn_7100219CE0 and answers whether that local flag (type 1) is set; false otherwise. Callers: the fld
    // plugin's setNpcMeet (before and after fn_710024DDDC), GfMenuManager::fn_710035A764.
    static bool fn_710024DE6C(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit next to fn_710024DA88 (same ids). What it does: 0 for an id up to 2000, else
    // GfBdatRsc::fn_7100219CE0(id). Caller: GfMenuManager::fn_710035A764 (before fn_710024DE6C on the same id).
    static unsigned int fn_710024DAB0(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit, next to fn_710024DDDC and fn_710024DE6C (same ids). What it does: 0 for an id up to 2000,
    // else GfBdatRsc::fn_7100219C58(id) (fn_710024DDDC records that value - 0xED02). Callers:
    // GfMenuCharDataAdapter::fn_7100339800 (an NPC object's id; shows the value - 0xED03), gf_menu_obj_hitonowa.
    static unsigned int fn_710024DA88(unsigned int id);
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (between GfDataDriver::getName and GfDataBlade::getName, no this) and its callers pass
    // it a blade id (GfMenuReference::getReferenceBladeID, GfGameUtil::getTrustRank). What it does: for the blades
    // 0x464-0x46C returns blade - 0x453 (the DLC drivers 0x11-0x19), 0 for any other blade.
    static unsigned int fn_7100236518(unsigned int blade);
    // whether a blade is one of the dummy blades (ids 1012-1013, 1073, 1110, 1124-1132); the symbols spell it
    // fn_7100237D28, 1.0.0's GfGameUtil::isDummyBlade calls GfDataBlade::isDummyBlade at the same place
    static bool isDummyBlade(unsigned int blade);
    // the blade's voice actor (getMenuCastName) and illustrator (getMenuIlustName) name ids, in the messages of
    // BDAT tables 0x137 and 0x138 (GfMenuCharDataAdapter::update_BL_CVName/update_BL_IlustName); 0 for none
    static unsigned int getMenuCastName(unsigned int blade);
    static unsigned int getMenuIlustName(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: stores (cloudSea != 0) at 0x1C of the record fn_710024E1C8
    // returns for the map; GfGameUtilCloudSea::setInnCloudSea passes (GfGameManager::getMapID(), its cloud sea),
    // GfPlayComPlayerDead::update calls it too.
    static void fn_710024E8F4(unsigned int map, CLOUD_SEA cloudSea);
    // Placeholder name: new in 3.0.1 (1.0.0's GfFieldWeather::getCloudSea and setupGame search the game data's map
    // records inline). A member because it lives in GfDataBlade's unit among its functions (no this). What it does:
    // the game data's record for the map (two 64-record arrays searched by m_mapId, the first in
    // GfDataManager::getDataGame() + 0x10A53C, each only when GfBdatMaplist::getMaplistresource(map) is set), else a
    // zeroed function-static record. Callers: GfFieldWeather (getCloudSea, setupGame, createWeather, updateEvent,
    // updateWeather, applyNowMapWeather), fn_710024E8F4, GfDataStore::initGameData.
    static MapEnvData* fn_710024E1C8(unsigned int map);
    // Placeholder name: new in 3.0.1 (1.0.0's GfFieldWeather::setupGame strcpys into the first free record inline).
    // A member for the same reason as fn_710024E1C8. What it does: a game data map record whose m_mapId is 0 (a free
    // one); GfFieldWeather::setupGame copies a map's resource name into it and sets its m_mapId.
    static MapEnvData* fn_710024E0D0();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason as fn_710024E1C8.
    // What it does: whether the map's record (fn_710024E1C8) has its cloud sea on (m_cloudSea != 0). Caller:
    // GfFieldWeather::applyNowMapWeather, which hands it on as the cloud sea to set (it tests the whole word).
    static CLOUD_SEA fn_710024E8D4(unsigned int map);
    // Placeholder name: nothing names it (1.0.0's GfGameUtil::execActivateMercenaryTeamForBlade calls
    // isActivateMercenaryTeam at its place, but 3.0.1 keeps that function at 0x71002398D8, reading another field).
    // A member because it lives in GfDataBlade's unit among its functions (no this). What it does: false for blade 0,
    // else whether the short at 0x5A2C of the blade's game data slot (getDataGame + slot * 0x8A4, the slot mapping
    // isActivateMercenaryTeam uses) is 2; execActivateMercenaryTeamForBlade does nothing when it holds.
    static bool fn_71002383C8(unsigned int blade);
    static ActivateType getBladeActivateType(const SDataBlade& blade);
    static ActivateType getBladeActivateType(unsigned int blade);
    static bool isActivateReserver(unsigned int blade);
    static bool setActivateReserver(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its functions (no this). What it does: sets local game flag 0xBDCD (width 1) of the game data's
    // GameFlag (game + 0xFBBC4) to flag; GfGameUtil::incGameClearCount passes getDataGame() and true.
    static void fn_71002320AC(SDataGame* game, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among its functions (no this). What it does: sets local game flag 0xD860 (width 1) of
    // game's GameFlag (+0xFBBC4) to flag; TUnk_B54858::fn_71002A7430 passes getDataGame() and (mode == 1).
    static void fn_71002324FC(SDataGame* game, bool flag);
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
    // the scale of a blade's weapon (GfGameMount::attach scales the weapon's models by it at option 3)
    static float getWpnScale(unsigned int blade);
    static bool isRareBlade(unsigned int blade);
    // a game flag: Pyra's name shown as Mythra's (GfMenuObjNameSelect sets it from the name picked)
    static void setHomuriNameHikari(bool hikari);
    static bool isHomuriNameHikari();  // the flag setHomuriNameHikari sets (local flag 0x89FB, 1 bit)
    static bool isActivateUnuse(unsigned int blade);
    static void setActivateUnuse(unsigned int blade);  // (symbols)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A GfDataBlade member because its address
    // lies in GfDataBlade's unit. What it does: returns one of three blade ids (a table at 0x71009BA374) by which
    // of three SDataGame shorts (0x7CBC, 0x8560, 0x8E04) is 2, else 0; ScriptPlayText's pt setDriverEnable takes
    // the returned blade's mercenary team off its mission for driver 4.
    static unsigned int fn_7100253C98();  // (it loads the table's 16-bit id; callers use all 32 bits)
    static bool isUnselect(unsigned int blade);
    // the driver the blade is set to, 0 for none
    static unsigned int getSetDriver(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in
    // GfDataBlade's unit and it takes no object. What it does: 0 for ids below 2001; else the game flag number
    // GfBdatRsc::fn_7100219C58(id) gives (the PtrSingleton<GfBdatRsc> instance) and, when that is nonzero, the
    // local game flag GfGameFlag::getLocal(2, flag). GfMenuGfObjAdapter::fn_7100340094 passes a type-6 object's
    // BDAT id (GfObjAcc::fn_7100523B74) and switches on 0..3.
    static unsigned int fn_710024DD94(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (no callers left). A member because it sits in
    // GfDataBlade's unit next to fn_710024DA88 and fn_710024D890 (same ids). What it does: false for an id up to
    // 2000, else whether GfBdatRsc::fn_7100219574(id) is nonzero.
    static bool fn_710024D82C(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (no callers left). A member for the same
    // reason as fn_710024D82C, next to fn_710024DE6C. What it does: for an id above 2000 reads local flag (type 2)
    // GfBdatRsc::fn_7100219C58(id) and answers whether it is 1 or 3; false otherwise.
    static bool fn_710024DED0(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (no callers left). A member for the same
    // reason as fn_710024D82C. What it does: sets local flag (type 1) 2160 + GfBdatRsc::fn_7100219CE0(id) (2160
    // alone for an id up to 2000) to value.
    static void fn_710024DF38(unsigned int id, bool value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (no callers left). A member for the same
    // reason as fn_710024D82C. What it does: whether local flag (type 1) 2160 + GfBdatRsc::fn_7100219CE0(id) is set
    // (2160 alone for an id up to 2000); fn_710024DF38 sets it.
    static bool fn_710024DF88(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in
    // GfDataBlade's unit and it takes no object. What it does: false for ids below 2001; else sets bdat to
    // GfDataBdat::getFP(0x1C3) and id to GfBdatRsc::fn_7100219BD0(blade) (the PtrSingleton<GfBdatRsc> instance) and
    // returns whether that id is nonzero. GfMenuObjTargetInfo::openOther passes a type-6 object's BDAT id
    // (GfObjAcc::fn_7100523B74) and shows the text at bdat/id as the other's shop name.
    static bool fn_710024D8C4(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    // the driver's slot (0..4) the blade is set in; SCOM_CURRENT_BLADE::exec passes it to GfDataDriver::setEquipBlade
    static unsigned int getDriverSetID(unsigned int blade);
    static AchievInfo* getAchievInfo(unsigned int blade, unsigned int line);
    // the blades with an affinity chart
    static void getListForAchievement(mm::mtl::FixedVector<unsigned short, 422>& list);
    static unsigned int getKeyReleaseLevel(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its blade accessors (no this). What it does: 0 for blade 0, else the blade's SDataBlade::m_gender
    // (game data slot via getBladeIndex); fn_710028AF64 calls it.
    static unsigned int fn_710023982C(unsigned int blade);
    // GfBdatChrBl::fn_71001ED49C(blade) for a blade row below getChrBlEnd, else false (GfMenuBladeList, the blade
    // set and release menus ask it)
    static bool fn_710023978C(unsigned int blade);
    // GfBdatChrBl::fn_71001ED52C(blade) for a blade row below getChrBlEnd, else false (btl::PlayerParameter::Initialize)
    static bool fn_71002397DC(unsigned int blade);
    // GfBdatBtl::fn_71001E77DC(id) while fn_71002324C8's flag (1, 0xD860) is set, else getGrowLevelExp(id)
    static unsigned int fn_71002326F0(unsigned int id);
    // a GfBdatRsc caption: bdat = GfDataBdat::getFP(452), id = GfBdatRsc::fn_710021A010(rsc); false for rows up to
    // 2000 or no caption (TUnk_B62AA0::fn_710041F998)
    static bool fn_710024DA20(unsigned char*& bdat, unsigned int& id, unsigned int rsc);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among its blade accessors (no this). What it does: stores the flag into the blade's
    // SDataBlade::m_activateMercenaryTeam (the byte isActivateMercenaryTeam reads); GfGameUtil::fn_71002EBC90 and
    // fn_71004922BC call it.
    static void fn_7100239934(unsigned int blade, bool flag);
    // the release level of a skill line: lines 0-2 the arts, 3-5 the skills, 6-8 the field skills, 9 the key
    static unsigned int getAchievReleaseLevel(unsigned int blade, unsigned int line);
    static void setSkillLineLevel(unsigned int blade, unsigned int line, unsigned int level);
    static unsigned int getBladeWpnType(unsigned int blade);
    static const char* getName(unsigned int blade, unsigned int kind);
    // the blade's name from its data: kind 0 its own name rows (SDataBlade::m_nameMsg/m_nameMsgAlt), else that
    // row of table 423 (blade rows below CHR_Bl's end) or 396; "" for none
    static const char* getName(const SDataBlade& data, unsigned int kind);
    // a common blade's debug name when one is set (else getName(blade, 0)); other blades' CHR_Bl DebugName
    static const char* getDebugName(unsigned int blade);
    // the message table and row of the blade's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    static unsigned int getQuestRace(unsigned int blade);
    static SDataBlade* getSDataBlade(unsigned int blade);
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
    static bool isUsedFavorite(unsigned int blade, FAVORITE favorite);  // whether the favorite has been used (seen)
    static int getOffsetID(unsigned int blade);  // its menu offset id
    static unsigned int getBladePower(unsigned int blade);
    static bool isMale(unsigned int blade);
    static bool isFemale(unsigned int blade);
    static bool isAnimal(unsigned int blade);
    static unsigned char getAttribute(unsigned int blade);
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
    static unsigned int getTrustRank(unsigned int blade);
    static bool isSetBlade(unsigned int blade);
    static unsigned int getBladeWeapon(unsigned int blade);
    static const char* getResourceNameMotion(unsigned int blade);
    static const char* getResourceNameAddMotion(unsigned int blade);
    static unsigned int getRace(unsigned int blade);
    static float getScale(unsigned int blade);
    static void setupSDataBlade(SDataBlade& data, unsigned int blade, bool flag);
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
    // (appended by chardata) 1.0.0's name: its GfMenuCharDataAdapter::update_BL_InMercenry calls it at the same site
    // (the symbols call it fn_71002398D8)
    static bool isActivateMercenaryTeam(unsigned int blade);
    static bool isNeedAttributeResource(unsigned int blade);
    // the reserve blades (GfDataMercenaries::getReserver fills its list with them)
    static void getListReserver(mm::mtl::FixedVector<unsigned short, 422>& list);
    static unsigned int getBladeRelativeID(unsigned int blade);  // getBladeIndex
    // whether a model path names a common blade (it starts with "bl/bl2")
    static bool getCommonBladeName(const char* path);
    // a blade's mercenary name message (none for the common blades' ids 1197-1422)
    static bool getMercenaryName(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    // a common blade's name text ("" for none)
    static const char* getCommonBladeName(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: local flag 1 (type 16) of game's GameFlag (+0xFBBC4).
    static unsigned short fn_7100231EB8(const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether local flag 0xD791 (type 1) of game's GameFlag is set.
    static bool fn_7100232244(const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether local flag 0x89FB (type 1) of game's GameFlag is set (isHomuriNameHikari's flag).
    static bool fn_7100235F94(const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: true when local flag 0xD793 (type 1) of game's GameFlag is set, else whether flag 0xD882 is.
    static bool fn_71002320C8(const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: true when local flag 0xD77E (type 1) of game's GameFlag is set, else whether flag 0xD87E is.
    static bool fn_710023217C(const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: fn_710023217C's test on GfDataManager::getDataGame()'s flags.
    static bool fn_7100232120();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether local flag 0xD795 (type 1) of GfDataManager::getDataGame()'s GameFlag is set.
    static bool fn_7100232290();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether local flag 0xD860 (type 1) of GfDataManager::getDataGame()'s GameFlag is set (fn_71002324FC sets it).
    static bool fn_71002324C8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether fn_7100231884 (local flag 1, type 16) is above 0xBE7.
    static bool fn_710023220C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether fn_7100231884 (local flag 1, type 16) is above 0x1F64.
    static bool fn_710024E91C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether local flag 0xD862 (type 1) is set (GfGameFlag::getLocal(1, 0xD862)); fn_710024E9CC sets it.
    static bool fn_710024E9A8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether local flag 0xD863 (type 1) is set; fn_710024EA00 sets it.
    static bool fn_710024E9DC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: local flag 652 (type 4) (GfGameFlag::getLocal(4, 652)).
    static unsigned int fn_710024DD88();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: true when local flag 0xD788 (type 1) is set, else
    // when the pointer at 0x7100C294C0 is set and gf::fn_71002229C0(3) is above 0 (GfGameManager::fn_71002AC64C).
    static bool fn_7100232754();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: sets local flag 0xD862 (type 1) to flag.
    static void fn_710024E9CC(bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: sets local flag 0xD863 (type 1) to flag.
    static void fn_710024EA00(bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: sets local flags 0xD77E and 0xD87E (type 1) to flag (the two fn_710023217C tests).
    static void fn_71002321D4(bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: sets local flag 0xD791 (type 1) of game's GameFlag to flag (fn_7100232244 reads it).
    static void fn_7100232274(SDataGame* game, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: sets local flag 0xD795 (type 1) of game's GameFlag to flag (fn_7100232290 reads it).
    static void fn_71002322C4(SDataGame* game, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether getDataGame()'s m_chapterSaveValue (+0x26) equals fn_7100231884 and m_eventChapterSave (+0x28) is not 0.
    static bool fn_710023182C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: returns 1397 (GfAchievManager::getBladeByAchievementSet calls it).
    static unsigned int fn_7100231754();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: nothing (an empty body; GfGameManager::setupGame calls it).
    static void fn_710023493C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether id is in 25501-25999 (GfItemUtil::getCountByItemCategory, getEnableStock, getProperty pass an item id).
    static bool fn_71002327B0(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether blade is in 1124-1132 (DataObjBlade::getNorAtkDmgMin/Max pass a blade id).
    static bool fn_71002364B8(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether id is in 10001-10744 (tl::TitleStatePlayEvent::enter passes an event id).
    static bool fn_710024F258(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions. What it does: whether id is 40260-40268 or 40312.
    static bool fn_710023384C(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataBlade's functions (before addRareBlade). What it does: getCreator on the given game
    // data: the blade's 16-bit m_creator, 0 for blade 0 (tl::TitleStatePlayEvent::enter calls it).
    static int fn_710023C478(const SDataGame& game, unsigned int blade);
};

}  // namespace gf

#endif
