#ifndef CLASSES_GF_GFFIELDLOCALSTEER_TISTARGETNOTSAMESQUAD_H
#define CLASSES_GF_GFFIELDLOCALSTEER_TISTARGETNOTSAMESQUAD_H

#include "classes/gf/GfFieldLocalSteer.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a template: 2 instances in the module. GfComBehaviorMob's constructor installs its table at 0x5320, right after
// its steering; the operator's body is defined in the unit of each owner
template <typename T>
class GfFieldLocalSteer::TIsTargetNotSameSquad {
public:
    // whether the target the steering considers is not of the steering object's squad
    virtual bool operator()(const gf::GfFieldLocalSteer& steer, gf::GF_OBJ_HANDLE* target) const;  // slot 0
};
}  // namespace gf

#endif
