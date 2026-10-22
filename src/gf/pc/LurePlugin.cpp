#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/LurePlugin.h"

namespace gf { namespace pc {

void LurePlugin::cleanup(gf::GfComBehaviorPc&) {}

void LurePlugin::onActivate() {}

void LurePlugin::onDeactivate() {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

mm::mtl::RTTI LurePlugin::m_rtti("LurePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
