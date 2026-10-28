#ifndef CLASSES_GF_SCOM_OBJ_VFADE_OFF_H
#define CLASSES_GF_SCOM_OBJ_VFADE_OFF_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A980
class SCOM_OBJ_VFADE_OFF : public ::gf::SCOM {
public:
    explicit SCOM_OBJ_VFADE_OFF(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned char pad_1c[0x4];
    GF_OBJ_HANDLE* m_value;
};
}  // namespace gf

#endif
