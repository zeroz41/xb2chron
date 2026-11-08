#ifndef CLASSES_GF_GFGAMEPARTY_H
#define CLASSES_GF_GFGAMEPARTY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { enum GEV : int; }
namespace gf { enum PTPOS : unsigned int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameParty; }
namespace gf { class GfComTransform; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfStatusProperty.h"
#include "gf/GfReqParam.h"
#include "gf/GfSelectBlade.h"
#include "gf/GfSelectIra.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfObj; class GfSetupParam; class GfWeapon; struct GfPartyPosInfo; }

namespace gf {
// a party member's objects (0x50 bytes; GfGameParty holds three, by party slot). Its constructor and destructor
// clear the handles to -1 (1.0.0's GfMemberInfo::GfMemberInfo, clear and ~GfMemberInfo; 3.0.1 inlines them).
class GfMemberInfo {
public:
    GfMemberInfo() { clear(); }
    ~GfMemberInfo() { clear(); }
    // the first eight handles from last to first, then the ninth: the order of 3.0.1's stores in
    // FixedArray<GfMemberInfo, 3>'s destructor and GfGameParty's constructor (1.0.0's clear, with seven handles,
    // stores the first six likewise, then the seventh)
    void clear() {
        for (int i = 7; i >= 0; --i) {
            m_handles[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
        m_handles[8] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }

    // the member's object handles: 0 the driver (getHandleDriver reads its index by the party argument),
    // 3-5 the blades by set (getHandleBlade); the names are not the original's
    GF_OBJ_HANDLE* m_handles[9];
    mm::mtl::IntrusivePtr<GfStatusProperty> m_statusProperty;  // getPartyStatusProperty
};

// table 0x7100B553B0; the base at 0x8 is the object listener GfObjManager::addListener registers (the constructor
// passes this+8)
class GfGameParty : public ::mm::mtl::PtrSingleton< ::gf::GfGameParty>, public IGfObjListener {
public:
    GfGameParty(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    // the return type is not proven (its only caller, RandPlayer::Warp::update, ignores it)
    static void judgeRandomTalkWarp();
    void update(const fw::UpdateInfo& info);
    // 1.0.0's (3.0.1 inlines them in the constructor and destroy)
    void initialize(const GfSetupParam&) {
        m_partyIdMemberOK[0] = 0;
        m_partyIdMemberOK[1] = 0;
        m_partyIdMemberOK[2] = 0;
        m_initialized = true;
    }
    void finalize() { m_initialized = false; }
    static gf::GF_OBJ_HANDLE* getHandleByHierarchy(unsigned int hierarchy);
    // the blade set of the driver at an index: a set given (not negative) as it is, else the driver's
    static int getBladeSetId(unsigned int index, int set);
    static GfStatusProperty* getPartyStatusProperty(unsigned int index);
    static void setPartyGauge(unsigned short gauge);
    static gf::GfObj* getLeaderTransformObj();  // the controlled mover's object
    void createdObject(gf::GF_OBJ_HANDLE* handle);
    // createdObject's blade and weapon cases: the blade goes into its party slot's handle of its set (a trinity
    // blade's ninth handle is only checked), the weapon into its driver's GfWeapon list by its mount index
    void buildObjBlade(gf::GF_OBJ_HANDLE* handle);
    void buildObjWeapon(gf::GF_OBJ_HANDLE* handle);
    // gives the member at an index a new status property with the hit points given (the second argument is unused)
    static void createPartyStatusProperty(unsigned int index, unsigned int, unsigned int hp);
    // the driver slot's blade set to start battles with: its driver's current one
    static void setupBattleStart(unsigned int index);
    static void gevGameObjEnter(gf::GF_OBJ_HANDLE*);
    static void gevGameObjLeave(gf::GF_OBJ_HANDLE*);
    static void refreshPartyMemberPosition();
    // whether the party members are in the game (GfObjUtil::applyExecUpdate updates flag-18 objects only then)
    static bool isPartyMemberInGameObj();
    static gf::GF_OBJ_HANDLE* getHandleMover(unsigned int id);
    static void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int);
    static void gevPartyIDMemberOK(bool, unsigned int);
    virtual ~GfGameParty();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    static gf::GfComTransform* getLeaderTransform();  // the leader's transform, null for none
    static gf::GF_OBJ_HANDLE* getLeader();  // the party's leader, -1 for none
    // the leader's level (getLevel of its DataParamAcc; GfMenuObjTargetCursor::update compares a target's with it)
    static unsigned int getLeaderLevel();
    static void getCurrentPartyInfo(RQ_SETUP_PARTY& info);
    static void getCurrentPartyInfo(RQ_SETUP_PARTY_DRIVER& info);
    // 3.0.1's symbol name: GfArenaParty::setupLevelForBattleEnd passes its RQ_SETUP_PARTY
    static void setupRequestData(const RQ_SETUP_PARTY& info);
    // the hierarchy of a party member's driver or blade (0 for none; the return type is not proven)
    static unsigned int getHierarchyByHandle(gf::GF_OBJ_HANDLE* handle);
    static bool isBtlLeaderDirver();
    static bool isLeaderDriver(gf::GF_OBJ_HANDLE* handle);
    // the bdat ID of the party member driver at an index, and of the blade in a slot of its driver
    // (3.0.1 passes a second argument, 0 here, through to the party data; 1.0.0 has only the first; 2.0.0's symbols
    // type it gf::PTPOS)
    static unsigned int getDriverBdatId(unsigned int index, PTPOS party);
    static unsigned int getBladeBdatId(unsigned int index, int slot);
    static unsigned int getPartyId(gf::GF_OBJ_HANDLE* handle);
    // the party of a member by id (GfGameUtil::isCondBladeModel passes 4 and a blade id; the names are not the
    // original's)
    static unsigned int getPartyId(unsigned int kind, unsigned int id);
    static gf::GF_OBJ_HANDLE* getLeaderDriver();
    // the handle of the party member driver at an index, and of the blade in a slot of the driver at an index
    // (3.0.1's getHandleDriver reads a second argument too, as getDriverBdatId does: StateUtil passes 0; 2.0.0's
    // symbols type it gf::PTPOS)
    static gf::GF_OBJ_HANDLE* getHandleDriver(unsigned int index, PTPOS party);
    static gf::GF_OBJ_HANDLE* getHandleBlade(unsigned int index, int slot);
    // the handle of the party driver of a driver id (GfGameUtil::refreshEnhanceState)
    static gf::GF_OBJ_HANDLE* getHandleDriverByBdatID(unsigned int driver);
    // the handle of the party blade of a blade id (the members 0-2's current blades)
    static gf::GF_OBJ_HANDLE* getHandleBladeByBdatID(unsigned int blade);
    // 2.0.0's symbols name them. Statics of GfGameParty: their addresses lie in gf_game_party's unit and they read
    // PtrSingleton<GfGameParty> (the driver handle of party slot `slot`, entries of 0x50 from +0x10; -1 for slot -1 or
    // no party). What they do: GfObjUtil::getObj of that handle, then GfGameMoverSwitcher's object at +8 gets, through
    // its table slot 3, the object's +0xE0 and a 0x18-byte message {0x33, 0x01000000, 0, slot, ...}:
    // switchFormationForIra with words {0, 1}, switchFormationForIraFR with {0, 2}, switchFormationForIraBR with {1,
    // ...}. GfPlayComResetBlade::update calls them for its mode 0, 1, 2 when GfGameManager::isGameTypeIra answers true
    // and the slot is 0-2; ChainAttackManager::UpdateProc calls switchFormationForIraFR too.
    static void switchFormationForIra(unsigned int slot);
    static void switchFormationForIraFR(unsigned int slot);
    static void switchFormationForIraBR(unsigned int slot);
    static unsigned short getPartyGauge();  // GfMenuBattleAdapter shows it in hundreds (300 full)
    static bool isLeaderBlade();
    // 2.0.0's symbols name them. They lie in gf_game_party's unit and GfGameManager's gevBattleStart / gevBattleEnd
    // call them on PtrSingleton<GfGameParty>'s instance. What they do: gevBattleStart, unless m_selectIra's
    // m_currentPartyValid (0x370) is set, stores getCurrentPartyInfo in its RQ_SETUP_PARTY (0x130) and sets that byte (a
    // party snapshot taken once when a battle starts); gevBattleEnd is empty.
    void gevBattleStart();
    void gevBattleEnd();
    // 2.0.0's symbols name it. What it does: for GEV 10 only, calls GfSelectIra::restorePartyMember on m_selectIra
    // (0x130).
    void gevPlayEvent(gf::GEV gev, unsigned int id);
    // 1.0.0's listenerGfObj hands these an object event's handle
    void entryHandle(gf::GF_OBJ_HANDLE* handle, unsigned int type);
    void destroyedObject(gf::GF_OBJ_HANDLE* handle);
    void removeHandle(gf::GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: through the object's GfComCollider sets or clears collider states,
    // GfObjAcc::setDisp / setAlphaNormal by the flag, then repeats for the object's followers
    // (GfObjManager::getFollowObj); BattleCharacter::SetAction and ChainAttackManager::UpdateProc call it too.
    static void setDispIraParty(gf::GF_OBJ_HANDLE* handle, bool flag);
    // 2.0.0's symbols name them. Static members: they lie in gf_game_party's unit and read PtrSingleton<GfGameParty>'s
    // instance. What they do: isNeedResetBladeForIra returns m_selectIra's m_currentPartyValid (false without an
    // instance), getDummpMover returns m_warpObj (-1 without one).
    static bool isNeedResetBladeForIra();
    static gf::GF_OBJ_HANDLE* getDummpMover();
    // 2.0.0's symbols name it. What it does: counts the party slots 0-2 whose driver handle GfObjUtil::isValid accepts.
    static unsigned int getDriverNum();
    // 1.0.0's getHierarchyMax (same place, after getBladeBdatId; it took the largest m_hierarchyDriver /
    // m_hierarchyBlade of the members 0-2, 3.0.1 does so over every party in m_hierarchy)
    static unsigned int getHierarchyMax();
    // the symbols name it (recalcHierarchy calls it). What it does: clears the hierarchy fields of the members 0-2 of
    // every party in m_hierarchy, makes the leader's driver hierarchy 1 (a leader of type 3 is the driver of party 0's
    // member 0; else the first member with a driver becomes the leader), then numbers from 2 the drivers left: the
    // leader's slot first, then the members 0-2, parties other than 2 before party 2
    static void recalcHierarchyIra();
    // the symbols name it (1.0.0 has it too). What it does: in an Ira game recalcHierarchyIra; else clears the
    // hierarchy fields of the members 0-2, gives the leader (type 3 a driver, 4 a blade; else the first member with a
    // driver becomes a type 3 leader) hierarchy 1, then numbers the leader's member and the members 0-2 on: driver,
    // then blade, or blade first when the driver's DataParamAcc answers isScenarioMask
    static void recalcHierarchy();
    // 2.0.0's symbols name it. What it does: resets m_hierarchy to {0}, adding 1 and 2 when
    // GfGameManager::isGameTypeIra answers true.
    void setupGame();
    // the symbols name them (GfManager's setupNewGame and setupPowerNewGame call them without an object)
    static void setupNewGameParty();
    static void setupPoweredNewGameParty();
    static void setupPartyPositionByPartyPosition(const GfPartyPosInfo& info);
    // the symbols name it. What it does: the position and y rotation of every hierarchy's object (1-6, 1-9 in an
    // Ira game) into its record, valid when the object has a transform
    static void getPartyPosition(GfPartyPosInfo& info);
    static gf::GfWeapon* getHandleWeapon(unsigned int index, int set);
    // the symbols name it. What it does: destroys every object of getHandleWeapon's weapon, both sets (the second,
    // then the first, each made the one in use), clearing their handles (GfGameUnit::destroyParty calls it)
    static void destroyHandleWeapon(unsigned int index, int set);
    // 2.0.0's symbols name it. What it does: for a driver object, its weapon: its own mount
    // (GfMountManager::getGfWeapon) when GfDataDriver::isIra accepts its driver id, else its party slot's
    // (getHandleWeapon with set -1); null for others (BattleCharacter::AttackTimingProc calls it).
    static gf::GfWeapon* getHandleWeaponDriver(gf::GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name them (update calls checkPartyObjReady, which asks isReadyAllObjDisplay)
    void checkPartyObjReady();
    // 2.0.0's symbols name them. getPartyMemberNum counts the party's drivers and (outside an Ira game) their engaged
    // blades; isExistObj answers whether one of the members' objects is being destroyed (the return types are not
    // proven)
    static int getPartyMemberNum();
    static bool isExistObj();
    bool isReadyAllObjDisplay(bool);
    // the symbols name it. What it does: false while a request of type 0x16 is under way, true for an empty party;
    // else whether every party member's object and loaded blade is valid or entered and there is a controlled mover
    static bool isReadyObj();
    // the symbols name it (SCOM_PARTY_ADD::exec asks it). What it does: whether a party member driver (the one at
    // index, every one for -1) has an object whose validity equals its driver's isScenarioMask
    static bool isExistMismatchScenarioMask(unsigned int index);
    // 2.0.0's symbols name it. What it does: for an object outside battle, hides it (setDispIraParty false) at party
    // position 2, else shows and fades it in (and its weapon for a driver GfDataDriver::isIraHideWeaponOnField takes)
    static void setupChangePartyPos(gf::GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: swaps the drivers of two parties' members at an index (their DLC records'
    // party index too) and the member's handles at those positions; the leader follows slot 0 of party 0
    void swapMemberForIra(unsigned int index, PTPOS a, PTPOS b);

    mm::mtl::FixedArray<GfMemberInfo, 3> m_members;  // by party slot
    bool m_initialized;  // 1.0.0's initialize sets it, finalize clears it, isInitialized reads it
    unsigned char pad_101[0x3];
    GfSelectBlade m_selectBlade;
    unsigned char pad_124[0xC];
    GfSelectIra m_selectIra;  // the name is not the original's
    unsigned char pad_374[0xC];
    // frames since the party's objects got ready, counted to 100 (update announces callPartyMemberOK(true) at 2),
    // and the request to start over (update then announces callPartyMemberOK(false)); the names are not the
    // original's
    int m_memberOKCount;
    bool m_memberOKReset;
    unsigned char pad_385[0x3];
    GF_OBJ_HANDLE* m_leader;  // the leader update last announced (GfEvent::callChangeLeader), -1 for none
    // by party ID: 2 once callPartyIDMemberOK(true) was announced (listenerGfObj announces false when the member
    // leaves); the name is not the original's
    int m_partyIdMemberOK[3];
    unsigned char pad_39c[0x4];
    mm::mtl::FixedVector<unsigned int, 3> m_hierarchy;  // party slots in hierarchy order (getHandleByHierarchy)
    // the object update warps to the controlled mover's position each frame, -1 for none (getDummpMover returns
    // it); the name is not the original's
    GF_OBJ_HANDLE* m_warpObj;
};
}  // namespace gf

#endif
