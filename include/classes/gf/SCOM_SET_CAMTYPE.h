#ifndef CLASSES_GF_SCOM_SET_CAMTYPE_H
#define CLASSES_GF_SCOM_SET_CAMTYPE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B5D0
class SCOM_SET_CAMTYPE : public ::gf::SCOM {
public:
    explicit SCOM_SET_CAMTYPE(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    int m_cameraType;
};
}  // namespace gf

#endif
