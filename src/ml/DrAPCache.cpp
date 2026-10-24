#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrLightObjLocalIBL.h"
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
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "navi/NvmshAcMan.h"

namespace ml {

void DrAPCache::endZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endThicknessRenderFirst() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endThicknessRenderSecond() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::endMdlZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::setGBuffRender(unsigned int render) {
    if (m_gBuffRender == render) {
        return;
    }
    m_gBuffRender = render;
    switch (render) {
    case 0x77777777:
        grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1);
        break;
    case 0xFFFFFFFF:
        grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 0);
        break;
    }
}

void DrAPCache::endGBuffRender() { grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1); }

void DrAPCache::setRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(0, 0, 0, 0); }

void DrAPCache::endRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1); }

void DrAPCache::beginTexSampling(int sampling, int wrap) {
    m_specialSampler = 0;
    m_specialSamplerKind = 0;
    m_texSampling[0] = sampling;
    m_texSampling[1] = sampling;
    m_texWrap = wrap;
    m_mipMap = 0;
}

void DrAPCache::begin3DTextureSampling() {
    m_specialSampler = 0x41;
    m_specialSamplerKind = 1;
}

void DrAPCache::begin3DTexturePointSampling() {
    m_specialSampler = 0x42;
    m_specialSamplerKind = 1;
}

void DrAPCache::begin3DTextureWarpSampling() {
    m_specialSampler = 0x43;
    m_specialSamplerKind = 1;
}

void DrAPCache::beginCubeTextureSampling(bool b) {
    m_specialSampler = b ? 0x47 : 0x45;
    m_specialSamplerKind = 2;
}

void DrAPCache::beginCubeTexturePointSampling(bool b) {
    m_specialSampler = b ? 0x48 : 0x46;
    m_specialSamplerKind = 2;
}

void DrAPCache::beginDepthCompare() {
    m_specialSampler = 0x49;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderWhite() {
    m_specialSampler = 0x4A;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderBlack() {
    m_specialSampler = 0x4B;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderDepthMax() {
    m_specialSampler = 0x4C;
    m_specialSamplerKind = 0;
}

void DrAPCache::beginBorderDepthMinusMax() {
    m_specialSampler = 0x4D;
    m_specialSamplerKind = 0;
}

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer& texture, const grlib::CGLibSampler& sampler,
                           unsigned int location) {
    grlib::CGLibCtlTexture::setTexture(texture, sampler, location);
}

void DrAPGxType::endOccQuery() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginShadow() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endShadow() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginColorOff() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endColorOff() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::setupCullingOff() { grlib::CGLibPolygon::setCullingOff(); }

void DrAPGxType::setupCullingFront() { grlib::CGLibPolygon::setCullingFront(); }

void DrAPGxType::setupCullingBack() { grlib::CGLibPolygon::setCullingBack(); }

}  // namespace ml
