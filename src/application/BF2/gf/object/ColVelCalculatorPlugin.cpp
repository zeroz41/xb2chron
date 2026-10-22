#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/ColVelCalculatorPlugin.h"

namespace gf { namespace pc {

ColVelCalculatorPlugin::ColVelCalculatorPlugin() : m_onGround(true) {}

void ColVelCalculatorPlugin::onActivate() {
    m_onGround = true;
}

mm::mtl::RTTI ColVelCalculatorPlugin::m_rtti("ColVelCalculatorPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
