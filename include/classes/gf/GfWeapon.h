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
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit next to GfGameUtil::getDriverModel, its caller (no this). What it does: the model name of the first of the
// driver's three accessories (GfDataDriver::getEquipAcce) whose GfBdatItem::getPcEquipModel name is non-empty and whose
// getPcEquipDriver is the driver ("pc/pc110602" instead of "pc/pc110601" for driver 6 with flag set); none otherwise.
// GfGameUtil::getDriverModel and GfGameUtil::getAcceDriverModel try it first.
const char* fn_71002DF4C4(unsigned int driverId, bool flag);
// Placeholder name: new in 3.0.1 and unnamed in 1.0.0 too (1.0.0's fn_7100356C34, called at the same places of
// GfGameUtil::setWatchedEvent). A free function because its address is in GfWeapon's unit among free placeholders
// and it takes no object of a class. What it does: fills a saved event row: the event, the time of day
// (GfFieldTime::getGameTime when GfFieldTime exists), the map weather id and weather type
// (GfFieldWeather::getCurrentMapWeatherID / getCurrentWtrType(false)) and drivers 1-9's equipped weapon and blade.
void fn_71002EEDC0(SDataGameSavedEvent& row, unsigned int event);
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
// Placeholder name: the symbols leave it unnamed. A free function because its address is in GfWeapon's unit
// (right after GfGameUtilHana::setupDefaultParts, its one caller; no object). What it does: unless the party already
// holds as many items of the item's BDAT range as GfItemUtil::getEnableStock(item) allows (item 0 skips that test),
// takes one away (addItemBox(id, -1)) of the id of the range the box holds most of that has an unequipped handle.
void fn_71002E8CD4(unsigned int item);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its code is in GfWeapon's unit
// and it takes no this. What it does: true for quest 0x8FD, and for quest 0x80B's task 1 (it builds that task's
// QuestTaskParam first); false otherwise. Callers: GfQuestTarget::getIconType, fn_710030A840 and
// GfMenuLocation::refreshLocatorFromQuest, which makes no locator for a task it holds for.
bool fn_71002EE5E0(QuestID quest, unsigned int task);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders (no this). What it does: GfGameUtil::addExpBattle's per-driver step
// (it tail-calls it for one driver and calls it for each party driver): the driver's battle experience, level up
// (GfDataDriver::setLevel, SCOM_FIELD_VOICE::createLevelup, SCOM_MAXIMUM_HEAL, GfEvent::callDriverLevel).
void fn_71002DAD5C(unsigned int driver, unsigned int exp);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
// GfWeapon's unit among free placeholders (no this). What it does: GfGameUtil::addExpInn's per-driver step (also
// called by fn_71002DAD5C and itself): adds experience through DataParamAcc and GfDataDriver.
void fn_71002DA8FC(unsigned int driver, unsigned int exp);
}  // namespace gf

#endif
