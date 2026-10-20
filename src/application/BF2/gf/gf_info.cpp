#include "classes/gf/GfInfo.h"

namespace gf {

int GfInfo::m_nScreenW;

// initialize, which the constructor and build use, is not written yet

GfInfo::~GfInfo() {}

void GfInfo::destroy() {
    GfInfo* info = get();
    info->finalize();
    delete info;
}

void GfInfo::finalize() {
    m_initialized = false;
}

bool GfInfo::isInitialized() {
    GfInfo* info = get();
    if (info != nullptr) {
        return info->m_initialized;
    }
    return false;
}

int GfScreenW() {
    return GfInfo::m_nScreenW;
}

}  // namespace gf
