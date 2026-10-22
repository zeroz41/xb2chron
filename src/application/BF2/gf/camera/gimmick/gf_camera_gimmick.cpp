#include "gf/FileStaticVec3.h"
#include "classes/gf/GimmickCamera.h"

namespace gf {

void GimmickCamera::onActivate() {}

mm::mtl::RTTI GimmickCamera::m_rtti("GimmickCamera", &::fw::Camera::m_rtti, nullptr);

}  // namespace gf
