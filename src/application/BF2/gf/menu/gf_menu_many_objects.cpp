#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuManyObjects.h"
#include <string.h>

namespace gf {

GfMenuManyObjects::GfMenuManyObjects(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuManyObjects::initialize(const GfSetupParam& param) {
    m_initialized = true;
    memset(m_queues, 0, sizeof(m_queues));
}

GfMenuManyObjects::~GfMenuManyObjects() {}

void GfMenuManyObjects::build(const GfSetupParam& param) {
#line 32
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuManyObjects(param);
}

void GfMenuManyObjects::destroy() {
    GfMenuManyObjects* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuManyObjects::finalize() {
    m_initialized = false;
}

bool GfMenuManyObjects::isInitialized() {
    GfMenuManyObjects* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuManyObjects::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
