#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; struct OwnerBonus; struct GfItem; }
namespace mm { namespace mtl { template <typename T, unsigned long N> class FixedVector; } }
namespace mm { class Vec3; namespace mtl { template <int LEN> class FixStr; template <typename T, unsigned long N> class FixedList; } }
namespace gmk { enum GmkType : int; }
namespace gf { class GfFieldLocator; }
namespace gf { class SDataBlade; enum GFDIFF : int; }
namespace mm { namespace mtl { template <typename T> class Vector; } }
namespace mm { class Mat44; }
namespace fw { class SoundPack; }

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
    static bool execTurnCmd(const ExecTurnCmdInfo& info);  // false when no behavior component took it
    static bool isTurnEnd(gf::GF_OBJ_HANDLE* handle);
    static bool execActivateReserverForBlade(unsigned int blade);
    static bool execActivateUnuseForBlade(unsigned int blade, bool releaseOrbs);
    // the boosters a released blade gives back, added to the party (GfMenuObjBladeRelease::seqExecRelease lists
    // them): true when there are any
    static bool execBoosterAddForReleaseBlade(mm::mtl::FixedVector<GfItem, 1024>& items, unsigned int blade);
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
    // 2.0.0's symbols name it. What it does: when GfDataDriver::isIraFront(driver) holds and getEquipWpnAcce(driver) is
    // 0, takes the accessory GfBdatChrDr's getChrIrDefWpnAcce(getChrDrIraParam(driver)) names, adds it to the item box
    // silently (if there is room) and hands it to GfItemUtil's unit's GfEquipUtil::equipIraWpnAcce with an empty handle. Its one
    // caller, GfGameScene::gevDriverActivate, calls it right after execEquipDriverDefaultAcce when a driver becomes
    // active.
    static void execEquipIraDefaultWpnAcce(unsigned int driver);
    // SCOM_POPUP::createAchievement passes its blade, line and level; when it returns true no popup is queued
    static bool setupSaveAchievementPopup(unsigned int, unsigned int, unsigned int);
    static bool isCondDriverModel(unsigned int);
    // 0 when done; else checkDriverSkillLevelUp's answer (1 line at its top, 2 not the next level, 3 too few
    // skill points, 4 locked); it inlines that check (3.0.1's code returns it in w0)
    static int execDriverSkillLevelUp(unsigned int driver, unsigned int line, unsigned int level, bool round);
    static int checkDriverSkillLevelUp(unsigned int driver, unsigned int line, unsigned int level, bool round);
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
    // (GfDataBlade::getEquipOrb by slot, getEquipOrbModel the name, getEquipOrbBlade the blade it is for, which must be
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
    // SCOM_ADD_TRUST::exec: (blade or driver, value); addTrustPointIra in the Torna mode (GfGameManager::isGameTypeIra)
    static void addTrustPoint(unsigned int id, unsigned int point);
    // 2.0.0's symbols name it (carried as setTrustPointForDebug before): addTrustPoint on the driver's getIraBlade
    static void addTrustPointIra(unsigned int driver, unsigned int point);
    // SCOM_CHAR_DEAD::exec passes the dead enemy's arrange id
    static void incEnemySuppress(unsigned int enemy);
    // SCOM_ADD_EXP::exec: inn experience (its value), else battle experience for a driver (driver, value)
    static void addExpInn(unsigned int exp);
    static void addExpBattle(unsigned int driver, unsigned int exp);
    // 2.0.0's symbols name it; SCOM_ADD_SP::exec calls it with (driver, value). What it does: addSp unless
    // GfGameManager::isGameTypeIra holds; then fn_71002DBB58 on the ChrDr getChrIrGroupID value of the driver (of each
    // of the ten party drivers for driver 0)
    static void addSpForObject(unsigned int driver, int sp);
    // Placeholder name: new in 3.0.1 (1.0.0's setFormationParam, 0x20C bytes, holds this loop itself), nothing names
    // it. A member because its only caller is GfGameUtil::setFormationParam, right before it. What it does: -1 for a
    // trinity blade; else the index (0-8) of the first GfGamePlayerFormation player whose object setup has the
    // handle's party id (GfGameParty::getPartyId) and whose GfObjUtil::getObjType and getPartyPos equal the
    // handle's; -1 when none does.
    static int fn_71002DE83C(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: for a driver whose DataParamAcc is not scenario-masked, adds sp to its
    // skill points (GfDataDriver::addSkillPoint).
    static void addSp(unsigned int driver, int sp);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because addSpForObject (its unit, right
    // before it) tail-calls it with its sp. What it does: for the DLC driver rows 0x11 to 0x19 whose GfBdatChrDr
    // getChrIrGroupID (of getChrDrIraParam) equals id and that are not GfDataDriver::isActivateUnuse, adds sp.
    static void fn_71002DBB58(unsigned int id, int sp);
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
    // stops or resumes the object's update layer (GfGameSalvage::setPartyNpcMove stops the party's members with it)
    static void changeStopLayer(gf::GF_OBJ_HANDLE* handle, bool stop);
    // the objects of an enemy arrange id: live ones plus ones still set up
    static int getObjNumberByEnArrangeId(unsigned int arrangeId);
    static void setMaxPartyGauge();  // the battle party gauge to 300
    static void setPartyChange10010();  // (symbols; the pt plugin's setPartyChange10010)
    static void setPartyChange10020();  // (symbols; the pt plugin's setPartyChange10020)
    // 3.0.1's takes a third argument (it tests bit 0 of w2; the symbols' Ejj is 1.0.0's two-argument signature);
    // ScriptPlayText's pt setDriverEnable passes (0, 1011, false). The third's name and type are inferred.
    // returns whether it went ahead (GfDataBlade::isActivateMercenaryTeam held): equipDriverBladeForce tail-calls it and returns 0
    // otherwise
    static bool execEquipMercenariesBlade(unsigned int driver, unsigned int blade, bool flag);
    // named by the symbols: adds a rare blade (GfDataBlade::addRareBlade) and, when that gives one, copies blade
    // 0x3FE's creator to 1050, marks its m_createEvent watched (setWatchedEvent) and calls GfEvent::callBladeActivate
    // from its previous activate type to 1; returns the new blade (0 for none)
    static unsigned int execAddRareBlade(const SDataBlade& data);
    // 2.0.0's symbols name it. What it does: when GfDataUtil::isClearGame holds and data's blade is
    // GfDataBlade::getStartCommonBlade, re-activates it (setActivateReserver) and returns it; else sets data's blade to
    // getStartCommonBlade for item 45010 (0 otherwise), adds it (GfDataBlade::addCommonBlade) and does
    // execAddRareBlade's watched-event and callBladeActivate(blade, 0, 1) steps; returns the new blade.
    static unsigned int execAddCommonBlade(SDataBlade& data, unsigned int item);
    static void setWatchedEvent(unsigned int event);  // (symbols)
    static void addTrusuPointByLastKizunaTalk();  // (symbols)
    // named by the symbols: raises the blade's trust rank by one up to 6 (GfDataBlade::setTrustRank), tells
    // GfEvent::callDebugChangeIdea(4, blade) and shows SCOM_POPUP::createAffinity for its driver (its set driver, else
    // its creator; with GfGameManager::isGameTypeIra GfDataDriver::getIraFront of GfDataBlade::getIraDriver)
    static void addTrustRankForKizunaRing(unsigned int blade);
    static void setSaikaLensOff(gf::GF_OBJ_HANDLE* handle);
    static void setSaikaLensOff();
    // named by the symbols: DataParamAcc::setBladeSet(select) on the object and, when it has a GfObj, sends it a
    // MsgUnk_1000045 with its attribute after and before the change
    static void setBladeSelect(gf::GF_OBJ_HANDLE* handle, int select);
    // 2.0.0's symbols name it. What it does: 1.0.0's pt setDriverEnable calls
    // GfDataDriver::equipDriverBladeFromReserverBlade(driver) at the same place; 3.0.1's calls this with driver 2 when
    // blade 1011 is not activate-unuse, and it calls execEquipMercenariesBlade. It returns false when
    // GfDataDriver::equipDriverBladeFromReserverBlade(driver) holds or the driver is not 1, 2, 3 or 6, else
    // execEquipMercenariesBlade's answer for the driver's blade (1: GfDataBlade::getStartCommonBlade, 2: 1004, 3: 1010,
    // 6: 1009).
    static bool equipDriverBladeForce(unsigned int driver);
    // (symbols) GfGameScene::gevDriverActivate calls it: takes off the driver's three accessories
    // (GfEquipUtil::equipDriverAcce with item 0) and unsets each blade the driver has engaged, last slot first
    static void execDriverDead(unsigned int driver);
    // 2.0.0's symbols name it. What it does: ScriptPlayText's pt changeKubira calls it with nothing; it reworks blades'
    // drivers, orbs, weapons and engage flags (GfDataBlade/GfEquipUtil) and calls SCOM_PARTY_ADD::removeBlade and
    // SCOM_CURRENT_BLADE::create.
    static void changeKubira();
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
    // sets or clears the object's flag 0x10, then the same for every object following it (GfObjManager::getFollowObj)
    static void setGameObjWait(gf::GF_OBJ_HANDLE* handle, bool wait);
    // an enemy set up again at its level plus add (at most the last ChrEnParam row), its maximum hit points
    // sent and the hit points it gains healed
    static void levelupForEnemy(gf::GF_OBJ_HANDLE* handle, unsigned int add);
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
    // 2.0.0's symbols name it. What it does: when the driver's level (GfDataDriver::getLevel) is above the level,
    // lowers it there (GfDataDriver::getBattleExp, getExp, getBattleExpNextLevel and the placeholders
    // setLevel/setExp/setBattleExp, the 999999999 experience cap). GfMenuObjLvupSelect::seqExecLevelUp calls it instead
    // of execLevelUp when the chosen level is lower.
    static void execLevelDown(unsigned int driver, unsigned int level);
    // raises the driver's level of the arts toward level (at most 5) while its weapon type's points cover
    // GfBdatBtl::getArtsDrNeedWP, spending them
    static void execDriverArtsLevelUp(unsigned int driver, unsigned int arts, unsigned int level);
    // the HP the UI shows for an object and its maximum (false when it has none)
    static bool getNowHpForUi(gf::GF_OBJ_HANDLE* handle, unsigned int* hp);
    static bool getMaxHpForUi(gf::GF_OBJ_HANDLE* handle, unsigned int* hp);
    // the object's HP (its property's, else its data's maximum) and maximum HP; type and id as DataParamAcc's
    static unsigned int getNowHp(gf::GF_OBJ_HANDLE* handle, unsigned int type, unsigned int id);
    static unsigned int getMaxHp(gf::GF_OBJ_HANDLE* handle, unsigned int type, unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies among
    // GfGameUtil's (right after getMaxHp) and its only callers are getNowHp, getMaxHp, getNowHpForUi and
    // getMaxHpForUi. What it does: for a valid driver object whose driver row GfDataDriver::isIra accepts,
    // collects GfDataDriver::getIraFront(driver) and GfDataDriver::getIraBack's list of driver ids and replaces
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
    // GfGameObj::enableGameObj calls it for a party driver or blade leaving the game
    static void resetFormationParam(gf::GF_OBJ_HANDLE* handle);
    // the object's formation index: its rebuilt driver's or blade's setup id when that is set, else its party
    // hierarchy - 1; -1 for a trinity blade or an object outside the party
    static int getFormationPlayerID(gf::GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: false for handle -1, a GfObjAcc with no object, a destroyed object
    // (isDestroy) or one with flag 0x11 (testFlag); for an object of type 6 whose bound gimmick (gmk::getBindedGmkInst)
    // has type 3 (its slot 2), whether the "flag" column of the gimmick's BDAT row (getBindedBdatFp, its row at 0x38)
    // holds the flag named "HITONOWAGET" (Bdat::getFlagVal) is nonzero. GfMenuGfObjAdapter::update_IRA_NpcHitonowaIcon
    // calls it.
    static bool getUiGetHitonowa(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What they do: when the arena game mode (GfGameArena::sys()) exists, send it a
    // MsgGameBtlArena of type 0xE (GfGameUtil::addEtherCube), 0xF (GfGameUtil::addScore) or 0x10
    // (GfGameUtil::applyClearTimeForArena) carrying value in its parameter word 0x30, 0x34 or 0x38. Callers: the exec
    // of the requests SCOM_ADD_ECUBE and SCOM_ADD_SCORE (their value at 0x1C) and gf_req_scom's SCOM_CLEAR_TIME::create.
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address is in
    // GfWeapon's unit among free placeholders and it takes only a handle. What it does: false unless the object is a
    // driver (GfObjUtil::getObjType 3); true when it is driver 0x11 whose GfComAsm (component 2) plays a layer-0 state
    // whose name holds "btstart", else whether GfMountManager::getMountType(handle, 0) is 1 or 3.
    // PlayerCameraTarget::writeTargetInfo takes it as m_isRiding in a battle.
    static bool isBattleWeapon(GF_OBJ_HANDLE* handle);
    static void addEtherCube(unsigned int value);
    static void addScore(unsigned int value);
    static void applyClearTimeForArena(unsigned int value);
    // 2.0.0's symbols name it. What it does: for a driver other than 0, lowers its experience (DataParamAcc(3,
    // driver).getExp()) by exp, down to 0 (at most 999999999), stores it (GfDataDriver::setExp) and, for a DLC driver
    // row (isIra), calls getIraFront on it; GfMenuObjBalloon::SelMoneyListener::reciveEvent calls it.
    static void subExpInn(unsigned int driver, unsigned int exp);
    // 2.0.0's symbols name it. What it does: a driver's class from the average trust rank (1..6) of the driver's active
    // party blades (GfDataDriver::getIraBack, GfGameUtil::getTrustRank) through GfBdatChrDr::getChrDrIraParam,
    // getChrIrGroupID and GfBdatBtl::getBTL_IrGroupRevGroupRev; GfMenuCharDataAdapter::update_DR_ClassBuffLv uses it
    // for the add-on (isValidExpansion(3)) driver class.
    static unsigned int getGroupClass(unsigned int driver);
    // 2.0.0's symbols name it. What it does: returns GfGameUtil::fn_71002DEFBC(blade) (a tail call);
    // GfAssetSetup::setRefResource calls it.
    static const char* getAcceBladeModel(unsigned int blade);
    // 2.0.0's symbols name it. What it does: the model name of driver id from GfBdatChrDr (getChrDrModel2,
    // getChrDrCondition with GfGameCond::isGameCond, then BDAT columns by the driver's id), first trying
    // fn_71002DF4C4(id, third argument); for driver 6 with the second argument set it also ORs in
    // isInvalidMelefRetarget's result. GfAssetSetupDriver's getMdlFile/getArcFile pass (id, create type in {2, 3, 11},
    // create type == 3), GfAssetSetupNpc::getMdlFile (id, false, create type == 3) for ids below 26.
    static const char* getDriverModel(unsigned int driverId, bool createTypeIn2311, bool createType3);
    // 2.0.0's symbols name it. What it does: fn_71002DF4C4(id, flag), where for driver 6 with the second argument set
    // flag also takes GfDataEvent::isInvalidMelefRetarget of GfGameEvent::getStartEventId() (as
    // GfGameUtil::getDriverModel does). GfAssetSetup::setRefResource calls it.
    static const char* getAcceDriverModel(unsigned int driverId, bool check, bool flag);
    // Placeholder name: GfWeapon's unit's function (callers GfGameObj::checkEnableGameObj, GfGameUtil::levelupForEnemy and
    // GfGameScene::gevChangeGameDifficult, which calls it on every object of list 5). A free function: its class is not known.
    static void refreshEnemyHp(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: for blade 1001, else 1002 (the first GfDataBlade::isActivateMercenaryTeam holds
    // for), cancels the mission of the blade's mercenary team (GfGameMercenaries::cancelMission of
    // GfDataMercenaries::getMissionIdByBlade) and clears that team's members (clearTeamMember of getTeamID);
    // GfGameScene::gevChangeScenarioFlag calls it.
    static void execClearMercenariesInHomuraHikari();
    // 2.0.0's symbols name it. What it does: for a handle other than -1, sets the alpha of its "medal" extra mesh
    // (GfObjAcc::getExtMeshIdx, setExtMeshAlpha) to 1 when show is set, else 0; fn_7100543F98 calls it.
    static void dispLauraMedal(GF_OBJ_HANDLE* handle, bool show);
    // 2.0.0's symbols name it. What it does: appends driver ids to the list: 17..25 for which GfDataDriver::isIraFront
    // holds while GfDataUtil::isIra's flag is set, else 1..8 (5 left out while GfDataUtil::isVandammeDead holds);
    // returns whether the list holds any.
    static bool getDriverAcceList(mm::mtl::FixedVector<unsigned short, 32>& list);
    // 2.0.0's symbols name it. What it does: when GfGameManager::isGameTypeIra holds, whether game condition 0xE86 does
    // not hold (GfGameCond::isGameCond); else whether GfDataUtil::getScenarioFlag() is below 5048.
    // GfMenuObjUtil::getFaceIconID and isIraSinMaskOff test it.
    static bool isDispSinMask();
    // 2.0.0's symbols name it. What it does: the address 0x4C bytes into the option data: tl::TitleMain's
    // getOptionBuffer when GfManager::isExecModeAdvertize or isExecModeThater holds and TitleMain exists, else
    // GfDataManager::getDataOption(). GfArenaBattle::mapjumpForReturnFieldForObjCleanup / execBattleSequence copy 0x3C bytes
    // into it. Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their
    // addresses are in GfWeapon's unit (no object). What they do: GfGameUtil::isDispLauraMedal: whether
    // GfDataUtil::getScenarioFlag() lies in 11100..11130 (caller fn_7100543F98).
    // GfGameUtil::isNeedRetargetDriverResource / GfGameUtil::getNeedRetargetDriverId: whether a model name contains
    // "pc110601" (true / 6, else false / 0; GfAssetSetupEnemy::setup and GfAssetSetupNpc::setup call both).
    // GfGameUtil::playSeForPartySwitch: plays menu sound effect 0x2E (GfMenuObjUtil::playSE;
    // GfReqCommand::execChangeBladeWithBladeId calls it). GfGameUtil::getDlcSePack / GfGameUtil::getDlcSeName:
    // GfFieldSound's getDlcSePack / getDlcSeName for name when GfFieldSound is up (none otherwise;
    // GfComSound::playSe2D calls both).
    static bool isDispLauraMedal();
    // 2.0.0's symbols name it. What it does: for drivers 1, 2, 3, 5 and 6 sets their blades back (mercenary blades by
    // GfGameUtil::execEquipMercenariesBlade, then the equipped one) and answers whether one was equipped;
    // GfArenaParty::removeFieldBlade passes (false, true).
    static bool execPartyBladeFollow(bool, bool);
    // 2.0.0's symbols name it. What it does: in the arena (GfGameArena::fn_7100291D54 holds)
    // GfGameArena::getWeaponDamage(handle), else DataParamAcc(handle).getWeaponDamage(false), as
    // GfGameUtil::getWpnStability does for the stability; btl::PlayerParameter::InitializeAttackParam calls it.
    static unsigned int getWpnDamage(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: DataParamAcc(handle).getWeaponStability(false);
    // btl::PlayerParameter::InitializeAttackParam calls it.
    static unsigned int getWpnStability(GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: false unless GfGameManager::isInstalledBattleArenaContents is true; then
    // true when GfItemUtil::getItemBoxCount(25497) is non-zero, else whether any of the five ints at
    // GfDataManager::getDataGame()+0x11AF18/0x11AF0C/0x11AF24/0x11AF30/0x11AF3C is non-zero.
    // GfFieldSound::createMapSound loads the "dlc_se_btl_spskill" sound pack when it is true.
    static bool isEnableBladeElma();
    // 2.0.0's symbols name it. What it does: whether the add-on blade is unlocked: 0x451 asks
    // GfGameAoc::isExistGameAoc(0x20101), 0x452/0x453 GfGameManager::isInstalledBattleArenaContents, 0x457 that one too,
    // item 25497 in the box and a first rule value set in row 25 of SDataGame's challenge rule table; every other blade
    // is.
    static bool isEnableBladeDlc(unsigned int blade);
    // 2.0.0's symbols name it. What it does: the row of GfBdatChrEnArrange whose getBTL_NamedListIraEnemyID (when
    // GfGameManager::isGameTypeIra holds, rows getBTL_NamedListIraStart up to getBTL_NamedListIraEnd) or
    // getBTL_NamedListEnemyID (rows getBTL_NamedListStart up to getBTL_NamedListEnd) equals enemy; 0 when none does.
    static unsigned int getNamedListIndex(unsigned int enemy);
    // 2.0.0's symbols name it. What it does: false when GfGameUtil::getNamedListIndex(enemy) gives no record, else
    // whether bit mode of that record's flag byte (0x14 bytes each in the game data, at 0x11B4DC) is set.
    // gf_menu_obj_named_list's updateNamedIDList passes a named enemy's "EnemyID" and
    // GfMenuObjOption::getDifficultyFromIndex's difficulty; its isDefeated passes GfGameManager::getBtlDifficult().
    static bool isDefeatNamed(unsigned int enemy, GFDIFF mode);
    // 2.0.0's symbols name it. What it does: GfGameUtil::getClearNamedTime with the record column chosen by mode
    // (0/1/2/4) instead of getBtlDifficult(); GfMenuCharDataAdapter::update_EN_DefeatedTime passes
    // GfMenuReference::getReferenceBtlchDifficulty().
    static unsigned int getClearNamedTime(unsigned int enemy, GFDIFF mode);
    // 2.0.0's symbols name it. What it does: -1 when GfGameUtil::getNamedListIndex(id) gives no record, else the int of
    // that record (0x14 bytes each in the game data) at 0x11B4CC/D0/D4/D8 for getBtlDifficult() 0/1/2/4 (-1 for other
    // values); GfMenuCharDataAdapter::update_EN_DefeatedTime2 shows it as minutes and seconds for an enemy (objType 5).
    static unsigned int getClearNamedTime(unsigned int enemy);
    // 2.0.0's symbols name it. What it does: unless GfGameManager::isEnableNamedRecord fails or isBattleArenaActive
    // holds, for GfGameUtil::getNamedListIndex(enemy)'s record (0x14 bytes each in the game data) keeps the time in the
    // column of mode (0/1/2/4, 0x11B4CC..) when the record's flag byte at 0x11B4DC has bit mode, else counts local flag
    // 8/0xFAF up (to 0xFF) when GfGameManager::isGameTypeIra holds. SCOM_ENBOOK_BOSS_TIME::exec passes its enemy, its
    // time and GfGameManager::getBtlDifficult() (1.0.0 called GfDataEnBook::setClearNamedTime(enemy, time) there).
    static void setClearNamedTime(unsigned int enemy, unsigned int time, GFDIFF mode);
    // 2.0.0's symbols name it. What they do: when GfGameScene is up, GfGameScene::fn_71002C4C0C(handle, target, flag)
    // with kind 0 (GfGameUtil::setIraBoneMountR) or 1 (GfGameUtil::setIraBoneMountL); btl::BattleCharacter::SetAction /
    // AsmCallback call them.
    static void setIraBoneMountR(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag);
    static void setIraBoneMountL(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag);
    // 2.0.0's symbols name it. What they do: false when the int at 0x10D7C of GfDataManager::getDataGameIra() is 0,
    // else whether GfBdatChrDr::getIRA_PartyGuest1 (GfGameUtil::isEnableIraSatahiko) / getIRA_PartyGuest2
    // (GfGameUtil::isEnableIraMilto) of it is non-zero. GfMenuObjPartyForm3::initialize shows "LAY_guest@01" /
    // "LAY_guest@02" by them (GfGameCond and event::ObjectList call them too).
    static bool isEnableIraSatahiko();
    static bool isEnableIraMilto();
    // 2.0.0's symbols name it. What it does: whether a blade is available: true for most IDs; 0x451..0x453 and 0x457
    // depend on GfGameAoc's content state and GfGameManager::isInstalledBattleArenaContents.
    // GfArenaParty::addFieldBlade / removeFieldBlade test it for each blade of GfBdatChrBl's range.
    static bool isEnableGameBlade(unsigned int blade);
    // 2.0.0's symbols name it. What it does: for driver 6 only, whether GfGameUtil::getDriverModel(6, ...) gives a
    // model name containing "pc110601" (false for other drivers); GfAssetSetupDriver::setup and
    // GfAssetSetupDriverForUi::setup call it.
    static bool isNeedRetargetDriver(unsigned int driverId, bool createTypeIn2311, bool createType3);
    static bool isNeedRetargetDriverResource(const char* name);
    static int getNeedRetargetDriverId(const char* name);
    // 2.0.0's symbols name it. What it does: the twin of isAdvancedDifficulity (same code with item 25495 for 25496).
    // Callers: TitleStateMainScreen::loadSaveDataForTitle, fn_7100154638 and GfMenuObjOption::initialize.
    static bool isAdvancedGameOption();
    // 2.0.0's symbols name it. What it does: takes GfDataManager::getDataGame (TitleMain's save buffer + 0x10 in the
    // theater or advertise mode), and calls ItemCountLowLevel::getCount on its 0xE98D8 and 0x11D27C areas with 0x6398; GfMenuObjOption's
    // difficulty lists use its answer to show all four difficulties.
    static bool isAdvancedDifficulity();
    static void playSeForPartySwitch();
    static fw::SoundPack* getDlcSePack(const char* name);
    static const char* getDlcSeName(const char* name);
};

}  // namespace gf

#endif
