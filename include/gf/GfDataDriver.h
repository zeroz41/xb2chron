#ifndef GF_GFDATADRIVER_H
#define GF_GFDATADRIVER_H

namespace gf { class SDataDriver; enum DBSLOT : int; struct GfItemHandle; }
namespace gf { struct SDataPouch; }
namespace gf { struct SDataDriverDlc; struct SDataDriverArtsEx; }
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
    // 1.0.0's names (the symbols still spell 3.0.1's copies fn_<address>: same call sites, same arguments; 3.0.1's
    // also cover the DLC drivers)
    static SDataDriver* getSDataDriver(unsigned int driver);  // fn_7100231C64
    // the driver's arts records past the ones its data keeps, found the getSDataDriver way (DLC rows 0x11-0x19 in
    // GfDataManager::fn_7100224A10's, others in getDataGame's 16, clamped as getSDataDriver clamps); inline in
    // fn_7100247804, fn_7100245478, fn_710024553C and GfDataDriverArts::getArtsLevel. The name is not the original's.
    static SDataDriverArtsEx* getSDataDriverArtsEx(unsigned int driver);
    static unsigned int getLevel(const SDataDriver& data);  // fn_710024572C
    // 1.0.0's name: its getLevel(unsigned int) has the same callers (GfMenuObjDrArtsSet2::ArtsListListener,
    // GfMenuObjLvupSelect's listeners) and reads getLevel(*getSDataDriver(driver)); the symbols spell fn_7100234674
    static unsigned int getLevel(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataDriver's functions and every caller passes it a driver row (getLevel, getExp, DataObjDriver). What it
    // does: for a DLC driver row (0x11-0x19) whose CHR_Ir "Type" is set, finds the first CHR_Ir row of the same
    // "GroupID" whose Type is 0 and returns its "driverID" (0x11 when there is none); any other row comes back as is.
    static unsigned int fn_71002417DC(unsigned int driver);
    // the experience a driver needs to reach level (GfMenuCharDataAdapter::update_DR_ExpNextVirtual)
    static unsigned int getExpSetLevel(unsigned int driver, unsigned int level);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among GfDataDriver's placeholder functions (fn_71002416B4, fn_71002417DC; no this). What it does: 0 unless
    // driver is a DLC driver row (0x11-0x19); then it walks fn_71002417DC(driver) and its fn_71002416B4 list and
    // returns a driver id; GfMenuCharDataAdapter::fn_710033973C shows that driver's face icon.
    static unsigned int fn_7100241A1C(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit among GfDataDriver's functions (after fn_7100241A1C) and takes a driver id. What it does: answers
    // fn_7100241E10(driver, list) for a local list (a 0x350-byte buffer and its size, cleared afterwards);
    // GfGameUtil::fn_71002E16F4 does nothing for a driver it holds for.
    static bool fn_7100241DD4(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit right after fn_7100241DD4, which passes it a driver id and a FixedVector<unsigned short, 424> (0x350-byte
    // room). What it does: fills the list with GfDataBlade::getListReserver's blades, drops those already listed and
    // the ones GameFlag / GfDataDriver::isEnableEquipBlade reject, and answers whether one is left (0x440 bytes).
    static bool fn_7100241E10(unsigned int driver, mm::mtl::FixedVector<unsigned short, 424>& list);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit among GfDataDriver's functions (after fn_7100241E10) and takes a driver id. What it does: the index
    // getSDataDriver uses: driver - 0x11 for a DLC row (0x11-0x19), else driver - 1 clamped to 1 past 0x10
    // (caller fn_71002EAF78).
    static unsigned int fn_710024229C(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it takes a driver row and
    // reads its data the getSDataDriver way (inlined), next to GfDataBlade::fn_710023B798's driver functions. What it
    // does: the first of the driver's three blade slots (SDataDriver::m_blades) holding a GfDataBlade::isDummyBlade
    // blade, -1 for none. Caller: gf::fn_71002EC268.
    static int fn_710023B6A8(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among GfDataDriver's
    // functions (right before fn_71002417DC) and takes a driver row. What it does: for a DLC driver row (0x11-0x19)
    // collects every GfBdatChrDr row of type 1 whose group (fn_71001F172C) equals the driver's into the list
    // (fn_71001F161C's 16-bit ids) and answers whether the list is non-empty; any other row: false. Callers include
    // GfDataBlade::fn_7100237B70, getListPartyAll and GfMenuCharDataAdapter's TUnk_B5B908::getCharData.
    static bool fn_71002416B4(mm::mtl::FixedVector<unsigned short, 32>& list, unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit among GfDataDriver's functions and takes a driver id. What it does: finds the driver's row (DLC rows
    // 0x11-0x19 through GfDataManager::fn_7100224A10, others in getDataGame) and tail-calls fn_7100245800 with the
    // two outputs and the row, which stores the reachable level (from the row's level at 0x94 and GfBdatBtl's growth
    // table) and a second value and returns true when it found one. GfMenuObjLvupSelect::SelectListener takes the
    // first output as the level select's maximum.
    static bool fn_7100245794(unsigned int* level, unsigned int* value, unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfDataBlade::isActivateDriver before
    // isActivateParty is other code). A member because it lies among GfDataDriver's functions (right before
    // isActivateParty) and its callers pass it a driver id. What it does: true for a driver outside the DLC rows
    // 0x11-0x19; for those, whether GfBdatChrDr::fn_71001F16A4 of the row GfBdatChrDr::fn_71001F13E0 gives is 0.
    // Caller here: gf_menu_obj_char_select_ira's fn_71003D273C (driver 0 and 1 references both set to it when true).
    static bool fn_7100237A94(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in GfDataBlade's
    // unit and lists driver ids (its callers, SCOM_ADD_TRUST::exec and GfMenuObjMainMenu2::openChrChangeSub, treat
    // them as drivers). What it does: pushes every GfBdatChrDr row id from fn_71001F15D4 up to (not including)
    // fn_71001F15E0 (fn_71001F161C) into drivers; true when drivers is not empty.
    static bool fn_7100241570(mm::mtl::FixedVector<unsigned short, 32>& drivers);
    // whether the driver (data type 1) is in a party slot below 3 (GfDataParty::getDriverPartyID)
    static bool isActivateParty(unsigned int driver);
    static unsigned int getExp(const SDataDriver& data);  // fn_7100245AB4
    static unsigned int getBattleExp(const SDataDriver& data);  // fn_7100245B7C
    static unsigned int getExpNextLevel(const SDataDriver& data);  // fn_710024618C
    static unsigned int getBattleExpNextLevel(const SDataDriver& data);  // fn_7100245FA4
    static void addSkillPoint(SDataDriver& data, int point);  // fn_7100247F2C
    static bool isScenarioMask(unsigned int driver);  // fn_71002465D0
    static unsigned int getEquipAcce(const SDataDriver& data, unsigned int slot);  // fn_7100247778
    static void setEquipAcce(SDataDriver& data, unsigned int slot, unsigned int accessory);  // fn_7100247A94
    // 1.0.0's name: GfEquipUtil::getEquipDriverAcce(driver, slot) tail-calls it in both builds (1.0.0:
    // GfDataDriver::getEquipAcce(unsigned int, unsigned int)); the symbols spell 3.0.1's copy fn_7100247794
    static unsigned int getEquipAcce(unsigned int driver, unsigned int slot);
    // Placeholder names: new in 3.0.1 (1.0.0's DataObjDriver::getDriverArtsLevel/setDriverArtsLevel/getDriverArts read
    // the driver's SDataDriver inline), nothing in 1.0.0's place names them. Static members because they sit in
    // GfDataBlade's unit among GfDataDriver's functions and take a driver id (no this). What they do:
    // fn_7100245478 returns the level byte of arts `arts` of the driver (same code as GfDataDriverArts::getArtsLevel:
    // DLC rows 0x11-0x19 through GfDataManager::fn_7100224A10, others in getDataGame's 0x5A0-byte records);
    // fn_710024553C stores it (DataObjDriver::setDriverArtsLevel clamps the level to 5 first).
    static unsigned int fn_7100245478(unsigned int driver, unsigned int arts);
    static void fn_710024553C(unsigned int driver, unsigned int arts, unsigned int level);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0's DataObjDriver::getDriverArts reads
    // the SDataDriver inline). Static members for the same reason (after getEquipAcce fn_7100247794, a driver id).
    // What they do: the 20-byte arts slot record `index` of the driver's row (fn_7100247804: +0xC0 of the row,
    // fn_71002478C8 / fn_7100247928: two DLC-table variants); DataObjDriver::getDriverArts indexes the words of it,
    // its third argument (0, 1, 2) picking which.
    static unsigned int* fn_7100247804(unsigned int driver, unsigned int index);
    static unsigned int* fn_71002478C8(unsigned int driver, unsigned int index);
    static unsigned int* fn_7100247928(unsigned int driver, unsigned int index);
    // 1.0.0's name: GfPouchUtil::getPouch calls it in both builds (1.0.0: GfDataDriver::getPouchData(unsigned int,
    // unsigned int)); the symbols spell 3.0.1's copy fn_71002409CC
    static SDataPouch* getPouchData(unsigned int driver, unsigned int pouch);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit among GfDataDriver's accessory functions (getEquipAcce fn_7100247794, setEquipAcce fn_7100247A94) and
    // takes a driver row. What it does: resolves the driver's row (a DLC row 0x11-0x19 from
    // GfDataManager::fn_7100224A10's 0xDAC-byte table, else getDataGame's 0x5A0-byte records), then the row its
    // u16 at +0x22 names, and returns bit 31 of that row's word at +0x2E8 (the word whose low 16 bits hold an
    // accessory). Its one caller is GfEquipUtil::fn_71002FC38C.
    static bool fn_7100247BF0(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason as
    // fn_7100247BF0. What it does: resolves the same row and sets (flag true) or clears bit 31 of its word at
    // +0x2E8. Its one caller is GfEquipUtil::fn_71002FC390.
    static void fn_7100247B40(unsigned int driver, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfDataBlade's
    // unit among GfDataDriver's functions and takes a driver row. What it does: for a DLC driver (0x11-0x19) the
    // 16-bit item id at +0x5A4 of its row of GfDataManager::fn_7100224A10's driver table, else 0.
    static unsigned int fn_7100247474(unsigned int driver);
    // false for a negative slot, or (engaging) when the slot's blade is not set to this driver: the slot is cleared
    static bool setEquipBlade(unsigned int driver, bool engage, int slot);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataDriver's functions and DataObjDriver passes it a driver's row. What it does: true for rows 0x11 to 0x19
    // (the DLC drivers, whose data GfDataDriver::getSDataDriver reads from a separate table of 0xDAC-byte records).
    static bool fn_710023F9A8(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataDriver's functions and DataObjDriver passes it a driver's row. What it does: the DLC driver's record in
    // that table (rows 0x11 to 0x19, others clamped); DataObjDriver keeps it when fn_710023F9A8 accepts the row.
    static SDataDriverDlc* fn_7100241BB4(unsigned int driver);

    static const char* getName(unsigned int driver);
    // the message table and row of the driver's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int driver);
    static const char* getModelResourceName(unsigned int driver);
    static const char* getMotionResourceName(unsigned int driver);
    static const char* getDebugName(unsigned int driver);  // DataObjDriver::getEffectResourceName returns it
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
    // whether the favorite has been used (seen). The symbols spell it fn_7100248A84: 1.0.0's
    // GfMenuObjUtil::getFavoriteStat calls GfDataDriver::isUsedFavorite(driver, favorite) where 3.0.1's calls
    // fn_7100248A84 with the same arguments (3.0.1's body also handles drivers 17-25)
    static bool isUsedFavorite(unsigned int driver, FAVORITE favorite);

    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrOffsetID itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrOffsetID for the row (DataObjDriver::getMenuOffset returns it).
    static int fn_7100241CAC(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrCenterBone itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrCenterBone for the row (DataObjDriver::getCenterBone returns it).
    static const char* fn_7100241CC4(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrCamBone itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrCamBone for the row (DataObjDriver::getCamBone returns it).
    static const char* fn_7100241CDC(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrChestHeight itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrChestHeight for the row (DataObjDriver::getChestHeight returns it).
    static unsigned int fn_7100241C04(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrLandingHeight itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrLandingHeight for the row (DataObjDriver::getLandingHeight returns it).
    static unsigned int fn_7100241C1C(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrStill itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrStill for the row (DataObjDriver::getIconData returns it).
    static unsigned int fn_7100241C34(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's DataObjDriver called GfBdatChrDr::getChrDrGender itself), nothing names it. A
    // member because its address lies among GfDataDriver's functions and it takes a driver's row like them. What it
    // does: GfBdatChrDr::getChrDrGender for the row (DataObjDriver::getGender returns it).
    static unsigned int fn_7100241C94(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because its address follows
    // GfDataDriver::getWeaponEfbFileIdx in the GfDataBlade unit and it takes a driver id, no object. What it does:
    // pushes onto enhances the equipment enhance ids (GfBdatItem::getPcEquipEnhance1) of the driver's equipped
    // items (the game data's driver rows, 0x5A0 apart; drivers 0x11-0x19 from another table, 0xDAC apart);
    // GfFobjManager::fn_7100289504 passes its party leader's driver id and sums the "EnhanceEffect" 0xFB rows.
    static bool fn_7100247580(mm::mtl::FixedVector<unsigned short, 64>& enhances, int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because its address sits
    // among GfDataDriver's functions in the GfDataBlade unit (after getEquipWpnType) and it takes a driver's data, no
    // object. What it does: fills enhances with the enhance ids that apply to the driver (its row at data+0x22, the
    // DLC drivers 0x11-0x19 through GfBdatChrDr and fn_71002416B4); DataObjDriver's stat getters sum the
    // BTL_Enhance rows of a given EnhanceEffect from it.
    static void fn_7100247FD0(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriver& data);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member for the same placement as
    // fn_7100247FD0. What it does: pushes onto enhances the equipment enhance (GfBdatItem::getPcEquipEnhance1) of the
    // DLC driver record's item at +0x5A4, when it has one, and returns whether enhances holds any; DataObjDriver's stat
    // getters use it for m_dlc.
    static bool fn_7100248668(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriverDlc& data);
    // the stat corrections (percent) DataObjDriver's stat getters apply
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (checked below). A static member because it
    // sits before getStrengthRev among GfDataDriver's functions and takes a driver's data. What it does: the HP
    // correction percent DataObjDriver::getHpMax applies (like getStrengthRev for the strength).
    static unsigned int fn_7100246694(const SDataDriver& data);
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
    static SDataIdea* getSDataIdea(unsigned int driver);
    static unsigned int getExpUsed(unsigned int driver);  // (appended by chardata)
    // takes the blade off the driver it is set to (GfGameUtil::execActivateReserverForBlade)
    static void unsetBlade(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in GfDataBlade's unit
    // after GfDataDriver::unsetBlade and its result goes to unsetBlade (fn_71002EC268 calls both in a row). What it
    // does: a blade id for drivers 1, 7, 9 and 12 (0x3F4, 0x3F5, 0x431, 0x456), else 0.
    static unsigned int fn_710023A9C8(unsigned int driver);
    // 1.0.0's setScenarioMask (0x71002A9D44, called by 1.0.0's pt setDriverAway with its two script arguments):
    // the flag byte at 0x59C of the driver's SDataDriver (3.0.1 adds drivers 0x11-0x19)
    static void setScenarioMask(unsigned int driver, bool mask);
    // Placeholder name: 1.0.0's pt setDriverEnable calls GfDataDriver::setActivateReserver(driver, x) here, 3.0.1
    // passes three arguments, so the name is not proven. A GfDataDriver member because its address lies among
    // GfDataDriver's functions. What it does: ScriptPlayText's pt setDriverEnable passes (2, -1, false) when
    // driver 2 is activate-unuse. The types of the last two are inferred from the constants.
    static void fn_7100243934(unsigned int driver, int blade, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataDriver's functions and it reads a driver's data the way getSDataDriver finds it (DLC rows 0x11-0x19 from
    // GfDataManager::fn_7100224A10, else the game data's rows). What it does: false for driver 0, else whether the
    // byte at 0x572 of that SDataDriver (m_defaultAcceDone) is set; GfGameUtil::execEquipDriverDefaultAcce skips a
    // driver for which it holds.
    static bool fn_71002491D4(unsigned int driver);
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
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they sit among
    // GfDataDriver's functions (between setUsedFavoriteItemForPouch and isDriver) and take a driver. What they do:
    // test / set flag `index` of the driver's 56 flags, 0..0x1B in its SDataDriver's m_flags, 0x1C.. in its
    // SDataDriverArtsEx's (fn_7100244A44 tests them, addRareBlade and addCommonBlade set them); false for driver 0.
    static bool fn_7100248DB0(unsigned int driver, unsigned int index);
    static void fn_7100248EB0(unsigned int driver, unsigned int index);
    // GfBdatChrDr::getChrDrDefBlade(driver, slot) (title event, three unnamed callers)
    static unsigned int fn_7100241640(unsigned int driver, unsigned int slot);
    // GfBdatChrDr::fn_71001F183C of the driver's GfBdatChrDr::fn_71001F13E0 row, false for none
    static bool fn_7100241660(unsigned int driver);
    // GfBdatChrDr::fn_71001F172C of the driver's GfBdatChrDr::fn_71001F13E0 row, 0 for none
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among GfDataDriver's
    // functions (between fn_71002417DC and fn_71002419C8) and takes a driver id. What it does: the DLC driver record's
    // m_partyIndex for drivers 0x11-0x19, else 0.
    static unsigned int fn_710024198C(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among GfDataDriver's
    // functions (right after fn_71002417DC) and takes a driver id. What it does: of fn_71002417DC(driver) and
    // fn_71002416B4's list for it, the first id whose fn_710024198C value (the DLC record's 16-bit field at 0xDA8,
    // 0 outside 0x11-0x19) equals the second argument, 0 for none. Callers: gf_menu_obj_char_select_ira's
    // TUnk_B61178::fn_71003D3F94 (with 0), GfReqCommand::reqChangeParty.
    static unsigned int fn_71002418CC(unsigned int driver, unsigned int);
    static unsigned int fn_71002419C8(unsigned int driver);
    // the blade in a slot (slot < 0: the engaged one, m_bladeSet), 0 for none; DLC drivers (0x11-0x19) answer
    // GfBdatChrDr::getChrDrDefBlade1 instead (DataObjDriver::getBlade)
    static unsigned int fn_7100244E78(const SDataDriver& data, int slot);
    // "oj/oj300002" for create types 9 and 13, else "oj/oj300001", when the param's object id is 1; else none
    static const char* getBelongingModelName(const GfInitParamDriver& param);
    static bool isExistBlade(unsigned int driver);  // getListBlade finds any
    static bool getListBlade(mm::mtl::FixedVector<unsigned short, 422>& list, unsigned int driver);
    static unsigned int getDriverBySetBlade(unsigned int blade);  // the blade's m_setDriver
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its only caller is
    // GfDataDriver::isEnableLevelUp, which hands it getSDataDriver's data. What it does: whether the driver can level
    // up: compares getExp(data) with the growth table (GfBdatBtl::getGrowEnd, GfBdatChrDr::fn_71001F13E0/fn_71001F16A4).
    static bool fn_7100245C98(const SDataDriver& data);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions. What it does: false for driver 0, else whether m_dataType (+0x20) of its data (found the getSDataDriver way) is 1.
    static bool fn_7100238094(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions. What it does: getSkillPoint of the driver's data (found the getSDataDriver way); GfGameUtil::execDriverSkillLevelUp/checkDriverSkillLevelUp call it.
    static unsigned int fn_7100247E28(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions. What it does: the item handle (+0x5A0) of the DLC driver (0x11-0x19) row of GfDataManager::fn_7100224A10's 0xDAC-byte table, else an empty handle (GfItemUtil::getEquipChar calls it).
    static GfItemHandle fn_71002474B0(unsigned int driver);
    // the item handle of the accessory in the driver's slot (0-1, 2 the DLC drivers' extra slot); the name is 1.0.0's
    // (its getEquipAcceHandle has the same callers), the symbols still spell it fn_7100247988
    static GfItemHandle getEquipAcceHandle(unsigned int driver, unsigned int slot);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions. What it does: sets the 16-bit item id (+0x5A4) of the DLC driver (0x11-0x19) row of GfDataManager::fn_7100224A10's 0xDAC-byte table (fn_7100247474 reads it).
    static void fn_71002474F4(unsigned int driver, unsigned short item);
    // 1.0.0's name: GfPouchUtil calls it in both builds (1.0.0: GfDataDriver::setPouchData(unsigned int, unsigned
    // int, const SDataPouch&)); copies the slot into the driver's pouch
    static void setPouchData(unsigned int driver, unsigned int pouch, const SDataPouch& data);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions and it takes a driver row. What it does: false for driver 0,
    // else whether the byte at +0x571 of the driver's data (found the getSDataDriver way) is nonzero. Callers:
    // GfGameUtil::execLevelUp, GfGameUtil::addWpForObject, GfAssetSetup::setRefResource.
    static bool fn_7100249170(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // sets bit 1 (flag true) or bit 0 of the byte at +0x573 of the driver's data; its one caller is
    // GfMenuObjDrKizunaRing::seqComplete.
    static void fn_7100241CF4(unsigned int driver, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // whether bit 1 (flag true) or bit 0 of the byte fn_7100241CF4 sets is set; its one caller is
    // GfMenuObjDrKizunaRing::seqComplete.
    static bool fn_7100241D64(unsigned int driver, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // nothing for driver 0, else setEquipAcce on the driver's data; its one caller is GfEquipUtil::equipDriverAcce.
    static void fn_7100247A08(unsigned int driver, unsigned int slot, unsigned int accessory);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // nothing for driver 0, else stores the handle as the item handle of the driver's accessory slot (slots 0-1 at
    // +0x574, others at +0x2EC); its one caller is GfEquipUtil::equipDriverAcce.
    static void fn_7100247ABC(unsigned int driver, unsigned int slot, const GfItemHandle& handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // addSkillPoint on the driver's data; callers GfGameUtil::execDriverSkillLevelUp and fn_71002DB9D4.
    static void fn_7100247E88(unsigned int driver, int point);
    // 3.0.1's symbol name (GfDataBlade's unit): recomputes the driver's base stats from its level
    static void calcDriverBaseParamByLevel(SDataDriver& data);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions and it takes a driver's data. What it does: for a DLC driver
    // (0x11-0x19) whose GfBdatChrDr::fn_71001F16A4 row is set, does the same to fn_71002417DC's driver; else stores
    // level at +0x94 and calls calcDriverBaseParamByLevel. Callers: DataObjDriver::setVirtualLevel, fn_710024487C.
    static void fn_71002447AC(SDataDriver& data, unsigned int level);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // fn_71002447AC on the driver's data (found the getSDataDriver way); callers include GfGameUtil's
    // fn_71002DAD5C and TUnk_28D7B8::fn_710028E15C.
    static void fn_710024487C(unsigned int driver, unsigned int level);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // stores exp at +0xB0 of the driver's data, for a DLC driver whose GfBdatChrDr::fn_71001F16A4 row is set the data
    // of fn_71002417DC's driver (getExp reads it the same way); callers GfGameUtil::execLevelUp, fn_71002DB338.
    static void fn_71002448D8(unsigned int driver, unsigned int exp);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // as fn_71002448D8 for the battle experience at +0xB4 (getBattleExp's field).
    static void fn_7100244988(unsigned int driver, unsigned int exp);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_7100245794 tail-calls
    // it with its outputs and the driver's data. What it does: see fn_7100245794.
    static bool fn_7100245800(unsigned int* level, unsigned int* value, const SDataDriver& data);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions. What it does: fn_7100247FD0 on the driver's data (found the
    // getSDataDriver way); its one caller is btl::PlayerParameter::InitializeEnhance.
    static void fn_7100247F74(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions (next to fn_71002474F4/fn_7100247534, which set the same row's fields
    // through the driver id). What it does: stores item into the DLC driver record's 16-bit item id (+0x5A4);
    // fn_71002251B8 (a DataObjDriver function) passes its record when the item is of type 2.
    static void fn_710024752C(SDataDriverDlc& data, unsigned short item);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions. What it does: copies handle into the item handle (+0x5A0) of the
    // DLC driver (0x11-0x19) row of GfDataManager::fn_7100224A10's 0xDAC-byte table (fn_71002474B0 reads it back).
    static void fn_7100247534(unsigned int driver, GfItemHandle handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions (after isEnableLevelUp, which has the same shape). What it does: getExp of the driver's row
    // (getSDataDriver).
    static unsigned int fn_7100245EA8(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions (after isEnableLevelUp, which has the same shape). What it does: getBattleExp of the driver's row
    // (getSDataDriver).
    static unsigned int fn_7100245EFC(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataDriver's functions (after isEnableLevelUp, which has the same shape). What it does: getBattleExpNextLevel of the driver's row
    // (getSDataDriver).
    static unsigned int fn_7100245F50(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_7100247580 hands it its
    // enhances and the driver's row (getSDataDriver) and its address follows fn_7100247580's. What it does: the work
    // fn_7100247580's comment describes, on one driver's data.
    static bool fn_71002475DC(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriver& data);
};
}  // namespace gf

#endif
