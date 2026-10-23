#ifndef CLASSES_GF_SCOM_ADD_TRUST_H
#define CLASSES_GF_SCOM_ADD_TRUST_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B1E0
class SCOM_ADD_TRUST : public ::gf::SCOM {
public:
    explicit SCOM_ADD_TRUST(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int, unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    unsigned int m_value2;
};
}  // namespace gf

#endif
