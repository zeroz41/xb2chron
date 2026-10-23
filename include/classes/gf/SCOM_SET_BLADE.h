#ifndef CLASSES_GF_SCOM_SET_BLADE_H
#define CLASSES_GF_SCOM_SET_BLADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B600
class SCOM_SET_BLADE : public ::gf::SCOM {
public:
    virtual ~SCOM_SET_BLADE();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
