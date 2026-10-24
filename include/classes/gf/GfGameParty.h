#ifndef CLASSES_GF_GFGAMEPARTY_H
#define CLASSES_GF_GFGAMEPARTY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameParty; }
namespace gf { class GfComTransform; }
#include "classes/gf/IGfObjListener.h"

namespace gf {
// a base of gf::GfGameParty no evidence names yet
class TUnk_B553D8 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B553B0; base at 0x8 unknown (TUnk_B553D8)
class GfGameParty : public ::mm::mtl::PtrSingleton< ::gf::GfGameParty>, public TUnk_B553D8 {
public:
    static void gevGameObjEnter(gf::GF_OBJ_HANDLE*);
    static void gevGameObjLeave(gf::GF_OBJ_HANDLE*);
    static void refreshPartyMemberPosition();
    static gf::GF_OBJ_HANDLE* getHandleMover(unsigned int id);
    static void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int);
    static void gevPartyIDMemberOK(bool, unsigned int);
    virtual ~GfGameParty();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    static gf::GfComTransform* getLeaderTransform();  // the leader's transform, null for none
    static gf::GF_OBJ_HANDLE* getLeader();  // the party's leader, -1 for none
    static bool isBtlLeaderDirver();
    static bool isLeaderDriver(gf::GF_OBJ_HANDLE* handle);
    // the bdat ID of the party member driver at an index, and of the blade in a slot of its driver
    // (3.0.1 passes a second argument, 0 here, through to the party data; 1.0.0 has only the first)
    static unsigned int getDriverBdatId(unsigned int index, unsigned int party);
    static unsigned int getBladeBdatId(unsigned int index, int slot);
    static unsigned int getPartyId(gf::GF_OBJ_HANDLE* handle);
    static gf::GF_OBJ_HANDLE* getLeaderDriver();
    // the handle of the party member driver at an index, and of the blade in a slot of the driver at an index
    // (3.0.1's getHandleDriver reads a second argument too, as getDriverBdatId does: StateUtil passes 0; its symbol
    // still spells one argument)
    static gf::GF_OBJ_HANDLE* getHandleDriver(unsigned int index, unsigned int party);
    static gf::GF_OBJ_HANDLE* getHandleBlade(unsigned int index, int slot);
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
};
}  // namespace gf

#endif
