#ifndef GF_GFDATADRIVER_H
#define GF_GFDATADRIVER_H

namespace gf { class SDataDriver; enum DBSLOT : int; }
namespace gf { struct SDataDriverDlc; }
namespace gf { enum FAVORITE : int; }
namespace gf { struct SDataIdea; class GfInitParamDriver; }

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

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
    // 1.0.0's names (the symbols still spell 3.0.1's copies fn_<address>: same call sites, same arguments; 3.0.1's
    // also cover the DLC drivers)
    static SDataDriver* getSDataDriver(unsigned int driver);  // fn_7100231C64
    static unsigned int getLevel(const SDataDriver& data);  // fn_710024572C
    // 1.0.0's name: its getLevel(unsigned int) has the same callers (GfMenuObjDrArtsSet2::ArtsListListener,
    // GfMenuObjLvupSelect's listeners) and reads getLevel(*getSDataDriver(driver)); the symbols spell fn_7100234674
    static unsigned int getLevel(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfDataDriver's functions and every caller passes it a driver row (getLevel, getExp, DataObjDriver). What it
    // does: for a DLC driver row (0x11-0x19) whose CHR_Ir "Type" is set, finds the first CHR_Ir row of the same
    // "GroupID" whose Type is 0 and returns its "driverID" (0x11 when there is none); any other row comes back as is.
    static unsigned int fn_71002417DC(unsigned int driver);
    static unsigned int getExp(const SDataDriver& data);  // fn_7100245AB4
    static unsigned int getBattleExp(const SDataDriver& data);  // fn_7100245B7C
    static unsigned int getExpNextLevel(const SDataDriver& data);  // fn_710024618C
    static unsigned int getBattleExpNextLevel(const SDataDriver& data);  // fn_7100245FA4
    static void addSkillPoint(SDataDriver& data, int point);  // fn_7100247F2C
    static bool isScenarioMask(unsigned int driver);  // fn_71002465D0
    static unsigned int getEquipAcce(const SDataDriver& data, unsigned int slot);  // fn_7100247778
    static void setEquipAcce(SDataDriver& data, unsigned int slot, unsigned int accessory);  // fn_7100247A94
    static void setEquipBlade(unsigned int driver, bool engage, int slot);
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
    // (appended by chardata) 1.0.0's names: its GfMenuCharDataAdapter::update_DR_LevelUpEnable / update_DR_IdeaPoint
    // call them at the same sites (the symbols call them fn_7100245C44 / fn_71002422C4)
    static bool isEnableLevelUp(unsigned int driver);
    static SDataIdea* getSDataIdea(unsigned int driver);
    static unsigned int getExpUsed(unsigned int driver);  // (appended by chardata)
    // takes the blade off the driver it is set to (GfGameUtil::execActivateReserverForBlade)
    static void unsetBlade(unsigned int blade);
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
    // "oj/oj300002" for create types 9 and 13, else "oj/oj300001", when the param's object id is 1; else none
    static const char* getBelongingModelName(const GfInitParamDriver& param);
    static bool isExistBlade(unsigned int driver);  // getListBlade finds any
    static bool getListBlade(mm::mtl::FixedVector<unsigned short, 422>& list, unsigned int driver);
    static unsigned int getDriverBySetBlade(unsigned int blade);  // the blade's m_setDriver
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its only caller is
    // GfDataDriver::isEnableLevelUp, which hands it getSDataDriver's data. What it does: whether the driver can level
    // up: compares getExp(data) with the growth table (GfBdatBtl::getGrowEnd, GfBdatChrDr::fn_71001F13E0/fn_71001F16A4).
    static bool fn_7100245C98(const SDataDriver& data);
};
}  // namespace gf

#endif
