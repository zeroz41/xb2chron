#ifndef CLASSES_GF_SCOM_NIA_BLADE_H
#define CLASSES_GF_SCOM_NIA_BLADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B630
class SCOM_NIA_BLADE : public ::gf::SCOM {
public:
    virtual ~SCOM_NIA_BLADE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
