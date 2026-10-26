// xbrd's library (ScnObjModelDrSysStandard::apply's matrix copy asserts with xbrd's mcl path)
#define MM_LIB_FROM_XBRD
#include "mm/Mat44.h"
#include "ml/AttrTransform.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/ml/ScnObjModelDrSysStandard.h"
#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibCtl.h"
#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrAPCacheNx.h"
#include "ml/DrAPGxType.h"
#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrAPCacheNx.h"
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
#include "classes/ml/ScnObjModelDrSysStandard.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/navi/NvmshManager.h"
#include "classes/navi/NvmshResMan.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibState.h"
#include "grlib/CGLibTextureBuffer.h"
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
#include "ml/DrResFetch.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "navi/NvmshAcMan.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "ml/AttrTransform.h"
#include "ml/DrCreator.h"
#include "mm/Col4.h"
#include "mtl/MemManager.h"

namespace ml {

ScnObjModelDrSysStandard::~ScnObjModelDrSysStandard() {
    if (m_pMdlObj != nullptr) {
        m_pMdlObj->setDisp(false);
        m_pMdlObj->setDeleteCall(DrMan::s_nDblStockIdx);
    }
}

void ScnObjModelDrSysStandard::update() { ScnObjModelDrSys::update(); }

// the draw model takes the world matrix with the scale applied to its rows, and the offset
void ScnObjModelDrSysStandard::apply() {
    ScnObjModelDrSys::apply();
    if (m_pMdlObj != nullptr) {
        mm::Mat44 mat(getTrans(false)->m_worldMat);
        const mm::Vec3& scl = static_cast<const ScnObjModel*>(this)->getTrans(false)->m_scl;
        mat.m[0][0] = scl.x * mat.m[0][0];
        mat.m[0][1] = scl.x * mat.m[0][1];
        mat.m[0][2] = scl.x * mat.m[0][2];
        mat.m[1][0] = scl.y * mat.m[1][0];
        mat.m[1][1] = scl.y * mat.m[1][1];
        mat.m[1][2] = scl.y * mat.m[1][2];
        mat.m[2][0] = scl.z * mat.m[2][0];
        mat.m[2][1] = scl.z * mat.m[2][1];
        mat.m[2][2] = scl.z * mat.m[2][2];
        m_pMdlObj->setMatrix(mat);
        m_pMdlObj->setOffsetPos(getOffsetInfo(false));
    }
}

void ScnObjModelDrSysStandard::tail() { ScnObjModel::tail(); }

ScnObjModelDrSysStandard* ScnObjModelDrSysStandard::create(Scn* scn, const void* res, const char* name, int view) {
    if (!scn->m_pool->isValidInsert(1)) {
        return nullptr;
    }
    ScnObjModelDrSysStandard* mdl =
        new (scn->m_allocHandle, nullptr, 0, 4, false) ScnObjModelDrSysStandard(scn, res, name, view);
    scn->m_pool->insert(mdl);
    return mdl;
}

// the clamp modes the first 64 samplers combine (the name is not the original's)
static const int s_samplerClampTbl[4] = {0, 1, 2, 6};

// 78 samplers: 64 combining min filter (mipmapped or not), mag filter and the s/t clamp modes, then single ones
void DrAPCache::createSampler() {
    m_pSampler = new (DrMan::getIns()->m_workHandle, nullptr, 0, 4, false) grlib::CGLibSampler[78];
    int idx = 0;
    for (int mip = 0; mip < 2; mip++) {
        for (int mag = 0; mag < 2; mag++) {
            for (int s = 0; s < 4; s++) {
                for (int t = 0; t < 4; t++) {
                    grlib::CGLibSampler& smp = m_pSampler[idx++];
                    if (mag == 0) {
                        smp.initSampler((GrlTexClamp)2, (GrlTexMagFilterType)0);
                        if (mip == 1) {
                            smp.setFilter((GrlTexMagFilterType)0, (GrlTexMinFilterType)2, (GrlTexTexAnisoRatio)0);
                        } else {
                            smp.setFilter((GrlTexMagFilterType)0, (GrlTexMinFilterType)0, (GrlTexTexAnisoRatio)0);
                        }
                    } else {
                        smp.initSampler((GrlTexClamp)2, (GrlTexMagFilterType)1);
                        if (mip == 1) {
                            smp.setFilter((GrlTexMagFilterType)1, (GrlTexMinFilterType)5, (GrlTexTexAnisoRatio)0);
                        } else {
                            smp.setFilter((GrlTexMagFilterType)1, (GrlTexMinFilterType)1, (GrlTexTexAnisoRatio)0);
                        }
                    }
                    smp.setClamp((GrlTexClamp)s_samplerClampTbl[s], (GrlTexClamp)s_samplerClampTbl[t], (GrlTexClamp)2);
                }
            }
        }
    }
    m_pSampler[65].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)1);
    m_pSampler[65].setClamp((GrlTexClamp)2, (GrlTexClamp)2, (GrlTexClamp)2);
    m_pSampler[66].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)0);
    m_pSampler[66].setClamp((GrlTexClamp)2, (GrlTexClamp)2, (GrlTexClamp)2);
    m_pSampler[67].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)1);
    m_pSampler[67].setClamp((GrlTexClamp)0, (GrlTexClamp)0, (GrlTexClamp)0);
    m_pSampler[68].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)0);
    m_pSampler[68].setClamp((GrlTexClamp)0, (GrlTexClamp)0, (GrlTexClamp)0);
    m_pSampler[69].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)1);
    m_pSampler[69].setClamp((GrlTexClamp)2, (GrlTexClamp)2, (GrlTexClamp)2);
    m_pSampler[70].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)0);
    m_pSampler[70].setClamp((GrlTexClamp)2, (GrlTexClamp)2, (GrlTexClamp)2);
    m_pSampler[71].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)1);
    m_pSampler[71].setClamp((GrlTexClamp)2, (GrlTexClamp)2, (GrlTexClamp)2);
    m_pSampler[71].setFilter((GrlTexMagFilterType)1, (GrlTexMinFilterType)5, (GrlTexTexAnisoRatio)0);
    m_pSampler[72].initSampler((GrlTexClamp)2, (GrlTexMagFilterType)0);
    m_pSampler[72].setClamp((GrlTexClamp)2, (GrlTexClamp)2, (GrlTexClamp)2);
    m_pSampler[72].setFilter((GrlTexMagFilterType)0, (GrlTexMinFilterType)2, (GrlTexTexAnisoRatio)0);
    m_pSampler[73].initSampler((GrlTexClamp)6, (GrlTexMagFilterType)1);
    m_pSampler[73].setDepthCompare((GrlTexCompare)3);
    m_pSampler[73].setBorderType((GrlTexBorderType)2);
    m_pSampler[74].initSampler((GrlTexClamp)6, (GrlTexMagFilterType)1);
    m_pSampler[74].setBorderType((GrlTexBorderType)2);
    m_pSampler[75].initSampler((GrlTexClamp)6, (GrlTexMagFilterType)1);
    m_pSampler[75].setBorderType((GrlTexBorderType)0);
    m_pSampler[76].initSampler((GrlTexClamp)6, (GrlTexMagFilterType)1);
    m_pSampler[76].setBorderColor(mm::Col4(8161.0f, 0.0f, 0.0f, 0.0f));
    m_pSampler[77].initSampler((GrlTexClamp)6, (GrlTexMagFilterType)1);
    m_pSampler[77].setBorderColor(mm::Col4(-8161.0f, 0.0f, 0.0f, 0.0f));
    for (int i = 0; i < 78; i++) {
        m_pSampler[i].updateData();
    }
}

DrAPCache* DrAPCache::s_pIns;

const int DrAPCache::TEXTYPE_R_8 = 1;
const int DrAPCache::TEXTYPE_R_UI8 = 3;
const int DrAPCache::TEXTYPE_RGBA_8 = 0x25;
const int DrAPCache::TEXTYPE_RGB_5 = 0x25;
const int DrAPCache::TEXTYPE_RGB_11 = 0x3F;
const int DrAPCache::TEXTYPE_RGB10A2_UNORM = 0x3D;
const int DrAPCache::TEXTYPE_HALF_X1 = 5;
const int DrAPCache::TEXTYPE_HALF_X4 = 0x29;
const int DrAPCache::TEXTYPE_FLOAT_X1 = 0xA;
const int DrAPCache::TEXTYPE_FLOAT_X2 = 0x16;
const int DrAPCache::TEXTYPE_R_UI32 = 0xB;
const int DrAPCache::TEXTYPE_RG_UI32 = 0x17;

void DrAPCache::begin() {
    m_cullType = 4;
    m_alphaBlend = -1;
    pad_C = -1;
    m_stencilRef = -1;
    m_stencilMode = -1;
    m_depthWrite = -1;
    m_depthMode = -1;
    m_gBuffRender = 0;
    pad_28 = -1;
    beginTexSampling(0, 0);
}

void DrAPCache::depthBegin() {
    m_depthWrite = -1;
    m_depthMode = -1;
    m_stencilRef = -1;
}

void DrAPCache::shadowBegin() {
    m_depthWrite = 1;
    m_stencilMode = -1;
    m_depthMode = 2;
    m_alphaBlend = 0;
    m_cullType = 2;
    m_stencilRef = -1;
    grlib::CGLibDepthCtl::setDepthControl(1, 1, (GrlCompare)1);
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
}

void DrAPCache::beginZRender() {
    m_depthMode = 2;
    m_depthWrite = 1;
    m_stencilMode = -1;
    m_cullType = 2;
    m_stencilRef = -1;
    grlib::CGLibDepthCtl::setDepthControl(1, 1, (GrlCompare)1);
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginThicknessRenderFirst() {
    m_depthMode = 2;
    m_stencilMode = -1;
    m_depthWrite = 0;
    m_cullType = 2;
    m_stencilRef = -1;
    grlib::CGLibDepthCtl::setDepthControl(1, 0, (GrlCompare)1);
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setColorChannelMask(1, 0, 0, 0);
    grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)2, (GrlBlendCombine)4, (GrlBlendFunc)2,
                                          (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)3);
}

void DrAPCache::endThicknessRenderFirst() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginThicknessRenderSecond() {
    m_depthMode = 2;
    m_depthWrite = 1;
    m_stencilMode = -1;
    m_cullType = 2;
    m_stencilRef = -1;
    grlib::CGLibDepthCtl::setDepthControl(1, 1, (GrlCompare)1);
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endThicknessRenderSecond() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginMdlZRender() {
    m_depthMode = 2;
    m_depthWrite = 1;
    m_stencilRef = -1;
    m_stencilMode = -1;
    grlib::CGLibDepthCtl::setDepthControl(1, 1, (GrlCompare)1);
    grlib::CGLibColorCtl::setColorBufferOff();
}

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

void DrAPCache::setMrtGBuffRender(unsigned int render, unsigned int mrt) {
    if (m_gBuffRender == render) {
        return;
    }
    long second = mrt & 1;
    unsigned int third = ((mrt >> 1) & 1) + second;
    m_gBuffRender = render;
    unsigned char masks[3] = {0, 0, 0};
    if (render & 0x1) masks[0] |= 7;
    if (render & 0x2) masks[third] |= 3;
    if (render & 0x4) masks[second] |= 2;
    if (render & 0x8) masks[second] |= 1;
    if (render & 0x10) masks[second] |= 8;
    if (render & 0x20) masks[second] |= 4;
    if (render & 0x40) masks[third] |= 4;
    if (render & 0x80) masks[third] |= 0xB;
    for (int i = 0; i < 3; i++) {
        if (masks[i] != 0) {
            grlib::CGLibColorCtl::setColorChannelMask((grlib::GrlMrtType)i, masks[i] & 1, (masks[i] >> 1) & 1,
                                                      (masks[i] >> 2) & 1, (masks[i] >> 3) & 1);
        }
    }
}

void DrAPCache::endGBuffRender() { grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1); }

void DrAPCache::setRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(0, 0, 0, 0); }

void DrAPCache::endRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1); }

void DrAPCache::setupCulling(DrApCullType type) {
    if (m_cullType == type) {
        return;
    }
    m_cullType = type;
    switch (type) {
    case 0:
        grlib::CGLibPolygon::setCullingBack();
        break;
    case 1:
        grlib::CGLibPolygon::setCullingFront();
        break;
    case 2:
        grlib::CGLibPolygon::setCullingOff();
        break;
    default:
        grlib::CGLibPolygon::setCullingDispOff();
        break;
    }
}

// depth write switch per setupDepthStencil's depthWrite (proposed name, not the original's: the symbols leave it
// unnamed (lbl_71009D4F3C))
static const unsigned char s_depthWriteTbl[] = {0, 1};

void DrAPCache::setupDepthStencil(int stencilRef, int stencilMode, int depthWrite, int depthMode) {
    if (m_stencilRef == stencilRef && m_stencilMode == stencilMode && m_depthWrite == depthWrite &&
        m_depthMode == depthMode) {
        return;
    }
    m_stencilRef = stencilRef;
    m_stencilMode = stencilMode;
    m_depthWrite = depthWrite;
    m_depthMode = depthMode;
    unsigned char depthTest;
    GrlCompare depthCompare;
    if (depthMode == 0) {
        depthTest = 0;
        depthCompare = (GrlCompare)1;
    } else if (depthMode == 1) {
        depthTest = 1;
        depthCompare = (GrlCompare)3;
    } else {
        depthTest = 1;
        depthCompare = depthMode == 3 ? (GrlCompare)2 : (GrlCompare)1;
    }
    unsigned char stencilTest = 1;
    GrlCompare stencilCompare = (GrlCompare)7;
    unsigned int ref = stencilRef;
    unsigned int writeMask = 0xFF;
    unsigned int mask = 0xFF;
    GrlStencil fail = (GrlStencil)3;
    switch (stencilMode) {
    case 0:
        stencilTest = 0;
        break;
    case 2:
        stencilCompare = (GrlCompare)2;
        mask = stencilRef;
        writeMask = stencilRef;
        fail = (GrlStencil)1;
        break;
    case 3:
        ref = 0;
        break;
    case 4:
        stencilCompare = (GrlCompare)5;
        mask = stencilRef;
        writeMask = stencilRef;
        break;
    case 5:
        stencilCompare = (GrlCompare)2;
        mask = stencilRef | 0x20;
        writeMask = stencilRef | 0x20;
        fail = (GrlStencil)1;
        break;
    case 6:
        stencilCompare = (GrlCompare)2;
        mask = 4;
        writeMask = stencilRef;
        break;
    case 7:
        mask = 4;
        writeMask = stencilRef | 4;
        break;
    default:
        if (stencilMode == 8) {
            stencilCompare = (GrlCompare)2;
            mask = stencilRef | 2;
            writeMask = stencilRef;
            fail = (GrlStencil)1;
        }
        break;
    }
    grlib::CGLibDepthCtl::setDepthStencilControl(depthTest, s_depthWriteTbl[depthWrite], depthCompare, stencilTest,
                                                 stencilCompare, ref, mask, writeMask, fail, (GrlStencil)1,
                                                 (GrlStencil)1);
}

void DrAPCache::setupAlphaBlend(int blend) {
    if (blend == 0) {
        if (m_alphaBlend != 0) {
            grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
            m_alphaBlend = 0;
        }
    } else if (m_alphaBlend != blend) {
        switch (blend) {
        case 1:
            grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)5, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
            break;
        case 2:
            grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)5, (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)3);
            break;
        case 3:
            grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)1, (GrlBlendFunc)3, (GrlBlendCombine)1, (GrlLogicType)3);
            break;
        case 4:
            grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)10, (GrlBlendFunc)1, (GrlBlendCombine)1, (GrlLogicType)3);
            break;
        case 5:
            grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)3);
            break;
        case 6:
            grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)5, (GrlBlendCombine)1, (GrlLogicType)3);
            break;
        case 7:
            grlib::CGLibColorCtl::setMrtBlend(1, (GrlLogicType)3);
            grlib::CGLibColorCtl::setMrtBlendControl((grlib::GrlMrtType)0, (GrlBlendFunc)5, (GrlBlendFunc)6,
                                                     (GrlBlendCombine)1);
            break;
        }
        m_alphaBlend = blend;
    }
    pad_C = -1;
}

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

void DrAPCache::setMipMapOn(const grlib::CGLibTextureBuffer& texture) { m_mipMap = texture.getMipmap() != 0; }

void DrAPCache::setupShader(grlib::CGLibDecShdExtTbl* table, DrResFetch* fetch) {
    grlib::CGLibCtlShader::setShader(*table, *fetch);
}

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer& texture, unsigned int location) {
    unsigned short index = m_specialSampler;
    if (index == 0) {
        index = m_texSampling[1] + (m_texSampling[0] << 2) + (m_texWrap << 4) + (m_mipMap << 5);
    }
    grlib::CGLibCtlTexture::setTexture(texture, m_pSampler[index], location);
}

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer& texture, const grlib::CGLibSampler& sampler,
                           unsigned int location) {
    grlib::CGLibCtlTexture::setTexture(texture, sampler, location);
}

void DrAPGxType::setupScreenQuads(bool blend) {
    if (blend) {
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)5, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
    } else {
        grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
    }
    grlib::CGLibDepthCtl::setDepthControl(0, 0, (GrlCompare)7);
    grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::setupBloomAddMaterial(GrlBlendFunc src, GrlBlendFunc dst) {
    grlib::CGLibColorCtl::setBlendControl(src, dst, (GrlBlendCombine)1, (GrlLogicType)3);
    grlib::CGLibDepthCtl::setDepthControl(0, 0, (GrlCompare)7);
    grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::beginOccQuery() {
    grlib::CGLibPolygon::setCullingOff();
    grlib::CGLibColorCtl::setColorBufferOff();
    grlib::CGLibDepthCtl::setDepthControl(1, 0, (GrlCompare)3);
}

void DrAPGxType::endOccQuery() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginShadow() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endShadow() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::shadowCacheSetup() {
    grlib::CGLibColorCtl::setColorBufferOff();
    grlib::CGLibDepthCtl::setDepthControl(1, 1, (GrlCompare)7);
    grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::beginColorOff() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endColorOff() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::setupAlphaChanel(bool alpha) {
    if (alpha) {
        grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 1);
    } else {
        grlib::CGLibColorCtl::setColorChannelMask(1, 1, 1, 0);
    }
}

void DrAPGxType::setupCullingOff() { grlib::CGLibPolygon::setCullingOff(); }

void DrAPGxType::setupCullingFront() { grlib::CGLibPolygon::setCullingFront(); }

void DrAPGxType::setupCullingBack() { grlib::CGLibPolygon::setCullingBack(); }

void DrAPGxType::setupStencilPrePassReset() { grlib::CGLibDepthCtl::setDepthControl(1, 1, (GrlCompare)1); }

// the compare and stencil-operation values the setters take, by index (proposed names, not the original's: the
// symbols leave them unnamed (lbl_71009B7BC8, lbl_71009B7BA8); the linker keeps one copy of each for several units)
static const GrlCompare s_compareTbl[] = {(GrlCompare)0, (GrlCompare)1, (GrlCompare)2, (GrlCompare)3,
                                          (GrlCompare)4, (GrlCompare)5, (GrlCompare)6, (GrlCompare)7};
static const GrlStencil s_stencilTbl[] = {(GrlStencil)1, (GrlStencil)2, (GrlStencil)3, (GrlStencil)4,
                                          (GrlStencil)5, (GrlStencil)6, (GrlStencil)7, (GrlStencil)8};

void DrAPGxType::setupStencilTest(unsigned char depthTest, unsigned char depthWrite, int depthCompare,
                                  unsigned char stencilTest, unsigned int ref, unsigned int mask, int stencilCompare,
                                  int fail, int depthFail, int pass) {
    grlib::CGLibDepthCtl::setDepthStencilControl(depthTest, depthWrite, s_compareTbl[depthCompare], stencilTest,
                                                 s_compareTbl[stencilCompare], ref, mask, mask, s_stencilTbl[fail],
                                                 s_stencilTbl[depthFail], s_stencilTbl[pass]);
}

void DrAPGxType::setupStencilTestWriteMask(unsigned char depthTest, unsigned char depthWrite, int depthCompare,
                                           unsigned char stencilTest, unsigned int ref, unsigned int mask,
                                           unsigned int writeMask, int stencilCompare, int fail, int depthFail,
                                           int pass) {
    grlib::CGLibDepthCtl::setDepthStencilControl(depthTest, depthWrite, s_compareTbl[depthCompare], stencilTest,
                                                 s_compareTbl[stencilCompare], ref, mask, writeMask,
                                                 s_stencilTbl[fail], s_stencilTbl[depthFail], s_stencilTbl[pass]);
}

void DrAPGxType::setupDepthContl(unsigned char test, unsigned char write, int compare) {
    grlib::CGLibDepthCtl::setDepthControl(test, write, s_compareTbl[compare]);
}

void DrAPGxType::setupBlend(int blend) {
    switch (blend) {
    default:
        grlib::CGLibColorCtl::setBlendOffControl((GrlLogicType)3);
        break;
    case 11:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)3, (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)7);
        break;
    case 10:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)1, (GrlBlendFunc)3, (GrlBlendCombine)1, (GrlBlendFunc)1,
                                              (GrlBlendFunc)5, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 9:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)4, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 8:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)3, (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 7:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 6:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)2, (GrlBlendFunc)5, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 5:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)1, (GrlBlendFunc)3, (GrlBlendCombine)1, (GrlBlendFunc)1,
                                              (GrlBlendFunc)5, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 4:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)3, (GrlBlendFunc)4, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 3:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)10, (GrlBlendFunc)1, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 2:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)5, (GrlBlendFunc)2, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    case 1:
        grlib::CGLibColorCtl::setBlendControl((GrlBlendFunc)5, (GrlBlendFunc)6, (GrlBlendCombine)1, (GrlLogicType)3);
        break;
    }
}

void DrAPGxType::getMainScreenSize(int& width, int& height) {
    width = grlib::CGLibState::getMainRenderTarget()->m_width;
    height = grlib::CGLibState::getMainRenderTarget()->m_height;
}

DrAPCacheNx::DrAPCacheNx() {}

DrAPCacheNx::~DrAPCacheNx() {
    if (m_pSampler != 0) {
        delete[] m_pSampler;
        m_pSampler = 0;
    }
}

}  // namespace ml
