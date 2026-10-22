#include "classes/gf/ChainAttackCameraEntity.h"
#include "classes/fw/Camera.h"

namespace gf {

ChainAttackCameraEntity::~ChainAttackCameraEntity() {}

void ChainAttackCameraEntity::onActivate() {}

mm::mtl::RTTI ChainAttackCameraEntity::m_rtti("ChainAttackCameraEntity", &fw::Camera::m_rtti, nullptr);

}  // namespace gf
