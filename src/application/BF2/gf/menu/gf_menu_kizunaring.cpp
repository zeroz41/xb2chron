#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuKizunaring.h"

namespace gf {

GfMenuKizunaring::GfMenuKizunaring(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuKizunaring::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuKizunaring::~GfMenuKizunaring() {}

void GfMenuKizunaring::build(const GfSetupParam& param) {
#line 41
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuKizunaring(param);
}

void GfMenuKizunaring::destroy() {
    GfMenuKizunaring* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuKizunaring::finalize() {
    m_initialized = false;
}

bool GfMenuKizunaring::isInitialized() {
    GfMenuKizunaring* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuKizunaring::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
