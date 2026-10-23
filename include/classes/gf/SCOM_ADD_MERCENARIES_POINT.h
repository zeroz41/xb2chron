#ifndef CLASSES_GF_SCOM_ADD_MERCENARIES_POINT_H
#define CLASSES_GF_SCOM_ADD_MERCENARIES_POINT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B150
class SCOM_ADD_MERCENARIES_POINT : public ::gf::SCOM {
public:
    explicit SCOM_ADD_MERCENARIES_POINT(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_point;
};
}  // namespace gf

#endif
