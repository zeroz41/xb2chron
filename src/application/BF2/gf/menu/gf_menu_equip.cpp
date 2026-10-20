#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuEquip.h"

namespace gf {

GfMenuEquip::GfMenuEquip(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuEquip::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuEquip::~GfMenuEquip() {}

void GfMenuEquip::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuEquip(param);
}

void GfMenuEquip::destroy() {
    GfMenuEquip* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuEquip::finalize() {
    m_initialized = false;
}

bool GfMenuEquip::isInitialized() {
    GfMenuEquip* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuEquip::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
