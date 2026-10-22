#include "classes/gf/ScriptCameraEntity.h"
#include "classes/fw/Camera.h"

namespace gf {

ScriptCameraEntity::~ScriptCameraEntity() {}

void ScriptCameraEntity::onActivate() {}

mm::mtl::RTTI ScriptCameraEntity::m_rtti("ScriptCameraEntity", &fw::Camera::m_rtti, nullptr);

}  // namespace gf
