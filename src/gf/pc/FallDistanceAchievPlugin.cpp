#include "classes/gf/pc/FallDistanceAchievPlugin.h"

namespace gf { namespace pc {

FallDistanceAchievPlugin::FallDistanceAchievPlugin() : m_property(nullptr), m_maxHeight(0.0f) {}

FallDistanceAchievPlugin::~FallDistanceAchievPlugin() {}

void FallDistanceAchievPlugin::cleanup(gf::GfComBehaviorPc&) {}

mm::mtl::RTTI FallDistanceAchievPlugin::m_rtti("FallDistanceAchievPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
