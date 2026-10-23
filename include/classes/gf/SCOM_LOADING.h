#ifndef CLASSES_GF_SCOM_LOADING_H
#define CLASSES_GF_SCOM_LOADING_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B390
class SCOM_LOADING : public ::gf::SCOM {
public:
    explicit SCOM_LOADING(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int, bool);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    bool m_value2;
};
}  // namespace gf

#endif
