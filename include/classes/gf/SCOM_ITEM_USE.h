#ifndef CLASSES_GF_SCOM_ITEM_USE_H
#define CLASSES_GF_SCOM_ITEM_USE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B4E0
class SCOM_ITEM_USE : public ::gf::SCOM {
public:
    virtual ~SCOM_ITEM_USE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
