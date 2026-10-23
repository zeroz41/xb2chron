#ifndef CLASSES_GF_SCOM_OBJ_WARP_POS_H
#define CLASSES_GF_SCOM_OBJ_WARP_POS_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B240
class SCOM_OBJ_WARP_POS : public ::gf::SCOM {
public:
    virtual ~SCOM_OBJ_WARP_POS();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
