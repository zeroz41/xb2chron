#ifndef CLASSES_GF_GFGAMEENV_H
#define CLASSES_GF_GFGAMEENV_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { class Vec3; }

namespace gf { class GfGameEnv; }
namespace gf {
// the handles GfGameEnv's create functions return (GfGameEvent keeps them, 0 for none)
enum CFILTER_HANDLE : int;
enum CLOUD_SEA_HANDLE : int;
enum CLOUD_SEA : int;
enum CLOUD_SEA_PRIO : int;
}
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B54838
class GfGameEnv : public ::mm::mtl::PtrSingleton< ::gf::GfGameEnv> {
public:
    virtual ~GfGameEnv();  // slot 0
    static bool isRoom();
    static unsigned int getMapJumpID();
    static int getMapID();
    static void destroyColorFilter(CFILTER_HANDLE handle);  // GfGameEvent::finalize's
    static CLOUD_SEA_HANDLE createCloudSea(CLOUD_SEA type, CLOUD_SEA_PRIO prio);
    static void destroyCloudSea(CLOUD_SEA_HANDLE handle);
    static void setMapID(unsigned int, unsigned int);
    static bool isMapjump();
    static bool isMapjumpWithSaveData();
    static void gevGameState(GF_STATE, GF_STATE);
    static void sendPlayerPositionToRender(const mm::Vec3& pos);
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void clear();
    static void gevPlayEvent(gf::GEV gev, unsigned int id);
};
}  // namespace gf

namespace gf {
// Unnamed class (TUnk_<table low address>, counted as debt): the symbols leave it unnamed (its tables are lbl_7100B54858 and its
// PtrSingleton base's lbl_7100B54878, its instance lbl_7100C23300). New in 3.0.1 (1.0.0 has no such object).
// gf_game_env.cpp's fn_71002A752C creates it (0x10 bytes, line 1258) from GfGameManager::initialize. What it does:
// keeps the add-on content state: its functions refresh the local flags 0xD781-0xD787 from GfDataAoc's counts
// (fn_71002229C0(1..3)), answer whether an encoded add-on item is owned (fn_71002A75DC) and hold the mode int that
// GfGameManager::fn_71002A9E68 tests for 1.
class TUnk_B54858 : public ::mm::mtl::PtrSingleton< ::gf::TUnk_B54858> {
public:
    virtual ~TUnk_B54858() {}  // slot 0 (its table's D2 slot holds the base's)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfGameManager::fn_71002AC558
    // passes the instance. What it does: sets GfDataGame's bit 0 of 0xFD6D0 to (mode == 1), stores mode at 0x8 and
    // refreshes the add-on flags 0xD781-0xD787 (as fn_71002A7468).
    void fn_71002A7430(int mode);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfGameManager::fn_71002AC598
    // passes the instance. What it does: decodes id (kind = bits 16-19, needed count = bits 8-15), true when
    // GfDataAoc's count of that kind reaches it; kind 4 (0x401xx/0x402xx) also asks GfBdatShop::fn_710021E7CC.
    bool fn_71002A75DC(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfGameManager's IGfEvent slot 46
    // override passes the instance. What it does: for id >= 35353 refreshes the add-on flags (fn_71002A7468).
    void fn_71002A7734(unsigned int id);

    int m_mode;  // 0x8 (the name is not the original's) 1 in the mode GfGameManager::fn_71002A9E68 tests
};
}  // namespace gf

#endif
