#ifndef CLASSES_GF_SCOM_PARTY_ADD_H
#define CLASSES_GF_SCOM_PARTY_ADD_H

#include "classes/gf/SCOM.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedQueue.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_SCOM_HANDLE; }

namespace gf {
// what GfGameParty::getPartyPosition fills: one record per party slot (0x20 bytes each; the member names are
// not the original's: the constructor sets the position to mm::Vec3::zero and the rest to zero)
struct GfPartyPosInfo {
    struct Pos {
        Pos() : m_pos(mm::Vec3::zero), m_rotY(0), m_isValid(false) {}
        mm::Vec3 m_pos;
        // the y rotation setupPartyPositionByPartyPosition gives the slot's object setup (GfObjSetup::pad_30.y)
        float m_rotY;
        bool m_isValid;
    };
    Pos m_pos[9];
};

// table 0x7100B6AA10 (unnamed in the symbols; the PtrSingleton<SCOM_PARTY_ADD> part at +0x20): one request runs
// the queued party changes (s_info); the add/remove functions queue a change, then create() starts the request
// unless one is running
class SCOM_PARTY_ADD : public ::gf::SCOM, public ::mm::mtl::PtrSingleton< ::gf::SCOM_PARTY_ADD> {
public:
    // a queued party change (the names are not the original's: what the add/remove functions store)
    struct Info {
        unsigned int m_blade;   // the blade (getActBlade2CommonBlade's), 0 for a driver change
        unsigned int m_driver;  // addBlade's second argument, the driver for a driver change
        int m_param;            // addBlade's third argument, addDriver's second; -1 when removing
        bool m_flag;            // removeBlade/removeDriver's bool, true otherwise
        bool m_isDone;
        bool m_isCurrent;       // setCurrentBlade sets it on the blade's queued addBlade
        bool m_isEnable;
        int m_kind;             // 1 addBlade, 2 removeBlade, 3 addDriver, 4 removeDriver, 5 setCurrentBlade
    };

    // 2.0.0's symbols type the handle GF_SCOM_HANDLE*, as SCOM_OBJ_VFADE's constructor
    explicit SCOM_PARTY_ADD(GF_SCOM_HANDLE* handle);
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // exec's path when GfGameManager::isGameTypeIra()
    bool execForIra(fw::UpdateInfo const&);

    static unsigned long create();
    static void addBlade(unsigned int blade, unsigned int driver, int param);
    // the third argument is 3.0.1's: the symbols keep 1.0.0's (unsigned int, bool) spelling
    // (every caller passes true for it; checked only once the game is cleared)
    static void removeBlade(unsigned int blade, bool flag, bool checkClear = true);
    static void removeBlade(unsigned int driver, int slot, bool flag);
    // the same for the menu: never checks a cleared game's exceptions; in a cleared game the driver's blade 1001 or 1002
    // also removes the other one and 1003
    static void removeBladeForMenu(unsigned int driver, int slot, bool flag);
    static void addDriver(unsigned int driver, unsigned int param);
    static void removeDriver(unsigned int driver, bool flag);
    static void setCurrentBlade(unsigned int blade);
    // 2.0.0's symbols name it. What it does: in s_info's ring of 16 0x14-byte requests finds the first of kind 3 with
    // value 4 and sets its byte 0xF; pt setDriverEnable calls it last.
    static void setToraBladeFollow();
    // 2.0.0's symbols name it. What it does: unless a cleared scenario game runs, stores its argument (.bss
    // 0x7100EB6CE8) and creates the request; pt setIraParty passes its script argument.
    static void setIraParty(unsigned int party);

    static mm::mtl::FixedQueue<Info, 16> s_info;
    // 2.0.0's symbols name it. setIraParty stores its argument here before create(); GfReqSmallCom's constructor zeroes
    // it; execForIra (0x7100560390, not yet written) reads it.
    static unsigned int s_iraParty;

    unsigned char pad_28[0x8];
    GfPartyPosInfo m_posInfo;
};
}  // namespace gf

#endif
