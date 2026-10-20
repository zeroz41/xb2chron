#ifndef CLASSES_GF_SCOM_SOLO_REX_H
#define CLASSES_GF_SCOM_SOLO_REX_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6ACF8
class SCOM_SOLO_REX : public ::gf::SCOM {
public:
    virtual ~SCOM_SOLO_REX();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
