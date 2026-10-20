// not proven yet: does not compile: redefinition of 'TIsTargetNotSameSquad' as different kind of symbol
#ifndef CLASSES_GF_GFFIELDLOCALSTEER_TISTARGETNOTSAMESQUAD_H
#define CLASSES_GF_GFFIELDLOCALSTEER_TISTARGETNOTSAMESQUAD_H

#include "classes/gf/GfFieldLocalSteer.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFieldLocalSteer; }

namespace gf {
// a template: 2 instances in the module
template <typename T0>
class GfFieldLocalSteer::TIsTargetNotSameSquad {
public:
    virtual void operator()(gf::GfFieldLocalSteer const&, gf::GF_OBJ_HANDLE*) const;  // slot 0
};
}  // namespace gf

#endif
