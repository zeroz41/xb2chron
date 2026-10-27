#include "grlib/CGLibRenderTarget.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostObjRainDrop.h"
#include "ml/DrPixlRenderTarget.h"
#include "ml/DrPixlPostObjCubeMapIBL.h"
#include "ml/DrPixlPostObjRainDrop.h"
#include "ml/DrPixlRenderTarget.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrAPCache.h"
#include "classes/grlib/CGLibUniformEtcUtility.h"
#include "grlib/CGLibShader.h"
#include "ml/DrAPGxType.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "ml/DrPixlMan.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtGlobalIBL.h"
#include "ml/DrShdLgtMan.h"
#include "ml/DrShdMan.h"
#include "mm/Vec4.h"
#include <math.h>
#include "grlib/CGLibDblUniformBlock.h"
#include "ml/DrPixlPostParm.h"
#include "mtl/MemManager.h"
#include <string.h>

namespace ml {

DrPixlPostObjCubeMapIBL::DrPixlPostObjCubeMapIBL(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_reset(true), m_blendCount(0), m_bufIdx(0) {
    for (int i = 0; i < 2; i++) {
        m_cubeMap[i] = new (drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderCubeMapMipMap(drMan);
        m_cubeMap[i]->setTextureInfo(64.0f, 64.0f, static_cast<GrlSurfaceFormat>(0x3F), false, 0);
    }
    m_mipNum = 5;
    m_uniformBlock = new (drMan->m_resHandle, nullptr, 0, 4, false) grlib::CGLibDblUniformBlock;
    m_uniformBlock->setup(0x110);
    memset(m_shMatrix, 0, sizeof(m_shMatrix));
    m_mtx = mm::Mat44::identity;
    m_pos = mm::Vec3::zero;
}

DrPixlPostObjCubeMapIBL::~DrPixlPostObjCubeMapIBL() {
    if (m_cubeMap[0] != nullptr) {
        delete m_cubeMap[0];
        m_cubeMap[0] = nullptr;
    }
    if (m_cubeMap[1] != nullptr) {
        delete m_cubeMap[1];
        m_cubeMap[1] = nullptr;
    }
    if (m_uniformBlock != nullptr) {
        delete m_uniformBlock;
        m_uniformBlock = nullptr;
    }
}

grlib::CGLibTextureBuffer* DrPixlPostObjCubeMapIBL::getPremTexture() const {
    return m_cubeMap[m_bufIdx]->m_pTexture;
}

const mm::Mat44& DrPixlPostObjCubeMapIBL::getSHMatrix(unsigned int idx) const {
    return m_shMatrix[m_bufIdx][idx];
}

void DrPixlPostObjCubeMapIBL::setUniformBlock(unsigned int location) const {
    m_uniformBlock->setUniformBlock(location);
}

DrPixlPostObjRainDrop::DrPixlPostObjRainDrop(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), m_flags(0), m_param0(0.0f), m_param1(0.1f), m_param2(0.2f) {
    m_target = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
}

DrPixlPostObjRainDrop::~DrPixlPostObjRainDrop() {
    if (m_target != nullptr) {
        delete m_target;
        m_target = nullptr;
    }
}

void DrPixlPostObjRainDrop::resetColorBuff() {}

void DrPixlPostObjRainDrop::update() {
    m_drMan->m_postParm[m_drMan->m_postParmIdx]->getRainDropOn();
}

void DrPixlPostObjRainDrop::requestUseLoadedDepth() {
    m_flags &= ~4u;
}

}  // namespace ml
