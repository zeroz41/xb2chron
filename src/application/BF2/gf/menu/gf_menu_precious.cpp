#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuPrecious.h"

namespace gf {

GfMenuPrecious::GfMenuPrecious(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuPrecious::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuPrecious::~GfMenuPrecious() {}

void GfMenuPrecious::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuPrecious(param);
}

void GfMenuPrecious::destroy() {
    GfMenuPrecious* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuPrecious::finalize() {
    m_initialized = false;
}

bool GfMenuPrecious::isInitialized() {
    GfMenuPrecious* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuPrecious::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
