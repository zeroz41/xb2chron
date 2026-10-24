#include "classes/ml/DrResMdoInstPartsAnm.h"
#include "classes/ml/DrResMdoInstPartsGlbID.h"
#include "classes/ml/DrResMdoSeamColi.h"
#include "classes/ml/DrResMdoSortMpf.h"
#include "classes/ml/DrResMdoSortPos.h"
#include "classes/ml/DrResMdoSortSeamAll.h"
#include "classes/ml/DrResMdoSortNom.h"
#include "classes/ml/DrResMdoSortNomLastApha.h"
#include "classes/ml/DrResMdoSortNomFastApha.h"
#include "classes/ml/DrResMdoSortNomCldBackApha.h"
#include "classes/ml/DrResMdoSortGrp.h"
#include "classes/ml/DrResMdoSortSeamEnvMap.h"
#include "classes/ml/DrResMdoSortCloud.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/navi/NvmshAcObjBaseGbl.h"
#include "ml/DrResEtcParams.h"
#include "ml/DrResFetch.h"
#include "ml/DrResMdoLight.h"
#include "ml/DrResMdoPosInstAnm.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrResEtcPamObj.h"
#include "ml/DrResMdoLodObj.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResMdoMorpObj.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrResMdoInstPartsObj.h"
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
#include "ml/DrShdDataObj.h"

namespace ml {

void DrShdLgtClustered::update() {}

void DrShdLgtClustered::delViewInfo(int) {}

void DrShdLgtClustered::setPntLightUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pntLight.setUniformBlock(location);
}

void DrShdLgtClustered::setSptLightUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].sptLight.setUniformBlock(location);
}

void DrShdLgtClustered::setPointerListUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pointerList.setUniformBlock(location);
}

void DrShdLgtClustered::setLightListUniformBlock(unsigned int, unsigned int) {}

void DrShdLgtClustered::setParamUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].param.setUniformBlock(location);
}

void DrShdLgtClustered::setPntLightStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pntLight.setStorageBuffer(location);
}

void DrShdLgtClustered::setSptLightStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].sptLight.setStorageBuffer(location);
}

void DrShdLgtClustered::setPointerListStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pointerList.setStorageBuffer(location);
}

void DrShdLgtClustered::setLightListStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].lightList.setStorageBuffer(location);
}

void DrShdLgtClustered::setParamStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].param.setStorageBuffer(location);
}

void DrShdLgtClustered::debugRender() {}

}  // namespace ml
