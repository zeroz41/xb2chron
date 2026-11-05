#ifndef GF_GFDATADRIVER_H
#define GF_GFDATADRIVER_H

namespace gf { class SDataDriver; enum DBSLOT : int; struct GfItemHandle; enum PTPOS : unsigned int; }
namespace gf { struct SDataPouch; }
namespace gf { struct SDataIra; struct SDataDriverArtsEx; }
namespace gf { enum FAVORITE : int; }
namespace gf { struct SDataIdea; class GfInitParamDriver; }

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}
namespace mm { namespace mtl { template <int> class FixStr; } }

namespace gf {
// the drivers' data (functions, by its symbols)
class GfDataDriver {
public:
    static int getMaxSetBladeNum(unsigned int driver);  // how many blades the driver can engage
    static bool isActivateUnuse(unsigned int driver);
    // the slot of the driver's engaged blade
    static int getBladeSet(unsigned int driver);
    // the blade in the driver's slot (GfMenuObjBladeSwitch::update asks GfMenuObjUtil::isValidBlade about it)
    static unsigned int getBlade(unsigned int driver, int slot);
    // the weapon types of the driver's equipped arts (its data's list: GfDataDriver::getEquipWpnType(types,
    // const SDataDriver&)). Room for 50 in 3.0.1: GfMenuObjDrArtsSet2 holds one with its count 0xC8 bytes past the
    // room (1.0.0 named the type with 27)
    static void getEquipWpnType(mm::mtl::FixedVector<unsigned int, 50>& types, unsigned int driver);
    // the weapon types (1-4) of the driver's arts types 1-49 (CHR_Dr's weapon type columns); room for 50 in 3.0.1 (its
    // push_back checks 50, its count sits 0xC8 bytes past the room; 1.0.0's symbol named the type with 27)
    static void getEquipWpnType(mm::mtl::FixedVector<unsigned int, 50>& types, const SDataDriver& data);
    // 1.0.0's and 2.0.0's names (same call sites, same arguments; 3.0.1's also cover the DLC drivers)
    static SDataDriver* getSDataDriver(unsigned int driver);  // getSDataDriver
    // the driver's arts records past the ones its data keeps, found the getSDataDriver way (DLC rows 0x11-0x19 in
    // GfDataManager::getDataGameIra's, others in getDataGame's 16, clamped as getSDataDriver clamps); inline in
    // getDriverWeaponType, getDriverArtsLevel, setDriverArtsLevel and GfDataDriverArts::getArtsLevel. The name is not the original's.
    static SDataDriverArtsEx* getSDataDriverArtsEx(unsigned int driver);
    static unsigned int getLevel(const SDataDriver& data);  // getLevel
    // 1.0.0's name: its getLevel(unsigned int) has the same callers (GfMenuObjDrArtsSet2::ArtsListListener,
    // GfMenuObjLvupSelect's listeners) and reads getLevel(*getSDataDriver(driver)); 2.0.0's symbols name it
    static unsigned int getLevel(unsigned int driver);
    // 2.0.0's symbols name it. What it does: for a DLC driver row (0x11-0x19) whose CHR_Ir "Type" is set, finds the
    // first CHR_Ir row of the same "GroupID" whose Type is 0 and returns its "driverID" (0x11 when there is none); any
    // other row comes back as is.
    static unsigned int getIraFront(unsigned int driver);
    // the experience a driver needs to reach level (GfMenuCharDataAdapter::update_DR_ExpNextVirtual)
    static unsigned int getExpSetLevel(unsigned int driver, unsigned int level);
    // 2.0.0's symbols name it. What it does: 0 unless driver is a DLC driver row (0x11-0x19); then it walks
    // getIraFront(driver) and its getIraBack list and returns a driver id; GfMenuCharDataAdapter::update_IRA_BackDrFace
    // shows that driver's face icon.
    static unsigned int getIraBack(unsigned int driver);
    // 2.0.0's symbols name it. What it does: answers fn_7100241E10(driver, list) for a local list (a 0x350-byte buffer
    // and its size, cleared afterwards); GfGameUtil::equipDriverBladeForce does nothing for a driver it holds for.
    static bool equipDriverBladeFromReserverBlade(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit right after equipDriverBladeFromReserverBlade, which passes it a driver id and a FixedVector<unsigned short, 424> (0x350-byte
    // room). What it does: fills the list with GfDataBlade::getListReserver's blades, drops those already listed and
    // the ones GameFlag / GfDataDriver::isEnableEquipBlade reject, and answers whether one is left (0x440 bytes).
    static bool fn_7100241E10(unsigned int driver, mm::mtl::FixedVector<unsigned short, 424>& list);
    // 2.0.0's symbols name it. What it does: the first of the driver's three blade slots (SDataDriver::m_blades)
    // holding a GfDataBlade::isDummyBlade blade, -1 for none. Caller: gf::GfGameUtil::execPartyBladeFollow.
    static int getSetIdByDummyBlade(unsigned int driver);
    // 2.0.0's symbols name it. What it does: for a DLC driver row (0x11-0x19) collects every GfBdatChrDr row of type 1
    // whose group (getChrIrGroupID) equals the driver's into the list (getChrIrdriverID's 16-bit ids) and answers
    // whether the list is non-empty; any other row: false. Callers include GfDataDriver::getIraBlade, getListPartyAll
    // and GfMenuCharDataAdapter's ReferenceBladeSetConverter::getCharData.
    static bool getIraBack(mm::mtl::FixedVector<unsigned short, 32>& list, unsigned int driver);
    // 2.0.0's symbols name it. What it does: finds the driver's row (DLC rows 0x11-0x19 through
    // GfDataManager::getDataGameIra, others in getDataGame) and tail-calls GfDataDriver::getEnableLevel with the two
    // outputs and the row, which stores the reachable level (from the row's level at 0x94 and GfBdatBtl's growth table)
    // and a second value and returns true when it found one. GfMenuObjLvupSelect::SelectListener takes the first output
    // as the level select's maximum.
    static bool getEnableLevel(unsigned int& level, unsigned int& value, unsigned int driver);
    // 2.0.0's symbols name it. What it does: true for a driver outside the DLC rows 0x11-0x19; for those, whether
    // GfBdatChrDr::getChrIrType of the row GfBdatChrDr::getChrDrIraParam gives is 0. Caller here:
    // gf_menu_obj_char_select_ira's mnu_chr_sel_ira::setReferenceChar (driver 0 and 1 references both set to it when true).
    static bool isIraFront(unsigned int driver);
    // 2.0.0's symbols name it. What it does: pushes every GfBdatChrDr row id from getChrIrStart up to (not including)
    // getChrIrEnd (getChrIrdriverID) into drivers; true when drivers is not empty.
    static bool getListIra(mm::mtl::FixedVector<unsigned short, 32>& drivers);
    // whether the driver (data type 1) is in a party slot below 3 (GfDataParty::getDriverPartyID)
    static bool isActivateParty(unsigned int driver);
    static unsigned int getExp(const SDataDriver& data);  // getExp
    static unsigned int getBattleExp(const SDataDriver& data);  // getBattleExp
    static unsigned int getExpNextLevel(const SDataDriver& data);  // getExpNextLevel
    static unsigned int getBattleExpNextLevel(const SDataDriver& data);  // getBattleExpNextLevel
    static void addSkillPoint(SDataDriver& data, int point);  // addSkillPoint
    static bool isScenarioMask(unsigned int driver);  // isScenarioMask
    static unsigned int getEquipAcce(const SDataDriver& data, unsigned int slot);  // getEquipAcce
    static void setEquipAcce(SDataDriver& data, unsigned int slot, unsigned int accessory);  // setEquipAcce
    // 1.0.0's name: GfEquipUtil::getEquipDriverAcce(driver, slot) tail-calls it in both builds (1.0.0:
    // GfDataDriver::getEquipAcce(unsigned int, unsigned int)); the symbols spell 3.0.1's copy fn_7100247794
    static unsigned int getEquipAcce(unsigned int driver, unsigned int slot);
    // 2.0.0's symbols name them. What they do: getDriverArtsLevel returns the level byte of arts `arts` of the driver
    // (same code as GfDataDriverArts::getArtsLevel: DLC rows 0x11-0x19 through GfDataManager::getDataGameIra, others in
    // getDataGame's 0x5A0-byte records); setDriverArtsLevel stores it (DataObjDriver::setDriverArtsLevel clamps the
    // level to 5 first).
    static unsigned int getDriverArtsLevel(unsigned int driver, unsigned int arts);
    static void setDriverArtsLevel(unsigned int driver, unsigned int arts, unsigned int level);
    // 2.0.0's symbols name them. Static members for the same reason (after getEquipAcce fn_7100247794, a driver id).
    // What they do: the 20-byte arts slot record `index` of the driver's row (getDriverWeaponType: +0xC0 of the row,
    // getDriverWeaponTypeIraBack / getDriverWeaponTypeIraSwitch: two DLC-table variants); DataObjDriver::getDriverArts
    // indexes the words of it, its third argument (0, 1, 2) picking which.
    static unsigned int* getDriverWeaponType(unsigned int driver, unsigned int index);
    static unsigned int* getDriverWeaponTypeIraBack(unsigned int driver, unsigned int index);
    static unsigned int* getDriverWeaponTypeIraSwitch(unsigned int driver, unsigned int index);
    // 1.0.0's name: GfPouchUtil::getPouch calls it in both builds (1.0.0: GfDataDriver::getPouchData(unsigned int,
    // unsigned int)); the symbols spell 3.0.1's copy fn_71002409CC
    static SDataPouch* getPouchData(unsigned int driver, unsigned int pouch);
    // 2.0.0's symbols name it. What it does: resolves the driver's row (a DLC row 0x11-0x19 from
    // GfDataManager::getDataGameIra's 0xDAC-byte table, else getDataGame's 0x5A0-byte records), then the row its u16 at
    // +0x22 names, and returns bit 31 of that row's word at +0x2E8 (the word whose low 16 bits hold an accessory). Its
    // one caller is GfEquipUtil::isEnableExtendDriverAcce.
    static bool isEnableExtendEquipAcce(unsigned int driver);
    // 2.0.0's symbols name it. What it does: resolves the same row and sets (flag true) or clears bit 31 of its word at
    // +0x2E8. Its one caller is GfEquipUtil::setEnableExtendDriverAcce.
    static void setEnableExtendEquipAcce(unsigned int driver, bool flag);
    // 2.0.0's symbols name it. What it does: for a DLC driver (0x11-0x19) the 16-bit item id at +0x5A4 of its row of
    // GfDataManager::getDataGameIra's driver table, else 0.
    static unsigned int getEquipWpnAcce(unsigned int driver);
    // false for a negative slot, or (engaging) when the slot's blade is not set to this driver: the slot is cleared
    static bool setEquipBlade(unsigned int driver, bool engage, int slot);
    // 2.0.0's symbols name it. What it does: true for rows 0x11 to 0x19 (the DLC drivers, whose data
    // GfDataDriver::getSDataDriver reads from a separate table of 0xDAC-byte records).
    static bool isIra(unsigned int driver);
    // 2.0.0's symbols name it. What it does: the DLC driver's record in that table (rows 0x11 to 0x19, others clamped);
    // DataObjDriver keeps it when isIra accepts the row.
    static SDataIra* getSDataIra(unsigned int driver);

    static const char* getName(unsigned int driver);
    // the message table and row of the driver's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int driver);
    static const char* getModelResourceName(unsigned int driver);
    static const char* getMotionResourceName(unsigned int driver);
    // 2.0.0's symbols name it (carried as getDebugName before); DataObjDriver::getEffectResourceName returns it
    static const char* getEffectResourceName(unsigned int driver);
    static unsigned int getEyeRotControl(unsigned int driver);
    static unsigned int getSkillPoint(const SDataDriver& data);
    static unsigned int getClass(const SDataDriver& data);
    static int getBladeSet(const SDataDriver& data);
    static int getMaxSetBladeNum(const SDataDriver& data);
    static unsigned int getRace(unsigned int driver);
    static unsigned int getFootStep(unsigned int driver);
    static unsigned int getFootStepEffect(unsigned int driver);
    static const char* getVoiceStr(const SDataDriver& data);
    static unsigned int getFavorite(unsigned int driver, FAVORITE favorite);
    // whether the favorite has been used (seen). 2.0.0's symbols name it; 1.0.0's
    // GfMenuObjUtil::getFavoriteStat calls GfDataDriver::isUsedFavorite(driver, favorite) where 3.0.1's calls
    // isUsedFavorite with the same arguments (3.0.1's body also handles drivers 17-25)
    static bool isUsedFavorite(unsigned int driver, FAVORITE favorite);

    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrOffsetID for the row (DataObjDriver::getMenuOffset
    // returns it).
    static int getMenuOffset(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrCenterBone for the row (DataObjDriver::getCenterBone
    // returns it).
    static const char* getCenterBone(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrCamBone for the row (DataObjDriver::getCamBone
    // returns it).
    static const char* getCamBone(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrChestHeight for the row
    // (DataObjDriver::getChestHeight returns it).
    static unsigned int getChestHeight(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrLandingHeight for the row
    // (DataObjDriver::getLandingHeight returns it).
    static unsigned int getLandingHeight(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrStill for the row (DataObjDriver::getIconData returns
    // it).
    static unsigned int getIconData(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfBdatChrDr::getChrDrGender for the row (DataObjDriver::getGender returns
    // it).
    static unsigned int getGender(unsigned int driver);
    // 2.0.0's symbols name it. What it does: pushes onto enhances the equipment enhance ids
    // (GfBdatItem::getPcEquipEnhance1) of the driver's equipped items (the game data's driver rows, 0x5A0 apart;
    // drivers 0x11-0x19 from another table, 0xDAC apart); GfFobjManager::updateEnhanceEffect passes its party leader's
    // driver id and sums the "EnhanceEffect" 0xFB rows.
    static bool getEquipAcceEnahnce(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int driver);
    // 2.0.0's symbols name it. What it does: fills enhances with the enhance ids that apply to the driver (its row at
    // data+0x22, the DLC drivers 0x11-0x19 through GfBdatChrDr and getIraBack); DataObjDriver's stat getters sum the
    // BTL_Enhance rows of a given EnhanceEffect from it.
    static void getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriver& data);
    // 2.0.0's symbols name it. What it does: pushes onto enhances the equipment enhance
    // (GfBdatItem::getPcEquipEnhance1) of the DLC driver record's item at +0x5A4, when it has one, and returns whether
    // enhances holds any; DataObjDriver's stat getters use it for m_dlc.
    static bool getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataIra& data);
    // the stat corrections (percent) DataObjDriver's stat getters apply
    // 2.0.0's symbols name it. What it does: the HP correction percent DataObjDriver::getHpMax applies (like
    // getStrengthRev for the strength).
    static unsigned int getHpMaxRev(const SDataDriver& data);
    static unsigned int getStrengthRev(const SDataDriver& data);
    static unsigned int getPowEtherRev(const SDataDriver& data);
    static unsigned int getDexRev(const SDataDriver& data);
    static unsigned int getAgilityRev(const SDataDriver& data);
    static unsigned int getLuckRev(const SDataDriver& data);
    static unsigned int getAiID(unsigned int driver);
    static unsigned int getExtraMountNpcRsc(unsigned int driver);
    static const char* getExtraMountBone(unsigned int driver);
    static bool isDriver(unsigned int driver);
    static bool isDummyDriver(unsigned int driver);
    static unsigned int getDebugAppendDeathBlowEfbFileIdx(unsigned int index);
    static unsigned int getDebugAppendDeathBlowEabFileIdx(unsigned int index);
    static unsigned int getWeaponEfbFileIdx(int index);
    static unsigned int getWeaponEabFileIdx(int index);
    static unsigned int getWeaponSwtFileIdx(int index);
    static unsigned int getWeaponAnmFileIdx(int index);
    // the driver's added animation for the weapon type; false without one (1.0.0's symbols name it)
    static bool getDriverAddAnim(mm::mtl::FixStr<128>& name, unsigned int driver, unsigned int weaponType);
    // (appended by chardata) 1.0.0's names: its GfMenuCharDataAdapter::update_DR_LevelUpEnable / update_DR_IdeaPoint
    // call them at the same sites (the symbols call them fn_7100245C44 / fn_71002422C4)
    static bool isEnableLevelUp(unsigned int driver);
    // the weapon type of the driver's data (found the getSDataDriver way); named by the symbols
    static unsigned short getDefaultWpnType(unsigned int driver);
    static unsigned short getDefaultWpnType(const SDataDriver& data);  // named by the symbols (not written yet)
    static SDataIdea* getSDataIdea(unsigned int driver);
    static unsigned int getExpUsed(unsigned int driver);  // (appended by chardata)
    // takes the blade off the driver it is set to (GfGameUtil::execActivateReserverForBlade)
    static void unsetBlade(unsigned int blade);
    // 2.0.0's symbols name it. What it does: a blade id for drivers 1, 7, 9 and 12 (0x3F4, 0x3F5, 0x431, 0x456), else
    // 0.
    static unsigned int getDummyBlade(unsigned int driver);
    // 1.0.0's setScenarioMask (0x71002A9D44, called by 1.0.0's pt setDriverAway with its two script arguments):
    // the flag byte at 0x59C of the driver's SDataDriver (3.0.1 adds drivers 0x11-0x19)
    static void setScenarioMask(unsigned int driver, bool mask);
    // 2.0.0's symbols name it. What it does: ScriptPlayText's pt setDriverEnable passes (2, -1, false) when driver 2 is
    // activate-unuse. The types of the last two are inferred from the constants.
    static void setActivateReserver(unsigned int driver, unsigned int blade, PTPOS flag);
    // 2.0.0's symbols name it. What it does: false for driver 0, else whether the byte at 0x572 of that SDataDriver
    // (m_defaultAcceDone) is set; GfGameUtil::execEquipDriverDefaultAcce skips a driver for which it holds.
    static bool isEquipDefaultAcce(unsigned int driver);
    static const char* getBelongingMountBone();   // "MT_wire"
    static const char* getBelongingMountBoneA();  // "EX_wireA"
    static const char* getBelongingMountBoneB();  // "EX_wireB"
    static unsigned int getDeathBlowEfbFileIdx(DBSLOT slot, int index);
    static unsigned int getDeathBlowEabFileIdx(DBSLOT slot, int index);
    static void openDriverArtsForLevelup(unsigned int driver);  // fn_7100244A44(driver, 0, true)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its callers are
    // GfDataDriver::openDriverArtsForLevelup and GfDataBlade::addRareBlade, in this unit, and it takes a driver.
    // What it does: opens the driver's arts (all of them when arts is 0, else the one whose id matches) and, per
    // opened art, calls GfEvent::callGetArts(driver, art, event).
    static void fn_7100244A44(unsigned int driver, unsigned int arts, bool event);
    // 2.0.0's symbols name them. What they do: test / set flag `index` of the driver's 56 flags, 0..0x1B in its
    // SDataDriver's m_flags, 0x1C.. in its SDataDriverArtsEx's (fn_7100244A44 tests them, addRareBlade and
    // addCommonBlade set them); false for driver 0.
    static bool isActivateWeaponType(unsigned int driver, unsigned int index);
    static void setActivateWeaponType(unsigned int driver, unsigned int index);
    // GfBdatChrDr::getChrDrDefBlade(driver, slot) (title event, three unnamed callers)
    static unsigned int getDefaultBlade(unsigned int driver, unsigned int slot);
    // GfBdatChrDr::isChrIrFlagWpnInNonView of the driver's GfBdatChrDr::getChrDrIraParam row, false for none
    static bool isIraHideWeaponOnField(unsigned int driver);
    // GfBdatChrDr::getChrIrGroupID of the driver's GfBdatChrDr::getChrDrIraParam row, 0 for none
    // 2.0.0's symbols name it. What it does: the DLC driver record's m_partyIndex for drivers 0x11-0x19, else 0.
    static unsigned int getPartyPos(unsigned int driver);
    // 2.0.0's symbols name it. What it does: of getIraFront(driver) and getIraBack's list for it, the first id whose
    // getPartyPos value (the DLC record's 16-bit field at 0xDA8, 0 outside 0x11-0x19) equals the second argument, 0 for
    // none. Callers: gf_menu_obj_char_select_ira's GfMenuObjCharSelectIra::changeBlade (with 0),
    // GfReqCommand::reqChangeParty.
    static unsigned int getIraFromPos(unsigned int driver, PTPOS);
    static unsigned int getIraGroup(unsigned int driver);
    // the blade in a slot (slot < 0: the engaged one, m_bladeSet), 0 for none; DLC drivers (0x11-0x19) answer
    // GfBdatChrDr::getChrDrDefBlade1 instead (DataObjDriver::getBlade)
    static unsigned int getBlade(const SDataDriver& data, int slot);
    // "oj/oj300002" for create types 9 and 13, else "oj/oj300001", when the param's object id is 1; else none
    static const char* getBelongingModelName(const GfInitParamDriver& param);
    static bool isExistBlade(unsigned int driver);  // getListBlade finds any
    static bool getListBlade(mm::mtl::FixedVector<unsigned short, 422>& list, unsigned int driver);
    static unsigned int getDriverBySetBlade(unsigned int blade);  // the blade's m_setDriver
    // 2.0.0's symbols name it. What it does: whether the driver can level up: compares getExp(data) with the growth
    // table (GfBdatBtl::getGrowEnd, GfBdatChrDr::getChrDrIraParam/getChrIrType).
    static bool isEnableLevelUp(const SDataDriver& data);
    // 2.0.0's symbols name it. What it does: false for driver 0, else whether m_dataType (+0x20) of its data (found the
    // getSDataDriver way) is 1.
    static bool isActivatePartyAll(unsigned int driver);
    // 2.0.0's symbols name it. What it does: getSkillPoint of the driver's data (found the getSDataDriver way);
    // GfGameUtil::execDriverSkillLevelUp/checkDriverSkillLevelUp call it.
    static unsigned int getSkillPoint(unsigned int driver);
    // 2.0.0's symbols name it. What it does: the item handle (+0x5A0) of the DLC driver (0x11-0x19) row of
    // GfDataManager::getDataGameIra's 0xDAC-byte table, else an empty handle (GfItemUtil::getEquipChar calls it).
    static GfItemHandle getEquipWpnAcceHandle(unsigned int driver);
    // the item handle of the accessory in the driver's slot (0-1, 2 the DLC drivers' extra slot); the name is 1.0.0's
    // (its getEquipAcceHandle has the same callers) and 2.0.0's
    static GfItemHandle getEquipAcceHandle(unsigned int driver, unsigned int slot);
    // 2.0.0's symbols name it. What it does: sets the 16-bit item id (+0x5A4) of the DLC driver (0x11-0x19) row of
    // GfDataManager::getDataGameIra's 0xDAC-byte table (getEquipWpnAcce reads it).
    static void setEquipWpnAcce(unsigned int driver, unsigned int item);
    // 1.0.0's name: GfPouchUtil calls it in both builds (1.0.0: GfDataDriver::setPouchData(unsigned int, unsigned
    // int, const SDataPouch&)); copies the slot into the driver's pouch
    static void setPouchData(unsigned int driver, unsigned int pouch, const SDataPouch& data);
    // 2.0.0's symbols name it. What it does: false for driver 0, else whether the byte at +0x571 of the driver's data
    // (found the getSDataDriver way) is nonzero. Callers: GfGameUtil::execLevelUp, GfGameUtil::addWpForObject,
    // GfAssetSetup::setRefResource.
    static bool isAttachedParty(unsigned int driver);
    // 2.0.0's symbols name it. What it does: sets bit 1 (flag true) or bit 0 of the byte at +0x573 of the driver's
    // data; its one caller is GfMenuObjDrKizunaRing::seqComplete.
    static void setKizunaringComplete(unsigned int driver, bool flag);
    // 2.0.0's symbols name it. What it does: whether bit 1 (flag true) or bit 0 of the byte setKizunaringComplete sets
    // is set; its one caller is GfMenuObjDrKizunaRing::seqComplete.
    static bool isKizunaringComplete(unsigned int driver, bool flag);
    // 2.0.0's symbols name it. What it does: nothing for driver 0, else setEquipAcce on the driver's data; its one
    // caller is GfEquipUtil::equipDriverAcce.
    static void setEquipAcce(unsigned int driver, unsigned int slot, unsigned int accessory);
    // 2.0.0's symbols name it. What it does: nothing for driver 0, else stores the handle as the item handle of the
    // driver's accessory slot (slots 0-1 at +0x574, others at +0x2EC); its one caller is GfEquipUtil::equipDriverAcce.
    static void setEquipAcceHandle(unsigned int driver, unsigned int slot, GfItemHandle handle);
    // 2.0.0's symbols name it. What it does: addSkillPoint on the driver's data; callers
    // GfGameUtil::execDriverSkillLevelUp and addSp.
    static void addSkillPoint(unsigned int driver, int point);
    // 3.0.1's symbol name (GfDataBlade's unit): recomputes the driver's base stats from its level
    static void calcDriverBaseParamByLevel(SDataDriver& data);
    // 2.0.0's symbols name it. What it does: for a DLC driver (0x11-0x19) whose GfBdatChrDr::getChrIrType row is set,
    // does the same to getIraFront's driver; else stores level at +0x94 and calls calcDriverBaseParamByLevel. Callers:
    // DataObjDriver::setVirtualLevel, setLevel.
    static void setLevel(SDataDriver& data, unsigned int level);
    // 2.0.0's symbols name it. What it does: setLevel on the driver's data (found the getSDataDriver way); callers
    // include GfGameUtil's fn_71002DAD5C and GfArenaParty::setupLevelForBattleEnd.
    static void setLevel(unsigned int driver, unsigned int level);
    // 2.0.0's symbols name it. What it does: stores exp at +0xB0 of the driver's data, for a DLC driver whose
    // GfBdatChrDr::getChrIrType row is set the data of getIraFront's driver (getExp reads it the same way); callers
    // GfGameUtil::execLevelUp, execLevelDown.
    static void setExp(unsigned int driver, unsigned int exp);
    // 2.0.0's symbols name it. What it does: as setExp for the battle experience at +0xB4 (getBattleExp's field).
    static void setBattleExp(unsigned int driver, unsigned int exp);
    // 2.0.0's symbols name it. What it does: see GfDataDriver::getEnableLevel.
    static bool getEnableLevel(unsigned int& level, unsigned int& value, const SDataDriver& data);
    // 2.0.0's symbols name it. What it does: getValidEnhance on the driver's data (found the getSDataDriver way); its
    // one caller is btl::PlayerParameter::InitializeEnhance.
    static void getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int driver);
    // 2.0.0's symbols name it. What it does: stores item into the DLC driver record's 16-bit item id (+0x5A4);
    // DataObjDriver::setVirtualEquipWpnAcce (a DataObjDriver function) passes its record when the item is of type 2.
    static void setEquipWpnAcce(SDataIra& data, unsigned int item);
    // 2.0.0's symbols name it. What it does: copies handle into the item handle (+0x5A0) of the DLC driver (0x11-0x19)
    // row of GfDataManager::getDataGameIra's 0xDAC-byte table (getEquipWpnAcceHandle reads it back).
    static void setEquipWpnAcceHandle(unsigned int driver, GfItemHandle handle);
    // 2.0.0's symbols name it. What it does: getExp of the driver's row (getSDataDriver).
    static unsigned int getExp(unsigned int driver);
    // 2.0.0's symbols name it. What it does: getBattleExp of the driver's row (getSDataDriver).
    static unsigned int getBattleExp(unsigned int driver);
    // 2.0.0's symbols name it. What it does: getBattleExpNextLevel of the driver's row (getSDataDriver).
    static unsigned int getBattleExpNextLevel(unsigned int driver);
    // 2.0.0's symbols name it. What it does: the work GfDataDriver::getEquipAcceEnahnce's comment describes, on one driver's data.
    static bool getEquipAcceEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriver& data);
    // 2.0.0's symbols name it. What it does: for drivers 17-25 only (else 0), GfBdatChrDr::getChrDrDefBlade(driver, 0)
    // of the driver itself (slot other than 0/1), or of the first (slot 0) / second (slot 1) id getIraBack lists for
    // it, 0 when the list is too short. GfGameUtil::addTrustPointIra passes (driver, -1) and adds the trust to the
    // result.
    static unsigned int getIraBlade(unsigned int driver, int slot);
    // 2.0.0's symbols name it. What it does: the slot DataObjDriver::setVirtualSetBlade engages a blade in: for driver
    // 1, 4 for blade 1003 and 3 for blade 1002 while blade 1001 has no driver set (getDriverSetID); else the slot it is
    // given.
    static int getRuleSetBlade(unsigned int driver, unsigned int blade, int slot);
    // 2.0.0's symbols name it. What it does: the index getSDataDriver uses: driver - 0x11 for a DLC row (0x11-0x19),
    // else driver - 1 clamped to 1 past 0x10 (caller fn_71002EAF78).
    static unsigned int getDriverRelativeID(unsigned int driver);
};
}  // namespace gf

#endif
