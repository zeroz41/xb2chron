#include "mm/mtl/Vector.h"
#include "classes/fw/AnimVolumeFadeModifier.h"

namespace fw {

AnimVolumeFadeModifier::~AnimVolumeFadeModifier() {}

}  // namespace fw

// a short vector's resize (its user is not written yet)
template void mm::mtl::Vector<short>::resize(size_t, const short&);
