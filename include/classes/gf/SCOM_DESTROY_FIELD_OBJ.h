#ifndef CLASSES_GF_SCOM_DESTROY_FIELD_OBJ_H
#define CLASSES_GF_SCOM_DESTROY_FIELD_OBJ_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B300
class SCOM_DESTROY_FIELD_OBJ : public ::gf::SCOM {
public:
    explicit SCOM_DESTROY_FIELD_OBJ(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create();
};
}  // namespace gf

#endif
