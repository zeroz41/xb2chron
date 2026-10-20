#ifndef CLASSES_GF_SCOM_SET_CAMTYPE_H
#define CLASSES_GF_SCOM_SET_CAMTYPE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B5D0
class SCOM_SET_CAMTYPE : public ::gf::SCOM {
public:
    virtual ~SCOM_SET_CAMTYPE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
