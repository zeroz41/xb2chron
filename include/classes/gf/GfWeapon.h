#ifndef CLASSES_GF_GFWEAPON_H
#define CLASSES_GF_GFWEAPON_H

#include "classes/gf/GfAppendHandles.h"

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
int fn_71002EEBE4();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit and it takes nothing. What it does: false unless GfGameManager::fn_71002AC598 is true; then true
// when GfItemUtil::getItemBoxCount(25497) is non-zero, else whether any of the five ints at
// GfDataManager::getDataGame()+0x11AF18/0x11AF0C/0x11AF24/0x11AF30/0x11AF3C is non-zero. GfFieldSound::createMapSound
// loads the "dlc_se_btl_spskill" sound pack when it is true.
bool fn_71002ED330();
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
void* fn_71002EE8C4();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit (no this). What it does: whether a blade is available: true for most IDs; 0x451..0x453 and 0x457
// depend on TUnk_B54858's content state and GfGameManager::fn_71002AC598. TUnk_28D7B8::fn_710028DA24 / fn_710028DAB4
// test it for each blade of GfBdatChrBl's range.
bool fn_71002EDAD4(unsigned int blade);
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
}  // namespace gf

#endif
