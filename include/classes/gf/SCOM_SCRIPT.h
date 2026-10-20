#ifndef CLASSES_GF_SCOM_SCRIPT_H
#define CLASSES_GF_SCOM_SCRIPT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B3C0
class SCOM_SCRIPT : public ::gf::SCOM {
public:
    virtual ~SCOM_SCRIPT();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
