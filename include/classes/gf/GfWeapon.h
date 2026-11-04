#ifndef CLASSES_GF_GFWEAPON_H
#define CLASSES_GF_GFWEAPON_H

#include "classes/gf/GfAppendHandles.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class SoundPack; }
namespace gf { class QuestID; struct SDataGameSavedEvent; }
namespace gf {
// table 0x7100B54DE8: its slot 0 is GfAppendHandles's destructor, so the destructor is inline
class GfWeapon : public ::gf::GfAppendHandles {
public:
    virtual ~GfWeapon() {}  // slot 0
    // Placeholder name: nothing names it in either version (1.0.0's copy at 0x710031E054 is unnamed too). A member
    // because GfGameMount::attach calls it on its m_weapon (x0) twice, once per set. What it does: for each of the
    // ten objects of the set in use whose GfObj has a GfComAsm (obj+0x48, isKindOf GfComAsm::m_rtti), it makes the
    // idle state name GfGameUtil::makeWeaponStateIdle gives for the weapon's owner (GfGameUtil::getWeaponOwner of the
    // object's handle) and whether that owner is in battle, and sets it on layer 0 (GfComAsm::setState).
    void fn_71002AE854();
    // the resource ID (GfAppend::getRscID) of the first append in the append list of the object in use's first
    // (right) and second (left) handle; 0 without appends (the original zero-extends it: a wider return type)
    unsigned int getRscRight() const;
    unsigned int getRscLeft() const;
};
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function of the GfWeapon unit
// (its address lies there; no this). What it does: the model name of driver id from GfBdatChrDr
// (getChrDrModel2, getChrDrCondition with GfGameCond::isGameCond, then BDAT columns by the driver's id),
// first trying fn_71002DF4C4(id, third argument); for driver 6 with the second argument set it also ORs in
// isInvalidMelefRetarget's result. GfAssetSetupDriver's getMdlFile/getArcFile pass (id, create type in {2, 3, 11},
// create type == 3), GfAssetSetupNpc::getMdlFile (id, false, create type == 3) for ids below 26.
const char* fn_71002DF39C(unsigned int driverId, bool createTypeIn2311, bool createType3);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to fn_71002DF39C, its caller (no this). What it does: the model name of the first of the
// driver's three accessories (GfDataDriver::getEquipAcce) whose GfBdatItem::getPcEquipModel name is non-empty and whose
// getPcEquipDriver is the driver ("pc/pc110602" instead of "pc/pc110601" for driver 6 with flag set); none otherwise.
// fn_71002DF39C and fn_71002DF624 try it first.
const char* fn_71002DF4C4(unsigned int driverId, bool flag);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit after fn_71002DF4C4 (no this). What it does: fn_71002DF4C4(id, flag), where for driver 6 with
// the second argument set flag also takes GfDataEvent::isInvalidMelefRetarget of GfGameEvent::getStartEventId() (as
// fn_71002DF39C does). GfAssetSetup::setRefResource calls it.
const char* fn_71002DF624(unsigned int driverId, bool check, bool flag);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes only a handle (no this). What it does: false for handle -1, a GfObjAcc with no
// object, a destroyed object (isDestroy) or one with flag 0x11 (testFlag); for an object of type 6 whose bound
// gimmick (gmk::getBindedGmkInst) has type 3 (its slot 2), whether the "flag" column of the gimmick's BDAT row
// (getBindedBdatFp, its row at 0x38) holds the flag named "HITONOWAGET" (Bdat::getFlagVal) is nonzero.
// GfMenuGfObjAdapter::update_IRA_NpcHitonowaIcon calls it.
bool fn_71002D9B5C(GF_OBJ_HANDLE* handle);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to fn_71002EEB14 (no object: it takes nothing). What it does: returns the int at .bss
// 0x7100EA4890, which fn_71002EEB14 (called by tl::TitleStatePlayGame::enter) stores from its first argument before
// running the "aoc_boot" script (GfScriptManager slot 0x46) and clears afterwards. The sys plugin's getBootType
// returns it to scripts.
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit between GfGameUtil::isCondBladeModel and getBladeMotion and it takes only a blade id. What it
// does: returns GfGameUtil::fn_71002DEFBC(blade) (a tail call); GfAssetSetup::setRefResource calls it.
const char* fn_71002DF344(unsigned int blade);
int fn_71002EEBE4();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to fn_71002EEBE4 (no object). What it does: when run is set, stores type at .bss 0x7100EA4890
// (fn_71002EEBE4's) and, when GfScriptManager is up, loads the "aoc_boot" script (slot 0x46), waits for it to load
// (GfSleep(1)), runs it to its end unless its load failed, destroys it and clears that int again.
// tl::TitleStatePlayGame::enter calls it.
void fn_71002EEB14(int type, bool run);
// Placeholder names: nothing names them (1.0.0's StateUtil::applyDamage calls neither). Free functions because their
// addresses are in GfWeapon's unit after fn_71002EEBE4 and they take no object. What they do: the sum of
// GfBdatBtl::getBTL_EnhanceParam1 over the enhances whose getBTL_EnhanceEnhanceEffect is effect, times 0.01 (0 for
// driver 0 or none): the driver's own enhances (GfDataDriver::fn_7100247580; fn_71002EEBF4) or the orb enhances of
// its blade in slot blade (GfDataDriver::getBlade, GfDataBlade::getEquipOrbEnance; fn_71002EECD4).
// StateUtil::applyDamage adds both for effect 0x108 to its damage cut.
float fn_71002EEBF4(unsigned int driver, unsigned short effect);
float fn_71002EECD4(unsigned int driver, int blade, unsigned short effect);
// Placeholder name: new in 3.0.1 and unnamed in 1.0.0 too (1.0.0's fn_7100356C34, called at the same places of
// GfGameUtil::setWatchedEvent). A free function because its address is in GfWeapon's unit among free placeholders
// and it takes no object of a class. What it does: fills a saved event row: the event, the time of day
// (GfFieldTime::getGameTime when GfFieldTime exists), the map weather id and weather type
// (GfFieldWeather::getCurrentMapWeatherID / getCurrentWtrType(false)) and drivers 1-9's equipped weapon and blade.
void fn_71002EEDC0(SDataGameSavedEvent& row, unsigned int event);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes nothing. What it does: false unless GfGameManager::isInstalledBattleArenaContents is true; then true
// when GfItemUtil::getItemBoxCount(25497) is non-zero, else whether any of the five ints at
// GfDataManager::getDataGame()+0x11AF18/0x11AF0C/0x11AF24/0x11AF30/0x11AF3C is non-zero. GfFieldSound::createMapSound
// loads the "dlc_se_btl_spskill" sound pack when it is true.
bool fn_71002ED330();
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are
// in GfWeapon's unit and they take nothing. What they do: false when the int at 0x10D7C of
// GfDataManager::getDataGameIra() is 0, else whether GfBdatChrDr::getIRA_PartyGuest1 (fn_71002ED9CC) /
// getIRA_PartyGuest2 (fn_71002EDA2C) of it is non-zero. GfMenuObjPartyForm3::initialize shows "LAY_guest@01" /
// "LAY_guest@02" by them (GfGameCond and event::ObjectList call them too).
bool fn_71002ED9CC();
bool fn_71002EDA2C();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders and it takes only a blade id. What it does: true when
// GfGameManager::isGameTypeIra holds, the blade's trust rank (GfDataBlade::getTrustRank) is 5 and its
// getKizunaringMax equals getKizunaringCompleteNum. GfMenuObjBlKizunaRing::procAchieve passes the reference blade.
bool fn_71002EE72C(unsigned int blade);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function, placed as fn_71002EE72C.
// What it does: under fn_71002EE72C's conditions (with max <= complete), clears the byte at 0x8A1 of the blade's
// GfDataBlade::getSDataBlade, GfGameUtil::addTrustRankForKizunaRing, then GfQuestUtil::execReward of
// GfKizunaringUtil::getCompleteKizunaringReward when that gives one. GfMenuObjBlKizunaRing::procAchieve calls it
// when fn_71002EE72C holds.
void fn_71002EE640(unsigned int blade);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: false when fn_71002ED4F0(enemy) gives no record, else whether bit mode of
// that record's flag byte (0x14 bytes each in the game data, at 0x11B4DC) is set. gf_menu_obj_named_list's
// updateNamedIDList passes a named enemy's "EnemyID" and GfMenuObjOption::getDifficultyFromIndex's difficulty; its
// isDefeated passes GfGameManager::getBtlDifficult().
bool fn_71002ED5B0(unsigned int enemy, unsigned int mode);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: -1 when fn_71002ED4F0(id) gives no record, else the int of that record
// (0x14 bytes each in the game data) at 0x11B4CC/D0/D4/D8 for getBtlDifficult() 0/1/2/4 (-1 for other values);
// GfMenuCharDataAdapter::update_EN_DefeatedTime2 shows it as minutes and seconds for an enemy (objType 5).
unsigned int fn_71002ED6B8(unsigned int enemy);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: fn_71002ED6B8 with the record column chosen by mode (0/1/2/4) instead
// of getBtlDifficult(); GfMenuCharDataAdapter::update_EN_DefeatedTime passes GfMenuReference::getReferenceBtlchDifficulty().
unsigned int fn_71002ED608(unsigned int enemy, unsigned int mode);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: unless GfGameManager::isEnableNamedRecord fails or isBattleArenaActive holds, for
// fn_71002ED4F0(enemy)'s record (0x14 bytes each in the game data) keeps the time in the column of mode (0/1/2/4,
// 0x11B4CC..) when the record's flag byte at 0x11B4DC has bit mode, else counts local flag 8/0xFAF up (to 0xFF) when
// GfGameManager::isGameTypeIra holds. SCOM_ENBOOK_BOSS_TIME::exec passes its enemy, its time and
// GfGameManager::getBtlDifficult() (1.0.0 called GfDataEnBook::setClearNamedTime(enemy, time) there).
void fn_71002ED774(unsigned int enemy, unsigned int time, unsigned int mode);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: the address 0x4C bytes into the option data: tl::TitleMain's
// getOptionBuffer when GfManager::isExecModeAdvertize or isExecModeThater holds and TitleMain exists, else
// GfDataManager::getDataOption(). GfArenaBattle::mapjumpForReturnFieldForObjCleanup / execBattleSequence copy 0x3C bytes into it.
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are
// in GfWeapon's unit (no object). What they do: fn_71002EB3FC: whether GfDataBlade::fn_7100231884() lies in
// 11100..11130 (caller fn_7100543F98). fn_71002EDC24 / fn_71002EDC4C: whether a model name contains "pc110601"
// (true / 6, else false / 0; GfAssetSetupEnemy::setup and GfAssetSetupNpc::setup call both). fn_71002EDD60: plays
// menu sound effect 0x2E (GfMenuObjUtil::playSE; GfReqCommand::execChangeBladeWithBladeId calls it).
// fn_71002EE5A0 / fn_71002EE5C0: GfFieldSound's getDlcSePack / fn_710027CEA4 for name when GfFieldSound is up
// (none otherwise; GfComSound::playSe2D calls both).
bool fn_71002EB3FC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit before fn_71002EB3FC (no object). What it does: when GfGameManager::isGameTypeIra holds, whether
// game condition 0xE86 does not hold (GfGameCond::isGameCond); else whether GfDataBlade::fn_7100231884() is below
// 5048. GfMenuObjUtil::getFaceIconID and isIraSinMaskOff test it.
bool fn_71002EB3C0();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: DataParamAcc(handle).getWeaponStability(false);
// btl::PlayerParameter::InitializeAttackParam calls it.
unsigned int fn_71002EC6F4(GF_OBJ_HANDLE* handle);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit before fn_71002EDC24 (no this). What it does: for driver 6 only, whether fn_71002DF39C(6, ...)
// gives a model name containing "pc110601" (false for other drivers); GfAssetSetupDriver::setup and
// GfAssetSetupDriverForUi::setup call it.
bool fn_71002EDBD8(unsigned int driverId, bool createTypeIn2311, bool createType3);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit before its callers fn_71002ED5B0 / ED608 / ED6B8 / ED774 (no this). What it does: the row of
// GfBdatChrEnArrange whose getBTL_NamedListIraEnemyID (when GfGameManager::isGameTypeIra holds, rows getBTL_NamedListIraStart up to
// getBTL_NamedListIraEnd) or getBTL_NamedListEnemyID (rows getBTL_NamedListStart up to getBTL_NamedListEnd) equals enemy; 0 when none does.
unsigned int fn_71002ED4F0(unsigned int enemy);
bool fn_71002EDC24(const char* name);
int fn_71002EDC4C(const char* name);
// Placeholder name: GfWeapon's unit's function (callers GfGameObj::checkEnableGameObj, GfGameUtil::levelupForEnemy and
// GfGameScene::gevChangeGameDifficult, which calls it on every object of list 5). A free function: its class is not known.
void fn_71002E0F28(GF_OBJ_HANDLE* handle);
void fn_71002EDD60();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among its free placeholders and it takes no object. What it does: for drivers 1, 2, 3, 5 and 6
// sets their blades back (mercenary blades by GfGameUtil::execEquipMercenariesBlade, then the equipped one) and
// answers whether one was equipped; GfArenaParty::removeFieldBlade passes (false, true).
bool fn_71002EC268(bool, bool);
fw::SoundPack* fn_71002EE5A0(const char* name);
const char* fn_71002EE5C0(const char* name);
void* fn_71002EE8C4();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to fn_71002EE8C4 (no object). What it does: calls fn_7100254EF0 with type on the same
// SSoundUiOption fn_71002EE8C4 returns (GfArenaBattle::execBattleSequence calls it).
void fn_71002EE954(unsigned int type);
// Placeholder name: the symbols leave it unnamed. A free function because its address is in GfWeapon's unit
// (no object; callers GfBladeCreate::createBladeNewVersion and fn_71002EDAD4). What it does: whether the add-on
// blade is unlocked: 0x451 asks GfGameAoc::fn_71002A75DC(0x20101), 0x452/0x453 GfGameManager::isInstalledBattleArenaContents,
// 0x457 that one too, item 25497 in the box and a first rule value set in row 25 of SDataGame's challenge rule
// table; every other blade is.
bool fn_71002ED3E8(unsigned int blade);
// Placeholder name: the symbols leave it unnamed. A free function because its address is in GfWeapon's unit
// (right after GfGameUtilHana::setupDefaultParts, its one caller; no object). What it does: unless the party already
// holds as many items of the item's BDAT range as GfItemUtil::getEnableStock(item) allows (item 0 skips that test),
// takes one away (addItemBox(id, -1)) of the id of the range the box holds most of that has an unequipped handle.
void fn_71002E8CD4(unsigned int item);
// Placeholder name: the symbols leave it unnamed. A free function because its address is in GfWeapon's unit
// (between GfGameUtilShop's functions; no object) and its one caller, GfPartySelect::getDriverList, is in another
// unit. What it does: appends driver ids to the list: 17..25 for which GfDataDriver::isIraFront holds while
// GfDataBlade::fn_71002324C8's flag is set, else 1..8 (5 left out while GfDataBlade::fn_710023220C holds); returns
// whether the list holds any.
bool fn_71002E66F8(mm::mtl::FixedVector<unsigned short, 32>& list);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: whether a blade is available: true for most IDs; 0x451..0x453 and 0x457
// depend on GfGameAoc's content state and GfGameManager::isInstalledBattleArenaContents. GfArenaParty::addFieldBlade / removeFieldBlade
// test it for each blade of GfBdatChrBl's range.
bool fn_71002EDAD4(unsigned int blade);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. Free functions because their addresses
// are in GfWeapon's unit (no object). Each reads the option data (tl::TitleMain::getOptionBuffer in advertize/theater
// mode, else GfDataManager::getDataOption()). What they do: fn_71002EC634: its byte 0x6F (as unsigned int); fn_71002EDA8C: byte 0x82
// is set; fn_71002EE9A4: byte 0x84 is 0; fn_71002EE9EC / fn_71002EEA34 / fn_71002EEA7C: byte 0x7F / 0x80 / 0x81 is
// set; fn_71002EE904: passes value to fn_7100254FDC on the SSoundUiOption at +0x4C. GfGameManager's statics
// getBtlDifficult, reqestEventAutoSave, isEnableSpecialBgm, isEnableAutoBattle/9A0/9A4 and getBtlDifParam call them.
unsigned int fn_71002EC634();
bool fn_71002EDA8C();
bool fn_71002EE9A4();
bool fn_71002EE9EC();
bool fn_71002EEA34();
bool fn_71002EEA7C();
void fn_71002EE904(unsigned int value);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit after fn_71002EEA7C, the same shape (no object). What it does: whether byte 0x83 of the option data
// (as fn_71002EE9EC reads it) is set; GfMenuManager::gevPlayerControl tests it.
bool fn_71002EEAC4();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: a driver's class from the average trust rank (1..6) of the driver's
// active party blades (GfDataDriver::getIraBack, GfGameUtil::getTrustRank) through GfBdatChrDr::getChrDrIraParam,
// getChrIrGroupID and GfBdatBtl::getBTL_IrGroupRevGroupRev; GfMenuCharDataAdapter::update_DR_ClassBuffLv uses it for the
// add-on (isValidExpansion(3)) driver class.
unsigned int fn_71002DC130(unsigned int driver);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: for each of 20 table rows (0x71009BBDC4 area) whose arts match the blade's
// (DataParamAcc(3, blade) getBladeArts(slot)) at a high enough getBladeArtsLevel (and whose quest, if any, is ordered),
// raises local flag 8 (row + 0xF9E) by one up to the row's limit. Caller: SCOM_ACHIEV_INC::createBladeArts with the
// blade's bdat id and the arts slot (0..2).
void fn_71002EE784(unsigned int blade, unsigned int slot);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in GfWeapon's unit
// and it takes no this. What it does: true for quest 0x8FD, and for quest 0x80B's task 1 (it builds that task's
// QuestTaskParam first); false otherwise. Callers: GfQuestTarget::getIconType, fn_710030A840 and
// GfMenuLocation::refreshLocatorFromQuest, which makes no locator for a task it holds for.
bool fn_71002EE5E0(QuestID quest, unsigned int task);
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are in
// GfWeapon's unit (no this). What they do: when the arena game mode (GfGameArena::sys()) exists, send it a
// MsgUnk_1000034 of type 0xE (fn_71002DA4FC), 0xF (fn_71002DA570) or 0x10 (fn_71002DA5E4) carrying value in its
// parameter word 0x30, 0x34 or 0x38. Callers: the exec of the requests SCOM_ADD_ECUBE and SCOM_ADD_SCORE (their value at
// 0x1C) and gf_req_scom's SCOM_CLEAR_TIME::create.
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders and it takes only a handle. What it does: false unless the object is a
// driver (GfObjUtil::getObjType 3); true when it is driver 0x11 whose GfComAsm (component 2) plays a layer-0 state
// whose name holds "btstart", else whether GfMountManager::getMountType(handle, 0) is 1 or 3.
// PlayerCameraTarget::writeTargetInfo takes it as m_isRiding in a battle.
bool fn_71002DA394(GF_OBJ_HANDLE* handle);
void fn_71002DA4FC(int value);
void fn_71002DA570(int value);
void fn_71002DA5E4(unsigned int value);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders (no this). What it does: GfGameUtil::addExpBattle's per-driver step
// (it tail-calls it for one driver and calls it for each party driver): the driver's battle experience, level up
// (GfDataDriver::setLevel, SCOM_FIELD_VOICE::createLevelup, SCOM_MAXIMUM_HEAL, GfEvent::callDriverLevel).
void fn_71002DAD5C(unsigned int driver, unsigned int exp);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders (no this). What it does: GfGameUtil::addExpInn's per-driver step (also
// called by fn_71002DAD5C and itself): adds experience through DataParamAcc and GfDataDriver.
void fn_71002DA8FC(unsigned int driver, unsigned int exp);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes no object. What it does: for blade 1001, else 1002 (the first GfDataBlade::fn_71002383C8
// holds for), cancels the mission of the blade's mercenary team (GfGameMercenaries::cancelMission of
// GfDataMercenaries::getMissionIdByBlade) and clears that team's members (clearTeamMember of getTeamID);
// GfGameScene::gevChangeScenarioFlag calls it.
void fn_71002E1824();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes only a handle (no this). What it does: in the arena (GfGameArena::isBattleNow holds)
// GfGameArena::getWeaponDamage(handle), else DataParamAcc(handle).getWeaponDamage(false), as fn_71002EC6F4 does for the
// stability; btl::PlayerParameter::InitializeAttackParam calls it.
unsigned int fn_71002EC674(GF_OBJ_HANDLE* handle);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among GfGameUtil's experience functions and it takes no object. What it does: for a driver other
// than 0, lowers its experience (DataParamAcc(3, driver).getExp()) by exp, down to 0 (at most 999999999), stores it
// (GfDataDriver::setExp) and, for a DLC driver row (isIra), calls getIraFront on it;
// GfMenuObjBalloon::SelMoneyListener::reciveEvent calls it.
void fn_71002DAB40(unsigned int driver, unsigned int exp);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes only a handle (no this). What it does: for a handle other than -1, sets the alpha of
// its "medal" extra mesh (GfObjAcc::getExtMeshIdx, setExtMeshAlpha) to 1 when show is set, else 0; fn_7100543F98
// calls it.
void fn_71002E24C0(GF_OBJ_HANDLE* handle, bool show);
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are
// in GfWeapon's unit (no this). What they do: when GfGameScene is up, GfGameScene::setIraBoneMount(handle, target,
// flag) with kind 0 (fn_71002ED96C) or 1 (fn_71002ED99C); btl::BattleCharacter::SetAction / AsmCallback call them.
void fn_71002ED96C(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag);
void fn_71002ED99C(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag);
}  // namespace gf

#endif
