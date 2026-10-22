#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/FallDamagePlugin.h"

namespace gf { namespace pc {

FallDamagePlugin::FallDamagePlugin()
    : m_property(nullptr), m_maxHeight(0.0f), m_damageDisable(false),
      m_attachObj(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {}

FallDamagePlugin::~FallDamagePlugin() {}

void FallDamagePlugin::cleanup(gf::GfComBehaviorPc&) {}

mm::mtl::RTTI FallDamagePlugin::m_rtti("FallDamagePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
