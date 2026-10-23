#ifndef CLASSES_GF_SCOM_SET_MERCENARIES_LEVEL_H
#define CLASSES_GF_SCOM_SET_MERCENARIES_LEVEL_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B180
class SCOM_SET_MERCENARIES_LEVEL : public ::gf::SCOM {
public:
    explicit SCOM_SET_MERCENARIES_LEVEL(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_level;
};
}  // namespace gf

#endif
