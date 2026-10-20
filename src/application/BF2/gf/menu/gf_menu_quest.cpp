#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuQuest.h"

namespace gf {

GfMenuQuest::GfMenuQuest(const GfSetupParam& param) : m_openValue(0), m_openId(-1) {
    initialize(param);
}

void GfMenuQuest::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuQuest::~GfMenuQuest() {}

void GfMenuQuest::build(const GfSetupParam& param) {
#line 47
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuQuest(param);
}

void GfMenuQuest::destroy() {
    GfMenuQuest* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuQuest::finalize() {
    m_initialized = false;
}

bool GfMenuQuest::isInitialized() {
    GfMenuQuest* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuQuest::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
