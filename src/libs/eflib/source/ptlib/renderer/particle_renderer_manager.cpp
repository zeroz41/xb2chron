#include "ptlib/renderer/RendererManager.h"
#include "ptlib/renderer/RendererObj.h"
#include "ptlib/renderer/RendererStream.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/StackAllocater.h"
#include "mm/MMStdBase.h"
#include <new>

#line 1 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/renderer/particle_renderer_manager.cpp"

namespace ptlib { namespace renderer {

static RenderManager* s_pIns;

RenderManager* RenderManager::get() {
#line 17
    MM_ASSERT(getPtr());
    return getPtr();
}

RenderManager*& RenderManager::getPtr() {
    return s_pIns;
}

void RenderManager::init(const DrDrawWorkInfoEF* pDrInfo, FxParam* pFxParam) {
#line 35
    MM_ASSERT(!getPtr());
#line 37
    StaticAllocObj* pAlloc = StaticAllocObj::create(0x19000, __FILE__, __LINE__);
    getPtr() = static_cast<RenderManager*>(pAlloc->sysAlloc(sizeof(RenderManager), 16, nullptr, 0));
    if (getPtr() == nullptr) {
        efAstMsg("0", "initialize error");
        return;
    }
    getPtr()->m_pAlloc = nullptr;
    getPtr()->m_pFxParam = pFxParam;
    getPtr()->m_pGrObj = static_cast<RenderGrObj*>(pAlloc->sysAlloc(sizeof(RenderGrObj), 16, nullptr, 0));
    new (getPtr()->m_pGrObj) RenderGrObj();
    getPtr()->setDrInfo(pDrInfo);
    getPtr()->m_pGrObj->init(pAlloc);
    getPtr()->m_pAlloc = pAlloc;
    getPtr()->m_pEffState = static_cast<EffStateManager*>(pAlloc->sysAlloc(sizeof(EffStateManager), 16, nullptr, 0));
    new (getPtr()->m_pEffState) EffStateManager();
    getPtr()->m_pEffState->init(pAlloc);
}

void RenderManager::setDrInfo(const DrDrawWorkInfoEF* pDrInfo) {
    if (m_pGrObj != nullptr) {
        m_pGrObj->m_pDrInfo = pDrInfo;
    }
}

void RenderManager::term() {
    if (getPtr() == nullptr) {
        efAstMsg("0", "initialize error");
        return;
    }
    getPtr()->m_pGrObj->term();
    getPtr()->m_pGrObj->~RenderGrObj();
    getPtr()->m_pEffState->~EffStateManager();
    getPtr()->m_pFxParam = nullptr;
    StaticAllocObj::destroy(getPtr()->m_pAlloc);
    getPtr() = nullptr;
}

}}  // namespace ptlib::renderer
