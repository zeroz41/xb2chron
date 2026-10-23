#ifndef CLASSES_GF_SCOM_FIELD_SKILL_H
#define CLASSES_GF_SCOM_FIELD_SKILL_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AA90
class SCOM_FIELD_SKILL : public ::gf::SCOM {
public:
    explicit SCOM_FIELD_SKILL(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int);
    static unsigned long createWithBlade(unsigned int, unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    int m_value2;
};
}  // namespace gf

#endif
