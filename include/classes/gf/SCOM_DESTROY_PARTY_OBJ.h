#ifndef CLASSES_GF_SCOM_DESTROY_PARTY_OBJ_H
#define CLASSES_GF_SCOM_DESTROY_PARTY_OBJ_H

#include "classes/gf/SCOM.h"
#include "gf/GfReqParam.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B6B2D0
class SCOM_DESTROY_PARTY_OBJ : public ::gf::SCOM {
public:
    // slot 0: implicit (its D2 and D0 sit in gf_req_scom's tail with the other inline slots; exec is the key function)
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the names below are not the original's: exec destroys m_party once (GfGameUnit::destroyParty, which fills
    // m_handles), then waits until no handle in m_handles has an object left
    bool m_isDestroyed;
    unsigned char pad_1D[0x3];
    RQ_SETUP_PARTY m_party;
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 32> m_handles;
};
}  // namespace gf

#endif
