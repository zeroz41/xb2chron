#ifndef CLASSES_GF_SCOM_OBJ_ALPHA_H
#define CLASSES_GF_SCOM_OBJ_ALPHA_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A950
class SCOM_OBJ_ALPHA : public ::gf::SCOM {
public:
    virtual ~SCOM_OBJ_ALPHA();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
