#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameFlag.h"

namespace gf {

GfGameFlag::GfGameFlag(const GfSetupParam& param) {
    initialize(param);
}

void GfGameFlag::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfGameFlag::~GfGameFlag() {}

void GfGameFlag::build(const GfSetupParam& param) {
#line 58
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameFlag(param);
}

void GfGameFlag::destroy() {
    GfGameFlag* flag = get();
    flag->finalize();
    delete flag;
}

void GfGameFlag::finalize() {
    m_initialized = false;
}

bool GfGameFlag::isInitialized() {
    GfGameFlag* flag = get();
    if (flag != nullptr) {
        return flag->m_initialized;
    }
    return false;
}

}  // namespace gf
