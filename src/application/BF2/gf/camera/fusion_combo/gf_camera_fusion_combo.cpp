#include "classes/gf/FusionComboCamera.h"
#include "classes/fw/Camera.h"

namespace gf {

FusionComboCamera::~FusionComboCamera() {}

void FusionComboCamera::onActivate() {}

mm::mtl::RTTI FusionComboCamera::m_rtti("FusionComboCamera", &fw::Camera::m_rtti, nullptr);

}  // namespace gf
