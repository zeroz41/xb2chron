#ifndef CLASSES_GF_SCOM_ADD_MONEY_H
#define CLASSES_GF_SCOM_ADD_MONEY_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AF40
class SCOM_ADD_MONEY : public ::gf::SCOM {
public:
    explicit SCOM_ADD_MONEY(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    int m_money;
};
}  // namespace gf

#endif
