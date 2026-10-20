#ifndef CLASSES_GF_SCOM_DESTROY_GMK_SET_H
#define CLASSES_GF_SCOM_DESTROY_GMK_SET_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B450
class SCOM_DESTROY_GMK_SET : public ::gf::SCOM {
public:
    virtual ~SCOM_DESTROY_GMK_SET();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
