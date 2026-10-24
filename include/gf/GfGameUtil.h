#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; namespace mtl { template <int LEN> class FixStr; } }
namespace gmk { enum GmkType : int; }

namespace gf {

// game-wide helpers (functions, by its symbols)
class GfGameUtil {
public:
    static bool getGmkTargetPointPos(mm::Vec3& pos, gf::GF_OBJ_HANDLE* handle);
    static bool getGmkTargetPointPos(mm::Vec3& pos, unsigned int id);
    // SCOM_ADD_DEVELOP's request passes its second value, then its first
    static void addDevelopPoint(unsigned int, unsigned int);
    static void setHp(GF_OBJ_HANDLE* handle, unsigned int hp);
    static void incGameClearCount();
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
};

}  // namespace gf

#endif
