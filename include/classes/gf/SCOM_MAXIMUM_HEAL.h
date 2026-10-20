#ifndef CLASSES_GF_SCOM_MAXIMUM_HEAL_H
#define CLASSES_GF_SCOM_MAXIMUM_HEAL_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B000
class SCOM_MAXIMUM_HEAL : public ::gf::SCOM {
public:
    virtual ~SCOM_MAXIMUM_HEAL();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
