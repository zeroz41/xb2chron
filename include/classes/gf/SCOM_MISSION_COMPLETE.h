#ifndef CLASSES_GF_SCOM_MISSION_COMPLETE_H
#define CLASSES_GF_SCOM_MISSION_COMPLETE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B1B0
class SCOM_MISSION_COMPLETE : public ::gf::SCOM {
public:
    virtual ~SCOM_MISSION_COMPLETE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
