#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/gf/GfGameSearchObj.h"

namespace gf { namespace pc {

FallIntoColiPlugin::~FallIntoColiPlugin() {}

void FallIntoColiPlugin::cleanup(gf::GfComBehaviorPc&) {
    if (m_searchObj != reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1)) {
        gf::GfGameSearchObj::destroyObj(m_searchObj);
        m_searchObj = reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1);
    }
}

void FallIntoColiPlugin::onDeactivate() {
    gf::GfGameSearchObj::setEnable(m_searchObj, false);
}

mm::mtl::RTTI FallIntoColiPlugin::m_rtti("FallIntoColiPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
