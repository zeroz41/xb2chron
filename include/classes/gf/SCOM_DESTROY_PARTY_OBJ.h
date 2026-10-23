#ifndef CLASSES_GF_SCOM_DESTROY_PARTY_OBJ_H
#define CLASSES_GF_SCOM_DESTROY_PARTY_OBJ_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B2D0
class SCOM_DESTROY_PARTY_OBJ : public ::gf::SCOM {
public:
    virtual ~SCOM_DESTROY_PARTY_OBJ();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
