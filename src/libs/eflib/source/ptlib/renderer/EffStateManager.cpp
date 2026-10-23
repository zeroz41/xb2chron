#define MM_LIB_FROM_EFLIB
#include "grlib/CGLibVtxInstans.h"
#include "ptlib/renderer/RendererStream.h"

namespace ptlib { namespace renderer {

// the one manager: its constructor sets it, its destructor clears it (the symbols leave it unnamed; the name is not
// the original's)
static EffStateManager* s_pInstance;

EffStateManager* EffStateManager::get() {
    return s_pInstance;
}

EffStateManager::EffStateManager() {
    s_pInstance = this;
}

EffStateManager::~EffStateManager() {
    for (int i = 0; i < 7; ++i) {
        m_fetch[i].release();
        m_instanceFetch[i].release();
    }
    m_otherFetch[0].release();
    m_otherFetch[1].release();
    m_vertex.release();
    m_otherVertex.release();
    for (int i = 0; i < 4; ++i) {
        m_index[i].release();
    }
    s_pInstance = nullptr;
}

void EffStateManager::init(StaticAllocObj* pAlloc) {
    initSampler();
    initVtxFetch();
    initVtxIndex();
}

void EffStateManager::begin() {
    m_instans.beginInstansBuff();
}

}}  // namespace ptlib::renderer
