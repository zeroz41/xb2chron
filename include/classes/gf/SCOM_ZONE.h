#ifndef CLASSES_GF_SCOM_ZONE_H
#define CLASSES_GF_SCOM_ZONE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B6C0
class SCOM_ZONE : public ::gf::SCOM {
public:
    virtual ~SCOM_ZONE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
