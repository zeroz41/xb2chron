#ifndef CLASSES_GF_GFWEAPON_H
#define CLASSES_GF_GFWEAPON_H

#include "classes/gf/GfAppendHandles.h"

namespace fw { class SoundPack; }
namespace gf { class QuestID; }
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
// fn_710024F910's result. GfAssetSetupDriver's getMdlFile/getArcFile pass (id, create type in {2, 3, 11},
// create type == 3), GfAssetSetupNpc::getMdlFile (id, false, create type == 3) for ids below 26.
const char* fn_71002DF39C(unsigned int driverId, bool createTypeIn2311, bool createType3);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to fn_71002DF39C, its caller (no this). What it does: the model name of the first of the
// driver's three accessories (GfDataDriver::getEquipAcce) whose GfBdatItem::fn_7100203698 name is non-empty and whose
// fn_7100203610 is the driver ("pc/pc110602" instead of "pc/pc110601" for driver 6 with flag set); none otherwise.
// fn_71002DF39C and fn_71002DF624 try it first.
const char* fn_71002DF4C4(unsigned int driverId, bool flag);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit after fn_71002DF4C4 (no this). What it does: fn_71002DF4C4(id, flag), where for driver 6 with
// the second argument set flag also takes GfDataEvent::fn_710024F910 of GfGameEvent::fn_71002A0FEC() (as
// fn_71002DF39C does). GfAssetSetup::setRefResource calls it.
const char* fn_71002DF624(unsigned int driverId, bool check, bool flag);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes only a handle (no this). What it does: false for handle -1, a GfObjAcc with no
// object, a destroyed object (isDestroy) or one with flag 0x11 (testFlag); for an object of type 6 whose bound
// gimmick (gmk::getBindedGmkInst) has type 3 (its slot 2), whether the "flag" column of the gimmick's BDAT row
// (getBindedBdatFp, its row at 0x38) holds the flag named "HITONOWAGET" (Bdat::getFlagVal) is nonzero.
// GfMenuGfObjAdapter::fn_7100340094 calls it.
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
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes nothing. What it does: false unless GfGameManager::fn_71002AC598 is true; then true
// when GfItemUtil::getItemBoxCount(25497) is non-zero, else whether any of the five ints at
// GfDataManager::getDataGame()+0x11AF18/0x11AF0C/0x11AF24/0x11AF30/0x11AF3C is non-zero. GfFieldSound::createMapSound
// loads the "dlc_se_btl_spskill" sound pack when it is true.
bool fn_71002ED330();
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are
// in GfWeapon's unit and they take nothing. What they do: false when the int at 0x10D7C of
// GfDataManager::fn_7100224A10() is 0, else whether GfBdatChrDr::fn_71001F1AEC (fn_71002ED9CC) /
// fn_71001F1B74 (fn_71002EDA2C) of it is non-zero. GfMenuObjPartyForm3::initialize shows "LAY_guest@01" /
// "LAY_guest@02" by them (GfGameCond and event::ObjectList call them too).
bool fn_71002ED9CC();
bool fn_71002EDA2C();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders and it takes only a blade id. What it does: true when
// GfGameManager::fn_71002A9E68 holds, the blade's trust rank (GfDataBlade::getTrustRank) is 5 and its
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
// fn_7100445F58 passes a named enemy's "EnemyID" and GfMenuObjOption::fn_7100452BC0's difficulty; its
// fn_7100446C54 passes GfGameManager::fn_71002AC57C().
bool fn_71002ED5B0(unsigned int enemy, unsigned int mode);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: -1 when fn_71002ED4F0(id) gives no record, else the int of that record
// (0x14 bytes each in the game data) at 0x11B4CC/D0/D4/D8 for fn_71002AC57C() 0/1/2/4 (-1 for other values);
// GfMenuCharDataAdapter::fn_7100339108 shows it as minutes and seconds for an enemy (objType 5).
unsigned int fn_71002ED6B8(unsigned int enemy);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: fn_71002ED6B8 with the record column chosen by mode (0/1/2/4) instead
// of fn_71002AC57C(); GfMenuCharDataAdapter::fn_7100339058 passes GfMenuReference::fn_7100369304().
unsigned int fn_71002ED608(unsigned int enemy, unsigned int mode);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: unless GfGameManager::fn_71002AC64C fails or fn_71002AC580 holds, for
// fn_71002ED4F0(enemy)'s record (0x14 bytes each in the game data) keeps the time in the column of mode (0/1/2/4,
// 0x11B4CC..) when the record's flag byte at 0x11B4DC has bit mode, else counts local flag 8/0xFAF up (to 0xFF) when
// GfGameManager::fn_71002A9E68 holds. SCOM_ENBOOK_BOSS_TIME::exec passes its enemy, its time and
// GfGameManager::fn_71002AC57C() (1.0.0 called GfDataEnBook::setClearNamedTime(enemy, time) there).
void fn_71002ED774(unsigned int enemy, unsigned int time, unsigned int mode);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: the address 0x4C bytes into the option data: tl::TitleMain's
// getOptionBuffer when GfManager::isExecModeAdvertize or isExecModeThater holds and TitleMain exists, else
// GfDataManager::getDataOption(). TUnk_B52C38::fn_710028D584 / fn_710028CFF8 copy 0x3C bytes into it.
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are
// in GfWeapon's unit (no object). What they do: fn_71002EB3FC: whether GfDataBlade::fn_7100231884() lies in
// 11100..11130 (caller fn_7100543F98). fn_71002EDC24 / fn_71002EDC4C: whether a model name contains "pc110601"
// (true / 6, else false / 0; GfAssetSetupEnemy::setup and GfAssetSetupNpc::setup call both). fn_71002EDD60: plays
// menu sound effect 0x2E (GfMenuObjUtil::playSE; GfReqCommand::execChangeBladeWithBladeId calls it).
// fn_71002EE5A0 / fn_71002EE5C0: GfFieldSound's fn_710027CE60 / fn_710027CEA4 for name when GfFieldSound is up
// (none otherwise; GfComSound::playSe2D calls both).
bool fn_71002EB3FC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit before fn_71002EB3FC (no object). What it does: when GfGameManager::fn_71002A9E68 holds, whether
// game condition 0xE86 does not hold (GfGameCond::isGameCond); else whether GfDataBlade::fn_7100231884() is below
// 5048. GfMenuObjUtil::getFaceIconID and fn_710048FCF8 test it.
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
// GfBdatChrEnArrange whose fn_71001F4EB8 (when GfGameManager::fn_71002A9E68 holds, rows fn_71001F4E70 up to
// fn_71001F4E7C) or fn_71001F4DE8 (rows fn_71001F4DA0 up to fn_71001F4DAC) equals enemy; 0 when none does.
unsigned int fn_71002ED4F0(unsigned int enemy);
bool fn_71002EDC24(const char* name);
int fn_71002EDC4C(const char* name);
// Placeholder name: GfWeapon's unit's function (callers GfGameObj::checkEnableGameObj, GfGameUtil::levelupForEnemy and
// GfGameScene::fn_71002C5994, which calls it on every object of list 5). A free function: its class is not known.
void fn_71002E0F28(GF_OBJ_HANDLE* handle);
void fn_71002EDD60();
fw::SoundPack* fn_71002EE5A0(const char* name);
const char* fn_71002EE5C0(const char* name);
void* fn_71002EE8C4();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to fn_71002EE8C4 (no object). What it does: calls fn_7100254EF0 with type on the same
// SSoundUiOption fn_71002EE8C4 returns (TUnk_B52C38::fn_710028CFF8 calls it).
void fn_71002EE954(unsigned int type);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: whether a blade is available: true for most IDs; 0x451..0x453 and 0x457
// depend on TUnk_B54858's content state and GfGameManager::fn_71002AC598. TUnk_28D7B8::fn_710028DA24 / fn_710028DAB4
// test it for each blade of GfBdatChrBl's range.
bool fn_71002EDAD4(unsigned int blade);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. Free functions because their addresses
// are in GfWeapon's unit (no object). Each reads the option data (tl::TitleMain::getOptionBuffer in advertize/theater
// mode, else GfDataManager::getDataOption()). What they do: fn_71002EC634: its byte 0x6F (as unsigned int); fn_71002EDA8C: byte 0x82
// is set; fn_71002EE9A4: byte 0x84 is 0; fn_71002EE9EC / fn_71002EEA34 / fn_71002EEA7C: byte 0x7F / 0x80 / 0x81 is
// set; fn_71002EE904: passes value to fn_7100254FDC on the SSoundUiOption at +0x4C. GfGameManager's statics
// fn_71002AC57C, fn_71002AC6A8, fn_71002AC89C, fn_71002AC99C/9A0/9A4 and fn_71002AC578 call them.
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
// active party blades (GfDataDriver::fn_71002416B4, GfGameUtil::getTrustRank) through GfBdatChrDr::fn_71001F13E0,
// fn_71001F172C and GfBdatBtl::fn_71001EA310; GfMenuCharDataAdapter::update_DR_ClassBuffLv uses it for the
// add-on (fn_710048FD30(3)) driver class.
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
// GfWeapon's unit (no this). What they do: when the arena game mode (TUnk_B535D0::sys()) exists, send it a
// MsgUnk_1000034 of type 0xE (fn_71002DA4FC), 0xF (fn_71002DA570) or 0x10 (fn_71002DA5E4) carrying value in its
// parameter word 0x30, 0x34 or 0x38. Callers: the exec of the requests TUnk_B6AF70 and TUnk_B6AFA0 (their value at
// 0x1C) and gf_req_scom's fn_7100558E88.
void fn_71002DA4FC(int value);
void fn_71002DA570(int value);
void fn_71002DA5E4(unsigned int value);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes no object. What it does: for blade 1001, else 1002 (the first GfDataBlade::fn_71002383C8
// holds for), cancels the mission of the blade's mercenary team (GfGameMercenaries::cancelMission of
// GfDataMercenaries::getMissionIdByBlade) and clears that team's members (clearTeamMember of getTeamID);
// GfGameScene::gevChangeScenarioFlag calls it.
void fn_71002E1824();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes only a handle (no this). What it does: in the arena (TUnk_B535D0::fn_7100291D54 holds)
// TUnk_B535D0::fn_7100291E14(handle), else DataParamAcc(handle).getWeaponDamage(false), as fn_71002EC6F4 does for the
// stability; btl::PlayerParameter::InitializeAttackParam calls it.
unsigned int fn_71002EC674(GF_OBJ_HANDLE* handle);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among GfGameUtil's experience functions and it takes no object. What it does: for a driver other
// than 0, lowers its experience (DataParamAcc(3, driver).getExp()) by exp, down to 0 (at most 999999999), stores it
// (GfDataDriver::fn_71002448D8) and, for a DLC driver row (fn_710023F9A8), calls fn_71002417DC on it;
// GfMenuObjBalloon::SelMoneyListener::reciveEvent calls it.
void fn_71002DAB40(unsigned int driver, unsigned int exp);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes only a handle (no this). What it does: for a handle other than -1, sets the alpha of
// its "medal" extra mesh (GfObjAcc::getExtMeshIdx, setExtMeshAlpha) to 1 when show is set, else 0; fn_7100543F98
// calls it.
void fn_71002E24C0(GF_OBJ_HANDLE* handle, bool show);
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their addresses are
// in GfWeapon's unit (no this). What they do: when GfGameScene is up, GfGameScene::fn_71002C4C0C(handle, target,
// flag) with kind 0 (fn_71002ED96C) or 1 (fn_71002ED99C); btl::BattleCharacter::SetAction / AsmCallback call them.
void fn_71002ED96C(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag);
void fn_71002ED99C(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag);
}  // namespace gf

#endif
