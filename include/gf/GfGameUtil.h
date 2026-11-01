#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; struct OwnerBonus; }
namespace mm { class Vec3; namespace mtl { template <int LEN> class FixStr; template <typename T, unsigned long N> class FixedList; } }
namespace gmk { enum GmkType : int; }
namespace gf { class GfFieldLocator; }
namespace gf { class SDataBlade; }
namespace mm { namespace mtl { template <typename T> class Vector; } }
namespace mm { class Mat44; }

namespace gf {

// game-wide helpers (functions, by its symbols)
class GfGameUtil {
public:
    // the field locators the orderable quests ask for (GfMenuLocation::refreshLocator fills its list 3 from them)
    static void collectOrderableLocators(mm::mtl::Vector<GfFieldLocator>& locators);
    static void clearEnemyRepopCounter(int enemy);
    // switches the current Homura/Hikari blade (true: to Hikari); GfMenuObjCharSelect::seqSpHomuraToHikari and
    // seqSpHikariToHomura call it
    static void changeHikariCurrent(bool hikari);
    // GfGameEvent::setGmkIdDisp and setGmkBdatDisp forward to them
    static void setDispByGmkTypeAndGmkIdx(gmk::GmkType type, unsigned int idx, bool flag);
    static void setDispByGmkTypeAndBdatId(gmk::GmkType type, int bdatId, bool flag);
    static bool getGmkTargetPointPos(mm::Vec3& pos, gf::GF_OBJ_HANDLE* handle);
    // whether the game can be saved at a point (GfFieldGimmick::update asks it for the player's position)
    static bool isPointSavable(const mm::Vec3& pos);
    static bool getGmkTargetPointPos(mm::Vec3& pos, unsigned int id);
    // the matrix of the current map's npc gimmick of a BDAT row (the first gimmick set of the map's RSC_GmkSetList row);
    // false when there is none
    static bool findNpcMat44(mm::Mat44& mtx, int bdatId);
    // SCOM_ADD_DEVELOP's request passes its second value, then its first
    static void addDevelopPoint(unsigned int, unsigned int);
    static void setHp(GF_OBJ_HANDLE* handle, unsigned int hp);
    static void incGameClearCount();
    // whether the object's weapon (mount 2) holds an object in slot 1 or 2 of its set in use
    static bool hasBelonging(gf::GF_OBJ_HANDLE* handle, unsigned int slot);
    // a turn of an object: execTurnCmd hands the four floats to the object's behavior component's
    // execTurnCmd(float, float, float, float) (the field names are not the original's)
    struct ExecTurnCmdInfo {
        gf::GF_OBJ_HANDLE* m_handle;
        float m_rotY;  // the angle turned to
        float m_arg1;
        float m_arg2;
        float m_arg3;
    };
    static void execTurnCmd(const ExecTurnCmdInfo& info);
    static bool isTurnEnd(gf::GF_OBJ_HANDLE* handle);
    static bool execActivateReserverForBlade(unsigned int blade);
    static bool execActivateUnuseForBlade(unsigned int blade, bool releaseOrbs);
    static bool isDriverEquipBlade(unsigned int driver, unsigned int blade);
    // the blade's kizuna link row (DataObjBlade::getLinkNum and its neighbours read BTL_Bl_KizunaLink by it)
    static unsigned int getKizunaLink(unsigned int blade);
    static int getTrustRank(unsigned int blade);
    static void setAchievementReleaseLevel(unsigned int blade, unsigned int line, unsigned int level);
    // sends the driver's party object its maximum hit points again (DataParamAcc::getHpMax)
    static void refreshEnhanceState(unsigned int driver);
    static void getOwnerBonus(OwnerBonus& bonus);  // GfGameScene::updateParam refreshes its owner bonus with it
    // hands a driver its default accessory once (CHR_Dr's DefAcce) and equips it in slot 0
    static void execEquipDriverDefaultAcce(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies between
    // execEquipDriverDefaultAcce and execDriverDead among GfGameUtil's functions. What it does: when
    // GfDataDriver::fn_7100237A94(driver) holds and fn_7100247474(driver) is 0, takes the accessory GfBdatChrDr's
    // fn_71001F17B4(fn_71001F13E0(driver)) names, adds it to the item box silently (if there is room) and hands it
    // to GfItemUtil's unit's fn_71002FCD68 with an empty handle. Its one caller, GfGameScene::gevDriverActivate,
    // calls it right after execEquipDriverDefaultAcce when a driver becomes active.
    static void fn_71002EB4B8(unsigned int driver);
    // SCOM_POPUP::createAchievement passes its blade, line and level; when it returns true no popup is queued
    static bool setupSaveAchievementPopup(unsigned int, unsigned int, unsigned int);
    static bool isCondDriverModel(unsigned int);
    static void execDriverSkillLevelUp(unsigned int driver, unsigned int line, unsigned int level, bool round);
    // the blade's model condition holds (GfGameCond), outside battle (no forced normal Homura, its driver of party
    // 4 not in battle)
    static bool isCondBladeModel(unsigned int blade);
    // an alpha change (SCOM_OBJ_ALPHA) for the belonging in slot 1 or 2 of the object's weapon
    static void changeAlphaBelonging(GF_OBJ_HANDLE* handle, unsigned int slot, float alpha, float time);
    static const char* getBladeModel(unsigned int blade, bool flag);
    static const char* getBladeMotion(unsigned int blade, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfGameUtil's (right after getBladeModel, its only caller found). What it does: unless the blade is a Hana
    // (GfDataHana::isValid), the model name a GfBdatItem row of one of the blade's equipped orbs gives
    // (GfDataBlade::getEquipOrb by slot, fn_7100200F60 the name, fn_7100200FE4 the blade it is for, which must be
    // this blade); nullptr for none. getBladeModel falls back to SDataBlade::m_modelName.
    static const char* fn_71002DEFBC(unsigned int blade);
    static const char* getSalvageDriverModel(unsigned int driver);  // the salvage setup passes its object id
    // the player party enters a battle (GfPlayComBattleStart retries it up to 3 seconds); handle -1 for none
    static bool enterPlayerBattle(bool flag, GF_OBJ_HANDLE* handle, bool flag2);
    static void execDevelopLevelUp();
    // add to the party's money and coins (SCOM_ADD_MONEY, SCOM_ADD_COIN)
    static void addMoney(int money);
    static void addCoin(int coin);
    // SCOM_ADD_ETHER::create forwards its value
    static void addEther(int ether);
    // SCOM_ADD_TRUST::exec: (blade or driver, value); the debug setter in the Torna mode (GfGameManager::fn_71002A9E68)
    static void addTrustPoint(unsigned int id, unsigned int point);
    static void setTrustPointForDebug(unsigned int driver, unsigned int point);
    // SCOM_CHAR_DEAD::exec passes the dead enemy's arrange id
    static void incEnemySuppress(unsigned int enemy);
    // SCOM_ADD_EXP::exec: inn experience (its value), else battle experience for a driver (driver, value)
    static void addExpInn(unsigned int exp);
    static void addExpBattle(unsigned int driver, unsigned int exp);
    // SCOM_ADD_SP::exec: (driver, value)
    static void addSP(unsigned int driver, int sp);
    // SCOM_ADD_IDEA::exec: (driver, its third value, value)
    static void addIdeaPoint(unsigned int driver, unsigned int type, int point);
    // SCOM_ADD_WP::exec, by its mode: 0 addWp, 1 and 3 addWpForObject (driver, its second value, value), 2 addWpForReserve (value)
    static void addWp(unsigned int driver, unsigned int id, int wp);
    static void addWpForObject(unsigned int driver, unsigned int id, int wp);
    static void addWpForReserve(int wp);
    // whether the object behind a handle is playing a voice
    // the field skill check of an FSID row for an object of name message nameMsId: whether the party passes it
    // (AFieldSeq::seqCheckFs, GfFieldTbox::seqCheckFs)
    static bool evalSumFs(int fsId, unsigned int nameMsId);
    // the name message id of the object behind handle, into out
    static void getNameMsId(unsigned int& out, gf::GF_OBJ_HANDLE* handle);
    static bool isPlayVoice(gf::GF_OBJ_HANDLE* handle);
    static int getObjAttribute(gf::GF_OBJ_HANDLE* handle);
    // the object takes field damage (GfGameScene::setDamageCharacter)
    static void requestFieldDamage(gf::GF_OBJ_HANDLE* handle);
    // the object's menu offset id, for GfMenuBdat::getMenuOffset
    static int getUiOffsetId(gf::GF_OBJ_HANDLE* handle);
    // the object a weapon object belongs to
    static gf::GF_OBJ_HANDLE* getWeaponOwner(gf::GF_OBJ_HANDLE* handle);
    // the name of a weapon's idle state for its owner, in battle or not
    static void makeWeaponStateIdle(mm::mtl::FixStr<32>& out, gf::GF_OBJ_HANDLE* owner, bool battle);
    // the same for a weapon id (GfEvtModelWeapon's states; the parameter names are not the original's)
    static void makeWeaponStateIdle(mm::mtl::FixStr<32>& out, unsigned int weaponId, bool battle);
    // the name of a weapon's battle (or field) command for a weapon id (GfEvtModelWeapon's commands);
    // the last flag picks the motion resource's name over the model's (the parameter names are not the original's)
    static void makeWeaponCommandBattle(mm::mtl::FixStr<32>& out, unsigned int weaponId, bool battle, bool motion);
    // the same for the weapon's owner object
    static void makeWeaponCommandBattle(mm::mtl::FixStr<32>& out, gf::GF_OBJ_HANDLE* owner, bool battle, bool motion);
    // shows or hides the gimmicks of a type
    static void setDispByGmkType(gmk::GmkType type, bool disp);
    // adds the game objects of every gimmick of a type (enemies, mobs, NPCs, map objects and their routed kinds);
    // false while there is no valid gimmick manager or for another type
    static bool collectGfObjHandleByGmkType(mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>& list, gmk::GmkType type);
    // the object's wire to target (GfAppendWire, through GfGameScene::getAppendControl)
    static void startWire(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* target, float time);
    static void startWireWithClose(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* target, float time, float, float);
    static void endWire(gf::GF_OBJ_HANDLE* handle, float time);
    // the objects of an enemy arrange id: live ones plus ones still set up
    static int getObjNumberByEnArrangeId(unsigned int arrangeId);
    static void setMaxPartyGauge();  // the battle party gauge to 300
    static void setPartyChange10010();  // (symbols; the pt plugin's setPartyChange10010)
    static void setPartyChange10020();  // (symbols; the pt plugin's setPartyChange10020)
    // 3.0.1's takes a third argument (it tests bit 0 of w2; the symbols' Ejj is 1.0.0's two-argument signature);
    // ScriptPlayText's pt setDriverEnable passes (0, 1011, false). The third's name and type are inferred.
    // returns whether it went ahead (GfDataBlade::fn_71002383C8 held): fn_71002E16F4 tail-calls it and returns 0
    // otherwise
    static bool execEquipMercenariesBlade(unsigned int driver, unsigned int blade, bool flag);
    // named by the symbols: adds a rare blade (GfDataBlade::addRareBlade) and, when that gives one, copies blade
    // 0x3FE's creator to 1050, marks its m_createEvent watched (setWatchedEvent) and calls GfEvent::callBladeActivate
    // from its previous activate type to 1; returns the new blade (0 for none)
    static unsigned int execAddRareBlade(const SDataBlade& data);
    static void setWatchedEvent(unsigned int event);  // (symbols)
    // named by the symbols: raises the blade's trust rank by one up to 6 (GfDataBlade::setTrustRank), tells
    // GfEvent::callDebugChangeIdea(4, blade) and shows SCOM_POPUP::createAffinity for its driver (its set driver, else
    // its creator; with GfGameManager::fn_71002A9E68 GfDataDriver::fn_71002417DC of GfDataBlade::fn_7100236518)
    static void addTrustRankForKizunaRing(unsigned int blade);
    // named by the symbols: DataParamAcc::setBladeSet(select) on the object and, when it has a GfObj, sends it a
    // MsgUnk_1000045 with its attribute after and before the change
    static void setBladeSelect(gf::GF_OBJ_HANDLE* handle, int select);
    // Placeholder name: new in 3.0.1's shape, its address lies between GfGameUtil::execActivateMercenaryTeamForBlade
    // and execEquipMercenariesBlade (so a GfGameUtil member). What it does: 1.0.0's pt setDriverEnable calls
    // GfDataDriver::equipDriverBladeFromReserverBlade(driver) at the same place; 3.0.1's calls this with driver 2
    // when blade 1011 is not activate-unuse, and it calls execEquipMercenariesBlade.
    // It returns false when GfDataDriver::fn_7100241DD4(driver) holds or the driver is not 1, 2, 3 or 6, else
    // execEquipMercenariesBlade's answer for the driver's blade (1: GfDataBlade::getStartCommonBlade, 2: 1004,
    // 3: 1010, 6: 1009).
    static bool fn_71002E16F4(unsigned int driver);
    // (symbols) GfGameScene::gevDriverActivate calls it: takes off the driver's three accessories
    // (GfEquipUtil::equipDriverAcce with item 0) and unsets each blade the driver has engaged, last slot first
    static void execDriverDead(unsigned int driver);
    // Placeholder name: new in 3.0.1 (1.0.0's pt has no changeKubira). A GfGameUtil member because its address
    // follows setPartyChange10020's. What it does: ScriptPlayText's pt changeKubira calls it with nothing; it
    // reworks blades' drivers, orbs, weapons and engage flags (GfDataBlade/GfEquipUtil) and calls
    // SCOM_PARTY_ADD::removeBlade and SCOM_CURRENT_BLADE::create.
    static void fn_71002EBC90();
    static int getAntiBladeAreaBdatId();
    // the blade joins its mercenary team (false when it already is on one)
    static bool execActivateMercenaryTeamForBlade(unsigned int blade);
    static bool isDummyBlade(gf::GF_OBJ_HANDLE* handle);  // the object is a dummy blade
    // whether a blade waits in the village: not one of the three main blades (1001-1003) nor Hana, not engaged
    // and set to no driver
    static bool isBladeInVillage(unsigned int blade);
    // the crystals on the drivers' chests: whether each shows, and show or hide it on an object's model
    static bool isDispRexCrystal();
    static bool isDispHomuraCrystal();
    static bool isDispMetsuCrystal();
    static void dispRexCrystal(gf::GF_OBJ_HANDLE* handle, bool disp);
    static void dispHomuraCrystal(gf::GF_OBJ_HANDLE* handle, bool disp);  // "cc_homu" shown, "cc_zohar" the opposite
    static void dispMetsuCrystal(gf::GF_OBJ_HANDLE* handle, bool disp);
    // Kosmos (blade 0x40f, type 4): shows (or hides) and runs (or stops) the second (left) object of its first
    // mounted weapon's first handle set
    static void setKosmosArts3EnableBothWeapon(gf::GF_OBJ_HANDLE* handle, bool enable);
    // a driver's weapon objects (-1 for none): the mounted weapon's, else the one of attach slot 3
    static gf::GF_OBJ_HANDLE* getDriverWeaponRight(gf::GF_OBJ_HANDLE* handle);
    static gf::GF_OBJ_HANDLE* getDriverWeaponLeft(gf::GF_OBJ_HANDLE* handle);  // the active anti-blade area gimmick's row
    static bool isGameObjWait(gf::GF_OBJ_HANDLE* handle);  // the object's flag 0x10
    static gf::GF_OBJ_HANDLE* getBlade(gf::GF_OBJ_HANDLE* handle);  // the blade mounted on a driver

    // the text the action window shows for an object (the names are not the original's)
    struct UiActionWindowInfo {
        UiActionWindowInfo() : m_bdat(nullptr), m_id(-1) {}
        void create(gf::GF_OBJ_HANDLE* handle);  // the text for the object behind the handle
        unsigned char* m_bdat;  // the message table and its id, as ui::UIStr takes them
        unsigned int m_id;
    };
    static void makeCommandBattle(mm::mtl::FixStr<32>& out, bool battle);
    static void makeStateBattle(mm::mtl::FixStr<32>& out, gf::GF_OBJ_HANDLE* handle, bool battle);
    // the name of an object's idle state: "S_idle" out of battle, else by its blade's weapon type
    static void makeStateIdle(mm::mtl::FixStr<32>& out, gf::GF_OBJ_HANDLE* handle, bool battle);
    // the same for a blade id (its DataParamAcc's weapon type; the parameter names are not the original's)
    static void makeStateBattleByBlade(mm::mtl::FixStr<32>& out, unsigned int blade, bool battle);
    // the name of a blade's idle state: "S_idle" out of battle, else by its weapon type (nothing for blade 0)
    static void makeStateIdleByBlade(mm::mtl::FixStr<32>& out, unsigned int blade, bool battle);
    static void debugHpZero(gf::GF_OBJ_HANDLE* handle);
    static void execSaveAchievementPopup(unsigned int blade);
    // a driver's level raised to that level (GfMenuObjLvupSelect::seqExecLevelUp)
    static void execLevelUp(unsigned int driver, unsigned int level);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies right after
    // GfGameUtil::execLevelUp in its unit and takes the same arguments. What it does: when the driver's level
    // (GfDataDriver::getLevel) is above the level, lowers it there (GfDataDriver::fn_7100245EFC, fn_7100245EA8,
    // fn_7100245F50 and the placeholders fn_710024487C/fn_71002448D8/fn_7100244988, the 999999999 experience cap).
    // GfMenuObjLvupSelect::seqExecLevelUp calls it instead of execLevelUp when the chosen level is lower.
    static void fn_71002DB338(unsigned int driver, unsigned int level);
    // the HP the UI shows for an object and its maximum (false when it has none)
    static bool getNowHpForUi(gf::GF_OBJ_HANDLE* handle, unsigned int* hp);
    static bool getMaxHpForUi(gf::GF_OBJ_HANDLE* handle, unsigned int* hp);
    // the object's HP (its property's, else its data's maximum) and maximum HP; type and id as DataParamAcc's
    static unsigned int getNowHp(gf::GF_OBJ_HANDLE* handle, unsigned int type, unsigned int id);
    static unsigned int getMaxHp(gf::GF_OBJ_HANDLE* handle, unsigned int type, unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfGameUtil's (right after getMaxHp) and its only callers are getNowHp, getMaxHp, getNowHpForUi and
    // getMaxHpForUi. What it does: for a valid driver object whose driver row GfDataDriver::fn_710023F9A8 accepts,
    // collects GfDataDriver::fn_71002417DC(driver) and GfDataDriver::fn_71002416B4's list of driver ids and replaces
    // the handle with the first one GfGameParty::getHandleDriverByBdatID gives a valid object for.
    static void fn_71002DF8B0(gf::GF_OBJ_HANDLE*& handle);
    // whether the object is near enough for its name / info icon to show
    // how far from the interest position an object's name is shown (0 or less: never; isUiNameDistMatch squares it)
    static float getUiNameDist(gf::GF_OBJ_HANDLE* handle);
    static bool isUiNameDistMatch(gf::GF_OBJ_HANDLE* handle);
    static bool isUiInfoIconDistMatch(gf::GF_OBJ_HANDLE* handle);
    static int getUiInfoIconBdatId(gf::GF_OBJ_HANDLE* handle);  // -1: none
    // the status icons an enemy shows (the field names are not the original's)
    struct UiEnemyStatusIconInfo {
        UiEnemyStatusIconInfo() : m_aggressive(false), m_link(false) {}
        void create(gf::GF_OBJ_HANDLE* handle);
        bool m_aggressive;
        bool m_link;
    };
};

}  // namespace gf

#endif
