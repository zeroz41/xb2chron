#ifndef CLASSES_GF_SCOM_SOLO_REX_H
#define CLASSES_GF_SCOM_SOLO_REX_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ACF8
class SCOM_SOLO_REX : public ::gf::SCOM {
public:
    explicit SCOM_SOLO_REX(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(bool);

    // the names are not the original's: what the create functions store (their arguments, in order)
    bool m_value;
};
}  // namespace gf

#endif
