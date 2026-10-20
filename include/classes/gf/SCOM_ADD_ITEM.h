#ifndef CLASSES_GF_SCOM_ADD_ITEM_H
#define CLASSES_GF_SCOM_ADD_ITEM_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B210
class SCOM_ADD_ITEM : public ::gf::SCOM {
public:
    virtual ~SCOM_ADD_ITEM();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
