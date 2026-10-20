#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuShop.h"

namespace gf {

GfMenuShop::GfMenuShop(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuShop::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuShop::~GfMenuShop() {}

void GfMenuShop::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuShop(param);
}

void GfMenuShop::destroy() {
    GfMenuShop* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuShop::finalize() {
    m_initialized = false;
}

bool GfMenuShop::isInitialized() {
    GfMenuShop* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuShop::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
