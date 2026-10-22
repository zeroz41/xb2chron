#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/AccessPlugin.h"

namespace gf { namespace pc {

void AccessPlugin::onActivate() {}

mm::mtl::RTTI AccessPlugin::m_rtti("AccessPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
