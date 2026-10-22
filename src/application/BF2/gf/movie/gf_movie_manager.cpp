#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComAnimation.h"

namespace gf {

GfComAnimation::~GfComAnimation() {}

mm::mtl::RTTI GfComAnimation::m_rtti("GfComAnimation", &GfComponent::m_rtti, nullptr);

}  // namespace gf
