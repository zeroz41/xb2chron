#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuBladeCreateCamera.h"

namespace gf {

GfMenuBladeCreateCamera::~GfMenuBladeCreateCamera() {}

mm::mtl::RTTI GfMenuBladeCreateCamera::m_rtti("GfMenuBladeCreateCamera", &::fw::Camera::m_rtti, nullptr);

}  // namespace gf
