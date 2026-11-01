#ifndef CLASSES_GF_GFGAMEPARTY_H
#define CLASSES_GF_GFGAMEPARTY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { enum GEV : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameParty; }
namespace gf { class GfComTransform; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfStatusProperty.h"
#include "gf/GfReqParam.h"
#include "gf/GfSelectBlade.h"
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
        for (int i = 0; i < 3; ++i) {
            m_partyIdMemberOK[i] = 0;
        }
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
    // 3.0.1's symbol name: TUnk_28D7B8::fn_710028E15C passes its RQ_SETUP_PARTY
    static void setupRequestData(const RQ_SETUP_PARTY& info);
    // the hierarchy of a party member's driver or blade (0 for none; the return type is not proven)
    static unsigned int getHierarchyByHandle(gf::GF_OBJ_HANDLE* handle);
    static bool isBtlLeaderDirver();
    static bool isLeaderDriver(gf::GF_OBJ_HANDLE* handle);
    // the bdat ID of the party member driver at an index, and of the blade in a slot of its driver
    // (3.0.1 passes a second argument, 0 here, through to the party data; 1.0.0 has only the first)
    static unsigned int getDriverBdatId(unsigned int index, unsigned int party);
    static unsigned int getBladeBdatId(unsigned int index, int slot);
    static unsigned int getPartyId(gf::GF_OBJ_HANDLE* handle);
    // the party of a member by id (GfGameUtil::isCondBladeModel passes 4 and a blade id; the names are not the
    // original's)
    static unsigned int getPartyId(unsigned int kind, unsigned int id);
    static gf::GF_OBJ_HANDLE* getLeaderDriver();
    // the handle of the party member driver at an index, and of the blade in a slot of the driver at an index
    // (3.0.1's getHandleDriver reads a second argument too, as getDriverBdatId does: StateUtil passes 0; its symbol
    // still spells one argument)
    static gf::GF_OBJ_HANDLE* getHandleDriver(unsigned int index, unsigned int party);
    static gf::GF_OBJ_HANDLE* getHandleBlade(unsigned int index, int slot);
    // the handle of the party driver of a driver id (GfGameUtil::refreshEnhanceState)
    static gf::GF_OBJ_HANDLE* getHandleDriverByBdatID(unsigned int driver);
    // the handle of the party blade of a blade id (the members 0-2's current blades)
    static gf::GF_OBJ_HANDLE* getHandleBladeByBdatID(unsigned int blade);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0's GfPlayComResetBlade::update
    // has no such calls). Statics of GfGameParty: their addresses lie in gf_game_party's unit and they read
    // PtrSingleton<GfGameParty> (the driver handle of party slot `slot`, entries of 0x50 from +0x10; -1 for
    // slot -1 or no party). What they do: GfObjUtil::getObj of that handle, then GfGameMoverSwitcher's object
    // at +8 gets, through its table slot 3, the object's +0xE0 and a 0x18-byte message {0x33, 0x01000000, 0,
    // slot, ...}: fn_71002BC718 with words {0, 1}, fn_71002BC7AC with {0, 2}, fn_71002BC840 with {1, ...}.
    // GfPlayComResetBlade::update calls them for its mode 0, 1, 2 when GfGameManager::fn_71002A9E68 answers
    // true and the slot is 0-2; ChainAttackManager::UpdateProc calls fn_71002BC7AC too.
    static void fn_71002BC718(unsigned int slot);
    static void fn_71002BC7AC(unsigned int slot);
    static void fn_71002BC840(unsigned int slot);
    static unsigned short getPartyGauge();  // GfMenuBattleAdapter shows it in hundreds (300 full)
    static bool isLeaderBlade();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0's GfGameManager::gevBattleStart
    // and gevBattleEnd call only GfGameScene). Members: they lie in gf_game_party's unit and GfGameManager's
    // gevBattleStart / gevBattleEnd call them on PtrSingleton<GfGameParty>'s instance. What they do:
    // fn_71002B8D3C, unless the byte at 0x370 is set, stores getCurrentPartyInfo of the RQ_SETUP_PARTY at 0x130
    // and sets that byte (a party snapshot taken once when a battle starts); fn_71002B8D70 is empty.
    void fn_71002B8D3C();
    void fn_71002B8D70();
    // Placeholder name: new in 3.0.1 (1.0.0's GfGameManager::gevPlayEvent does not call it). A member: it lies in
    // gf_game_party's unit and GfGameManager::gevPlayEvent passes PtrSingleton<GfGameParty>'s instance, the GEV and
    // the id on. What it does: for GEV 10 only, hands the RQ_SETUP_PARTY at 0x130 to fn_71002B8D88.
    void fn_71002B8D74(gf::GEV gev, unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: it lies in
    // gf_game_party's unit and fn_71002B8D74 hands it the RQ_SETUP_PARTY at 0x130. What it does: fills a local
    // RQ_SETUP_PARTY with getCurrentPartyInfo and compares it with the one given, working on the members'
    // objects through GfObjUtil::getObj.
    static void fn_71002B8D88(RQ_SETUP_PARTY& party);
    // 1.0.0's listenerGfObj hands these an object event's handle
    void entryHandle(gf::GF_OBJ_HANDLE* handle, unsigned int type);
    void destroyedObject(gf::GF_OBJ_HANDLE* handle);
    void removeHandle(gf::GF_OBJ_HANDLE* handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: it lies in
    // gf_game_party's unit, and listenerGfObj calls it with an object handle. What it does: through the object's
    // GfComCollider sets or clears collider states, GfObjAcc::setDisp / setAlphaNormal by the flag, then repeats
    // for the object's followers (GfObjManager::getFollowObj); BattleCharacter::SetAction and
    // ChainAttackManager::UpdateProc call it too.
    static void fn_71002BC46C(gf::GF_OBJ_HANDLE* handle, bool flag);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members: they lie in
    // gf_game_party's unit and read PtrSingleton<GfGameParty>'s instance. What they do: fn_71002BC6D0 returns
    // m_currentPartyValid (false without an instance), fn_71002BC6F8 returns m_warpObj (-1 without one).
    static bool fn_71002BC6D0();
    static gf::GF_OBJ_HANDLE* fn_71002BC6F8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: it lies in
    // gf_game_party's unit and reads the members through getHandleDriver. What it does: counts the party slots
    // 0-2 whose driver handle GfObjUtil::isValid accepts.
    static unsigned int fn_71002BC338();
    // 1.0.0's getHierarchyMax (same place, after getBladeBdatId; it took the largest m_hierarchyDriver /
    // m_hierarchyBlade of the members 0-2, 3.0.1 does so over every party in m_hierarchy)
    static unsigned int getHierarchyMax();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it lies in gf_game_party's
    // unit and GfGameManager::setupGame passes PtrSingleton<GfGameParty>'s instance. What it does: resets
    // m_hierarchy to {0}, adding 1 and 2 when GfGameManager::fn_71002A9E68 answers true.
    void fn_71002BC3B4();
    static void setupPartyPositionByPartyPosition(const GfPartyPosInfo& info);
    static gf::GfWeapon* getHandleWeapon(unsigned int index, int set);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: it lies in
    // gf_game_party's unit and calls getHandleWeapon. What it does: for a driver object, its weapon: its own
    // mount (GfMountManager::getGfWeapon) when GfDataDriver::fn_710023F9A8 accepts its driver id, else its party
    // slot's (getHandleWeapon with set -1); null for others (BattleCharacter::AttackTimingProc calls it).
    static gf::GfWeapon* fn_71002B7C34(gf::GF_OBJ_HANDLE* handle);

    mm::mtl::FixedArray<GfMemberInfo, 3> m_members;  // by party slot
    bool m_initialized;  // 1.0.0's initialize sets it, finalize clears it, isInitialized reads it
    unsigned char pad_101[0x3];
    GfSelectBlade m_selectBlade;
    unsigned char pad_124[0xC];
    RQ_SETUP_PARTY m_currentParty;  // what getCurrentPartyInfo fills (the name is not the original's)
    bool m_currentPartyValid;  // set once m_currentParty is filled (the name is not the original's)
    unsigned char pad_371[0xF];
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
    // the object update warps to the controlled mover's position each frame, -1 for none (fn_71002BC6F8 returns
    // it); the name is not the original's
    GF_OBJ_HANDLE* m_warpObj;
};
}  // namespace gf

#endif
