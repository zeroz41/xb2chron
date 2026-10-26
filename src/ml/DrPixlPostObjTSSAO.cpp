#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/navi/NvmshManager.h"
#include "classes/navi/NvmshResMan.h"
#include "grlib/CGLibCtl.h"
#include "mtl/MemManager.h"
#include "grlib/CGLibUniBaseUtility.h"
#include "grlib/CGLibVtxIndex.h"
#include "idcoli/IDColiGrandObj.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiTreeTop.h"
#include "idcoli/IDColiUtilColi.h"
#include "ml/CriticalSection.h"
#include "ml/DrAPGxType.h"
#include "ml/DrCalcClipMan.h"
#include "ml/DrCalcGpuCost.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrLightObjGlobalIBL.h"
#include "ml/DrPixlPostMan.h"
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjTSSAO.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrRequetIBL.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "navi/NvmshAcMan.h"

namespace ml {

DrLightObjLocalIBL::~DrLightObjLocalIBL() {}

DrPixlPostObjExpStencil::DrPixlPostObjExpStencil(DrMan* drMan) : m_pDrMan(drMan) {}

DrPixlPostObjExpStencil::~DrPixlPostObjExpStencil() {}

void DrPixlPostObjExpStencil::render() {}

void DrPixlPostObjTSSAO::update() { m_postMan->setDownDepth(); }

DrPixlPostObjUnbranchToDepth::DrPixlPostObjUnbranchToDepth(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan) {}

DrPixlPostObjUnbranchToDepth::~DrPixlPostObjUnbranchToDepth() {}

void DrPixlPostObjUnbranchToDepth::render() {
    renderFull();
    if (m_drMan->m_unbranchQuater) {
        renderQuater();
    }
}

DrRequetIBL::DrRequetIBL(DrLightObjGlobalIBL* ibl) : m_pIBL(ibl), m_id(reinterpret_cast<unsigned long>(ibl)) {}

unsigned int DrRequetIBL::getTextureNum() const { return m_pIBL->m_textureNum; }

const grlib::CGLibTextureBuffer* DrRequetIBL::getTexture(unsigned int index) const { return &m_pIBL->m_texture[index]; }

const mm::Mat44* DrRequetIBL::getSHMatrix(unsigned int index, unsigned int term) const {
    return m_pIBL->m_shMatrix + (term + index * 4);
}

float DrRequetIBL::getSkyIntensity() const { return m_pIBL->m_skyIntensity; }

float DrRequetIBL::getDirLightIntensity() const { return m_pIBL->m_dirLightIntensity; }

const mm::Vec3* DrRequetIBL::getAdditionalAmbient() const { return &m_pIBL->m_additionalAmbient; }

unsigned int DrRequetIBL::getVersion() const { return m_pIBL->m_version; }

DrShdLgtHybrid::DrShdLgtHybrid(DrMan* drMan) {
    m_pDrMan = drMan;
    m_pClustered = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtClustered(drMan, false);
    m_pTileBasedDr = new (drMan->m_workHandle, nullptr, 0, 4, false) DrShdLgtTileBasedDr(drMan);
}

DrShdLgtHybrid::~DrShdLgtHybrid() {
    if (m_pClustered) {
        delete m_pClustered;
        m_pClustered = nullptr;
    }
    if (m_pTileBasedDr) {
        delete m_pTileBasedDr;
        m_pTileBasedDr = nullptr;
    }
}

DrShdCubeCapFilter::DrShdCubeCapFilter(DrMan* drMan) : m_pDrMan(drMan) {}

DrShdCubeCapFilter::~DrShdCubeCapFilter() {}

void DrShdLgtHybrid::stockBegin() {
    m_pClustered->stockBegin();
    m_pTileBasedDr->stockBegin();
}

void DrShdLgtHybrid::stockEnd() {
    m_pClustered->stockEnd();
    m_pTileBasedDr->stockEnd();
}

void DrShdLgtHybrid::update() {
    m_pClustered->update();
    m_pTileBasedDr->update();
}

void DrShdLgtHybrid::setupCate(int cateIdx) {
    m_cateIdx = cateIdx;
    m_pClustered->setupCate(cateIdx);
    m_pTileBasedDr->setupCate(cateIdx);
}

void DrShdLgtHybrid::addViewInfo(int view) {
    m_pClustered->addViewInfo(view);
    m_pTileBasedDr->addViewInfo(view);
}

void DrShdLgtHybrid::delViewInfo(int view) {
    m_pClustered->delViewInfo(view);
    m_pTileBasedDr->delViewInfo(view);
}

void DrShdLgtHybrid::stockPntList(DrLightObjPnt* light) {
    m_pClustered->stockPntList(light);
    m_pTileBasedDr->stockPntList(light);
}

void DrShdLgtHybrid::stockSptList(DrLightObjSpt* light) {
    m_pClustered->stockSptList(light);
    m_pTileBasedDr->stockSptList(light);
}

void DrShdLgtHybrid::render(DrShdLgtMan* shdLgtMan, DrLightMan* lightMan) {
    switch (m_pDrMan->m_shdLgtType) {
    case 0:
        m_pTileBasedDr->render(shdLgtMan, lightMan);
        break;
    case 1:
        if (!DrMan::getIns()->m_clusteredRenderOff) {
            m_pClustered->render(shdLgtMan, lightMan);
        }
        break;
    }
}

void DrShdLgtHybrid::debugRender() {
    switch (m_pDrMan->m_shdLgtType) {
    case 0:
        m_pTileBasedDr->debugRender();
        break;
    case 1:
        m_pClustered->debugRender();
        break;
    }
}

void ScnObjModelDrSys::update() {}

void ScnObjModelDrSys::setGroups(int groups) { m_pMdlObj->setGroups(groups); }

int ScnObjModelDrSys::getGroups() { return m_pMdlObj->getGroups(); }

void ScnObjModelDrSys::setAlpha(float alpha) { m_pMdlObj->setAlpha(alpha); }

float ScnObjModelDrSys::getAlpha() const { return m_pMdlObj->getAlpha(); }

void ScnObjModelDrSys::setWriteStencil(bool enable) { m_pMdlObj->setWriteStencil(enable); }

void ScnObjModelDrSys::setAlwaysTexStm(bool enable) { m_pMdlObj->setAlwaysTexStm(enable); }

bool ScnObjModelDrSys::isMdlTexStm() const { return m_pMdlObj->isMdlTexStm(); }

bool ScnObjModelDrSys::isMemTexStm() const { return m_pMdlObj->isMemTexStm(); }

const mm::Vec3& ScnObjModelDrSys::getAABBMax() const { return m_pMdlObj->getAABBMax(); }

const mm::Vec3& ScnObjModelDrSys::getAABBMin() const { return m_pMdlObj->getAABBMin(); }

const mm::Vec3& ScnObjModelDrSys::getCenter() const { return m_pMdlObj->getCenter(); }

float ScnObjModelDrSys::getLength() const { return m_pMdlObj->getLength(); }

}  // namespace ml
