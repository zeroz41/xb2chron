#include "classes/gf/EyeBlinkPlugin.h"
#include "classes/gf/Plugin.h"

namespace gf {

void EyeBlinkPlugin::cleanup(gf::GfComBehavior&) {}

mm::mtl::RTTI EyeBlinkPlugin::m_rtti("EyeBlinkPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
