#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuMain.h"

namespace gf {

GfMenuMain::GfMenuMain(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuMain::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuMain::~GfMenuMain() {}

void GfMenuMain::build(const GfSetupParam& param) {
#line 41
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuMain(param);
}

void GfMenuMain::destroy() {
    GfMenuMain* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuMain::finalize() {
    m_initialized = false;
}

bool GfMenuMain::isInitialized() {
    GfMenuMain* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuMain::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
