#ifndef CLASSES_GF_SCOM_ACHIEV_INC_H
#define CLASSES_GF_SCOM_ACHIEV_INC_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AA60
class SCOM_ACHIEV_INC : public ::gf::SCOM {
public:
    virtual ~SCOM_ACHIEV_INC();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
