#ifndef CLASSES_GF_SCOM_ITEM_USE_H
#define CLASSES_GF_SCOM_ITEM_USE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B4E0
class SCOM_ITEM_USE : public ::gf::SCOM {
public:
    explicit SCOM_ITEM_USE(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int, unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_item;
    unsigned int m_count;
};
}  // namespace gf

#endif
