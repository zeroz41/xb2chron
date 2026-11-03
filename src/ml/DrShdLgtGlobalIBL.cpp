#include "classes/mm/mtl/List.h"
#include "classes/ml/DrMan.h"
#include "ml/DrLightObjGlobalIBL.h"
#include "ml/DrPixlPostParm.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "algorithm"

namespace ml {
namespace _dr_shd_lgt_glb_ibl {
bool CompareByPriority(const DrLightObjGlobalIBL* a, const DrLightObjGlobalIBL* b) {
    return a->getPriority() > b->getPriority();
}
}  // namespace _dr_shd_lgt_glb_ibl

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

// m_objList's destructors (the class destructor, not written yet, runs them)
template mm::mtl::List<ml::DrLightObjGlobalIBL*>::~List();
template mm::mtl::_ReslistBase<ml::DrLightObjGlobalIBL*>::~_ReslistBase();
// updateView's std::sort with CompareByPriority (updateView is not written yet)
template void std::__sort<bool (*&)(const ml::DrLightObjGlobalIBL*, const ml::DrLightObjGlobalIBL*), ml::DrLightObjGlobalIBL**>(
    ml::DrLightObjGlobalIBL**, ml::DrLightObjGlobalIBL**, bool (*&)(const ml::DrLightObjGlobalIBL*, const ml::DrLightObjGlobalIBL*));
