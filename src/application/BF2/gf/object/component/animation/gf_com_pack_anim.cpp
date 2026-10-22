#include "classes/gf/GfComPackAnim.h"
#include "classes/gf/GfComAnimation.h"

namespace gf {

void GfComPackAnim::changeLayer(unsigned int, unsigned int) {}

mm::mtl::RTTI GfComPackAnim::m_rtti("GfComPackAnim", &GfComAnimation::m_rtti, nullptr);

}  // namespace gf
