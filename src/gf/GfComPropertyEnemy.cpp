#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComPropertyEnemy.h"

namespace gf {

GfComPropertyEnemy::~GfComPropertyEnemy() {}

mm::mtl::RTTI GfComPropertyEnemy::m_rtti("GfComPropertyEnemy", &GfComProperty::m_rtti, nullptr);

}  // namespace gf
