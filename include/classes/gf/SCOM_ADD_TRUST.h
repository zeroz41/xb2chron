#ifndef CLASSES_GF_SCOM_ADD_TRUST_H
#define CLASSES_GF_SCOM_ADD_TRUST_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B1E0
class SCOM_ADD_TRUST : public ::gf::SCOM {
public:
    virtual ~SCOM_ADD_TRUST();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
