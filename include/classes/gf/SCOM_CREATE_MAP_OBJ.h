#ifndef CLASSES_GF_SCOM_CREATE_MAP_OBJ_H
#define CLASSES_GF_SCOM_CREATE_MAP_OBJ_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B360
class SCOM_CREATE_MAP_OBJ : public ::gf::SCOM {
public:
    explicit SCOM_CREATE_MAP_OBJ(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int, unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    unsigned int m_value2;
};
}  // namespace gf

#endif
