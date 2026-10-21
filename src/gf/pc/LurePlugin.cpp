#include "classes/gf/pc/LurePlugin.h"

namespace gf { namespace pc {

void LurePlugin::cleanup(gf::GfComBehaviorPc&) {}

void LurePlugin::onActivate() {}

void LurePlugin::onDeactivate() {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

}}  // namespace gf::pc
