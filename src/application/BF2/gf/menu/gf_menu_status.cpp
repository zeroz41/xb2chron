#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuStatus.h"

namespace gf {

GfMenuStatus::GfMenuStatus(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuStatus::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuStatus::~GfMenuStatus() {}

void GfMenuStatus::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuStatus(param);
}

void GfMenuStatus::destroy() {
    GfMenuStatus* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuStatus::finalize() {
    m_initialized = false;
}

bool GfMenuStatus::isInitialized() {
    GfMenuStatus* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuStatus::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
