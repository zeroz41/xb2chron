#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; namespace mtl { template <int LEN> class FixStr; } }
namespace gmk { enum GmkType : int; }

namespace gf {

// game-wide helpers (functions, by its symbols)
class GfGameUtil {
public:
    static void clearEnemyRepopCounter(int enemy);
    // switches the current Homura/Hikari blade (true: to Hikari); GfMenuObjCharSelect::seqSpHomuraToHikari and
    // seqSpHikariToHomura call it
    static void changeHikariCurrent(bool hikari);
    // GfGameEvent::setGmkIdDisp and setGmkBdatDisp forward to them
    static void setDispByGmkTypeAndGmkIdx(gmk::GmkType type, unsigned int idx, bool flag);
    static void setDispByGmkTypeAndBdatId(gmk::GmkType type, int bdatId, bool flag);
    static bool getGmkTargetPointPos(mm::Vec3& pos, gf::GF_OBJ_HANDLE* handle);
    static bool getGmkTargetPointPos(mm::Vec3& pos, unsigned int id);
    // SCOM_ADD_DEVELOP's request passes its second value, then its first
    static void addDevelopPoint(unsigned int, unsigned int);
    static void setHp(GF_OBJ_HANDLE* handle, unsigned int hp);
    static void incGameClearCount();
    // whether the object's weapon (mount 2) holds an object in slot 1 or 2 of its set in use
    static bool hasBelonging(gf::GF_OBJ_HANDLE* handle, unsigned int slot);
    static bool execActivateReserverForBlade(unsigned int blade);
    // sends the driver's party object its maximum hit points again (DataParamAcc::getHpMax)
    static void refreshEnhanceState(unsigned int driver);
    // hands a driver its default accessory once (CHR_Dr's DefAcce) and equips it in slot 0
    static void execEquipDriverDefaultAcce(unsigned int driver);
    // SCOM_POPUP::createAchievement passes its blade, line and level; when it returns true no popup is queued
    static bool setupSaveAchievementPopup(unsigned int, unsigned int, unsigned int);
    static bool isCondDriverModel(unsigned int);
    static const char* getBladeModel(unsigned int blade, bool flag);
    static const char* getBladeMotion(unsigned int blade, bool flag);
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
    // the name of a weapon's battle (or field) command for a weapon id (GfEvtModelWeapon's commands; the meaning of
    // the last flag is not known)
    static void makeWeaponCommandBattle(mm::mtl::FixStr<32>& out, unsigned int weaponId, bool battle, bool arg);
    // shows or hides the gimmicks of a type
    static void setDispByGmkType(gmk::GmkType type, bool disp);
    // the object's wire to target (GfAppendWire, through GfGameScene::getAppendControl)
    static void startWire(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* target, float time);
    static void startWireWithClose(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* target, float time, float, float);
    static void endWire(gf::GF_OBJ_HANDLE* handle, float time);
    // the objects of an enemy arrange id: live ones plus ones still set up
    static int getObjNumberByEnArrangeId(unsigned int arrangeId);
    static void setMaxPartyGauge();  // the battle party gauge to 300
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
    static void dispMetsuCrystal(gf::GF_OBJ_HANDLE* handle, bool disp);
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
    static void debugHpZero(gf::GF_OBJ_HANDLE* handle);
    static void execSaveAchievementPopup(unsigned int blade);
    // the HP the UI shows for an object and its maximum (false when it has none)
    static bool getNowHpForUi(gf::GF_OBJ_HANDLE* handle, unsigned int* hp);
    static bool getMaxHpForUi(gf::GF_OBJ_HANDLE* handle, unsigned int* hp);
    // whether the object is near enough for its name / info icon to show
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
