#define MM_LIB_FROM_EFLIB
#include "grlib/CGLibVtxVertex.h"
#include "classes/effect/SystemManager.h"
#include "grlib/CGLibVtxInstans.h"
#include "ptlib/renderer/RendererStream.h"
#include "mm/MMStdBase.h"

namespace ptlib { namespace renderer {

void StreamObj::init(STREAM_SIZE_TYPE size, unsigned int count, FxVertexType type) {
    m_initialized = true;
    m_size = size;
    m_type = type;
    m_offset = 0;
    // (tested in reverse: the original tests 1 first)
    if (type == 0) {
        m_pVertex = &EffStateManager::get()->m_vertex;
        m_indexType = 0;
    } else if (type == 1) {
        m_vertex.createVertexBuff(38400, 0x60);
        m_indexType = 2;
        m_pVertex = &m_vertex;
    }
    initFetchVertex();
}

void StreamObj::release() {
    m_vertex.delayRelease();
    m_pVertex = nullptr;
}

void StreamObj::releaseSub() {
    m_vertex.delayRelease();
    m_pVertex = nullptr;
}

void StreamObj::initFetchVertex() {
    if (m_type == 1) {
        m_pInstanceFetch = &EffStateManager::get()->m_fetch[1];
        m_pFetch = &EffStateManager::get()->m_fetch[1];
        return;
    }
    switch (m_size) {
    case 20:
        m_pInstanceFetch = &EffStateManager::get()->m_instanceFetch[1];
        m_pFetch = &EffStateManager::get()->m_fetch[1];
        break;
    case 24:
        m_pInstanceFetch = &EffStateManager::get()->m_instanceFetch[2];
        m_pFetch = &EffStateManager::get()->m_fetch[2];
        break;
    case 28:
        m_pInstanceFetch = &EffStateManager::get()->m_instanceFetch[3];
        m_pFetch = &EffStateManager::get()->m_fetch[3];
        break;
    case 32:
        m_pInstanceFetch = &EffStateManager::get()->m_instanceFetch[4];
        m_pFetch = &EffStateManager::get()->m_fetch[4];
        break;
    case 36:
        m_pInstanceFetch = &EffStateManager::get()->m_instanceFetch[5];
        m_pFetch = &EffStateManager::get()->m_fetch[5];
        break;
    case 40:
        m_pInstanceFetch = &EffStateManager::get()->m_instanceFetch[6];
        m_pFetch = &EffStateManager::get()->m_fetch[6];
        break;
    default:
#line 172
        MM_ASSERT(0);
        break;
    }
}

void* StreamObj::lockStream(const DrDrawWorkInfoEF* pDrInfo) {
    if (m_type == 1) {
        unsigned int size;
        void* pBuffer;
        m_pVertex->lock(&pBuffer, &size);
        char* pStream = static_cast<char*>(pBuffer);
        return effect::SystemManager::getPtr()->m_secondBuffer ? pStream + 19200 : pStream;
    }
    m_offset = EffStateManager::get()->m_instans.m_offset;
    return EffStateManager::get()->m_instans.getNextInstansBuff();
}

void StreamObj::unlockStream(const DrDrawWorkInfoEF* pDrInfo, unsigned int count) {
    if (m_type == 1) {
        if (effect::SystemManager::getPtr()->m_secondBuffer) {
            m_pVertex->unlock(19200, 19200);
        } else {
            m_pVertex->unlock(0, 19200);
        }
        return;
    }
    m_offset = EffStateManager::get()->m_instans.m_offset;
    grlib::CGLibVtxInstans& instans = EffStateManager::get()->m_instans;
    instans.m_offset += count * m_size * 4;
    EffStateManager::get()->m_instans.updateInstansBuff();
}

// renderStreamNum (0x7100860AB8) is not here yet

}}  // namespace ptlib::renderer
