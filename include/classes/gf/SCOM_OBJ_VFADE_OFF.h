#ifndef CLASSES_GF_SCOM_OBJ_VFADE_OFF_H
#define CLASSES_GF_SCOM_OBJ_VFADE_OFF_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A980
class SCOM_OBJ_VFADE_OFF : public ::gf::SCOM {
public:
    virtual ~SCOM_OBJ_VFADE_OFF();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
