#include "classes/gf/MenuForceCalculator.h"
#include "classes/fw/ForceCalculator.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/mm/mtl/IAllocator.h"

namespace gf {

mm::mtl::IntrusivePtr<MenuForceCalculator> MenuForceCalculator::create() {
#line 30
    return new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MenuForceCalculator();
}

MenuForceCalculator::~MenuForceCalculator() {}

mm::mtl::RTTI MenuForceCalculator::m_rtti("MenuForceCalculator", &fw::ForceCalculator::m_rtti, nullptr);

}  // namespace gf
