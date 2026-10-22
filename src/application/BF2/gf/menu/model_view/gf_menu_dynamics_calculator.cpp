#include "classes/gf/MenuForceCalculator.h"
#include "classes/fw/ForceCalculator.h"

namespace gf {

MenuForceCalculator::~MenuForceCalculator() {}

mm::mtl::RTTI MenuForceCalculator::m_rtti("MenuForceCalculator", &fw::ForceCalculator::m_rtti, nullptr);

}  // namespace gf
