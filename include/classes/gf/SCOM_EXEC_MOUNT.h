#ifndef CLASSES_GF_SCOM_EXEC_MOUNT_H
#define CLASSES_GF_SCOM_EXEC_MOUNT_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { enum OPTMNT : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B420
class SCOM_EXEC_MOUNT : public ::gf::SCOM {
public:
    explicit SCOM_EXEC_MOUNT(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(GF_OBJ_HANDLE* obj, OPTMNT mount);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned char pad_1c[0x4];
    GF_OBJ_HANDLE* m_value;
    OPTMNT m_value2;
};
}  // namespace gf

#endif
