#ifndef CLASSES_GF_SCOM_PARTY_ADD_H
#define CLASSES_GF_SCOM_PARTY_ADD_H

#include "classes/gf/SCOM.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedQueue.h"

namespace fw { class UpdateInfo; }

namespace gf {
// what GfGameParty::getPartyPosition fills: one record per party slot (0x20 bytes each; the member names are
// not the original's: the constructor sets the position to mm::Vec3::zero and the rest to zero)
struct GfPartyPosInfo {
    struct Pos {
        Pos() : m_pos(mm::Vec3::zero), m_value(0), m_isValid(false) {}
        mm::Vec3 m_pos;
        int m_value;
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

    explicit SCOM_PARTY_ADD(unsigned long handle = GfReqSmallCom::sys()->newHandle());
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    static unsigned long create();
    static void addBlade(unsigned int blade, unsigned int driver, int param);
    // the third argument is 3.0.1's: the symbols keep 1.0.0's (unsigned int, bool) spelling
    // (every caller passes true for it; checked only once the game is cleared)
    static void removeBlade(unsigned int blade, bool flag, bool checkClear = true);
    static void removeBlade(unsigned int driver, int slot, bool flag);
    static void addDriver(unsigned int driver, unsigned int param);
    static void removeDriver(unsigned int driver, bool flag);
    static void setCurrentBlade(unsigned int blade);

    static mm::mtl::FixedQueue<Info, 16> s_info;

    unsigned char pad_28[0x8];
    GfPartyPosInfo m_posInfo;
};
}  // namespace gf

#endif
