#ifndef FW_IKRESOLVER_H
#define FW_IKRESOLVER_H

#include "mm/mtl/IntrusiveList.h"

namespace fw {

// what AnimationManager resolves IK through on a layer (addIkResolver links it into the layer's list, removeIkResolver
// unlinks it): no table, a list node (gf::GfComIK is one, at 0x10)
class IkResolver : public mm::mtl::IntrusiveListNodeBase {};

}  // namespace fw

#endif
