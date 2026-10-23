#ifndef CLASSES_GF_SCOM_CREATE_PARTY_OBJ_H
#define CLASSES_GF_SCOM_CREATE_PARTY_OBJ_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B2A0
class SCOM_CREATE_PARTY_OBJ : public ::gf::SCOM {
public:
    virtual ~SCOM_CREATE_PARTY_OBJ();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
