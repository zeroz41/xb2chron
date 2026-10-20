#ifndef CLASSES_GF_SCOM_CURRENT_BLADE_H
#define CLASSES_GF_SCOM_CURRENT_BLADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AC28
class SCOM_CURRENT_BLADE : public ::gf::SCOM {
public:
    virtual ~SCOM_CURRENT_BLADE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
