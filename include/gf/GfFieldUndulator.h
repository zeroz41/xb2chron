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
        BdatInfo() : pad_0(false), pad_1(false), pad_4(0.0f), pad_8(0.0f), pad_c(0.0f), pad_10(0.0f), pad_14(0) {}
        void create(int unduration);
        bool pad_0;  // update runs while pad_0 or pad_1
        bool pad_1;
        float pad_4;
        float pad_8;
        float pad_c;
        float pad_10;
        int pad_14;
    };

    explicit GfFieldUndulator(const CreateInfo* info);
    // inline: GfComBehaviorEnemy's destructor disposes it, then clears the row's two update flags, in place
    ~GfFieldUndulator() {
        dispose();
        m_bdat.pad_0 = false;
        m_bdat.pad_1 = false;
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
