#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuMinimap.h"

namespace gf {

GfMenuMinimap::GfMenuMinimap(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuMinimap::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuMinimap::~GfMenuMinimap() {}

void GfMenuMinimap::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuMinimap(param);
}

void GfMenuMinimap::destroy() {
    GfMenuMinimap* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuMinimap::finalize() {
    m_initialized = false;
}

bool GfMenuMinimap::isInitialized() {
    GfMenuMinimap* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuMinimap::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
