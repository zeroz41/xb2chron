#include "ptlib/renderer/RendererManager.h"
#include "ptlib/renderer/RendererObj.h"
#include "ptlib/renderer/RendererStream.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/StackAllocater.h"
#include "mm/MMStdBase.h"

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
