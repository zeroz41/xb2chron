#include "classes/gf/Plugin.h"

namespace gf {

Plugin::Plugin() : m_active(false) {}

Plugin::~Plugin() {}

void Plugin::setActivate(bool active) {
    if (m_active == active) {
        return;
    }
    m_active = active;
    if (active) {
        onActivate();
    } else {
        onDeactivate();
    }
}

mm::mtl::RTTI Plugin::m_rtti("Plugin", nullptr, nullptr);

}  // namespace gf
