#ifndef GF_GFFIELDUNDULATOR_H
#define GF_GFFIELDUNDULATOR_H

#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ReferenceFrame; }

namespace gf {
// no table: follows the ground's undulation under an object (rays cast against the ground, applied to its
// reference frame), set up from the BDAT row its id leads to (ParamID -> ResourceID -> Unduration); the field
// names are not the original's
class GfFieldUndulator {
public:
    struct CreateInfo {
        unsigned int m_id;  // the row create looks ParamID up with
        unsigned char pad_4[0x4];
    };
    // what the BDAT row sets up (BdatInfo::create takes its Unduration)
    struct BdatInfo {
        // the row's Flag bits UndX and UndZ: update copies the pair by value (one halfword load, each byte tested
        // whole); the type and field names are not the original's
        struct Flag {
            unsigned char m_x;
            unsigned char m_z;
        };
        BdatInfo() : pad_4(0.0f), pad_8(0.0f), pad_c(0.0f), pad_10(0.0f), pad_14(0.0f) {
            m_flag.m_x = false;
            m_flag.m_z = false;
        }
        void create(int unduration);
        // inline: the name is not the original's
        Flag getFlag() const { return m_flag; }
        Flag m_flag;  // update runs while either is set
        float pad_4;   // UndMinX, as radians
        float pad_8;   // UndMaxX
        float pad_c;   // UndMinZ
        float pad_10;  // UndMaxZ
        float pad_14;  // UndDeg, in tenths of a degree, as radians
    };

    explicit GfFieldUndulator(const CreateInfo* info);
    // inline: GfComBehaviorEnemy's destructor disposes it, then clears the row's two update flags, in place
    ~GfFieldUndulator() {
        dispose();
        m_bdat.m_flag.m_x = false;
        m_bdat.m_flag.m_z = false;
    }
    void create(const CreateInfo& info);
    void dispose();
    void castRay(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, bool flag);
    void update(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, bool skipRay);
    void apply(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);

    CreateInfo m_info;
    BdatInfo m_bdat;
    mm::Vec3 pad_20;  // unitY at first
    mm::Vec3 pad_30;  // unitY at first
};
}  // namespace gf

#endif
