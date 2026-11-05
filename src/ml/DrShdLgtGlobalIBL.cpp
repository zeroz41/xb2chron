#include "classes/mm/mtl/List.h"
#include "classes/ml/DrMan.h"
#include "ml/DrLightObjGlobalIBL.h"
#include "ml/DrPixlMan.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjCubeMapMultiIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "algorithm"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "mm/Vec4.h"
#include <string.h>

namespace ml {
namespace _dr_shd_lgt_glb_ibl {
bool CompareByPriority(const DrLightObjGlobalIBL* a, const DrLightObjGlobalIBL* b) {
    return a->getPriority() > b->getPriority();
}
}  // namespace _dr_shd_lgt_glb_ibl

DrShdLgtGlobalIBL::~DrShdLgtGlobalIBL() {
    for (int i = 0; i < 4; i++) {
        if (m_view[i].m_uniformBlock != nullptr) {
            delete m_view[i].m_uniformBlock;
            m_view[i].m_uniformBlock = nullptr;
        }
        m_view[i].m_objList.freeNodes();
    }
}

void DrShdLgtGlobalIBL::update(int viewIdx) {
    DrMan* drMan = m_drMan;
    if (viewIdx != 0) {
        if (viewIdx < 1) return;
        if (!drMan->m_viewInfo[viewIdx].m_enable) return;
    }
    updateView(viewIdx);
}

void DrShdLgtGlobalIBL::addObj(DrLightObjGlobalIBL* obj, int viewIdx) {
    ViewInfo& view = m_view[viewIdx];
    view.m_objList.insert(view.m_objList.end(), obj);
}

void DrShdLgtGlobalIBL::render(DrShdLgtMan* lgtMan) {
    if (!m_drMan->m_postParm[m_drMan->m_postParmIdx]->m_multiIBL) return;
    renderIndexTable();
    renderLinkList(lgtMan);
    for (const Slot& slot : m_view[m_drMan->m_postParmIdx].m_slot) {
        if (slot.m_obj == nullptr || slot.m_state[(slot.m_frame + 2) % 3] == 3) continue;
        for (int k = 0; k < 3; k++) {
            if (slot.m_state[k] == 2) {
                grlib::CGLibCtlShader::setMemoryBarrierBit(2);
                renderByLinkList(lgtMan);
                return;
            }
        }
    }
}

bool DrShdLgtGlobalIBL::isEnable() const {
    return m_view[m_drMan->m_postParmIdx].m_objList.m_size > 0;
}

void DrShdLgtGlobalIBL::delViewInfo(int viewIdx) {}

void DrShdLgtGlobalIBL::resetColorBuff(int viewIdx) {
    if (m_drMan->m_postParm[viewIdx]->m_iblColorMode == 3) {
        m_view[viewIdx].m_resetColorBuff = true;
    }
}

void DrShdLgtGlobalIBL::updateUniformBlock(int viewIdx) {
    updateUniformBlockImpl(viewIdx);
}
}  // namespace ml

// m_objList's destructors (the List table the constructor installs holds them; the constructor is not written yet)
template mm::mtl::List<ml::DrLightObjGlobalIBL*>::~List();
template mm::mtl::_ReslistBase<ml::DrLightObjGlobalIBL*>::~_ReslistBase();
// updateView's std::sort with CompareByPriority (updateView is not written yet)
template void std::__sort<bool (*&)(const ml::DrLightObjGlobalIBL*, const ml::DrLightObjGlobalIBL*), ml::DrLightObjGlobalIBL**>(
    ml::DrLightObjGlobalIBL**, ml::DrLightObjGlobalIBL**, bool (*&)(const ml::DrLightObjGlobalIBL*, const ml::DrLightObjGlobalIBL*));
