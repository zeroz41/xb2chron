#ifndef CLASSES_GF_SCOM_SET_FLAG_H
#define CLASSES_GF_SCOM_SET_FLAG_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B5A0
class SCOM_SET_FLAG : public ::gf::SCOM {
public:
    explicit SCOM_SET_FLAG(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int, unsigned int, unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    unsigned int m_value2;
    unsigned int m_value3;
};
}  // namespace gf

#endif
