#ifndef CLASSES_GF_SCOM_ADD_DEVELOP_H
#define CLASSES_GF_SCOM_ADD_DEVELOP_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B0F0
class SCOM_ADD_DEVELOP : public ::gf::SCOM {
public:
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    unsigned int m_value2;
    unsigned char pad_24[0x4];
};
}  // namespace gf

#endif
