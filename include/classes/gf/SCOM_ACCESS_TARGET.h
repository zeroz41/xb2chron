#ifndef CLASSES_GF_SCOM_ACCESS_TARGET_H
#define CLASSES_GF_SCOM_ACCESS_TARGET_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B540
class SCOM_ACCESS_TARGET : public ::gf::SCOM {
public:
    explicit SCOM_ACCESS_TARGET(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues one: the PC's access target becomes handle's (-1: none)
    static unsigned long create(GF_OBJ_HANDLE* handle);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned char pad_1c[0x4];
    GF_OBJ_HANDLE* m_target;
};
}  // namespace gf

#endif
