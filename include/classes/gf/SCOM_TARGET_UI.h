#ifndef CLASSES_GF_SCOM_TARGET_UI_H
#define CLASSES_GF_SCOM_TARGET_UI_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B570
class SCOM_TARGET_UI : public ::gf::SCOM {
public:
    explicit SCOM_TARGET_UI(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(GF_OBJ_HANDLE*);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned char pad_1c[0x4];
    GF_OBJ_HANDLE* m_target;
};
}  // namespace gf

#endif
