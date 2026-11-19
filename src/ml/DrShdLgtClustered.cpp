#define MM_LIB_FROM_XBRD
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
#include "classes/ml/DrLightObjPnt.h"
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
#include "mtl/MemManager.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcViewWork.h"
#include "mm/Math.h"
#include "mm/Vec3.h"
#include <math.h>
#include <string.h>

namespace ml {

const DrShdLgtClustered::ClusterSetting DrShdLgtClustered::c_ClusterSettings[4] = {
    {20, 12, 16, 20, 256},
    {5, 3, 4, 5, 16},
    {5, 3, 4, 20, 128},
    {5, 3, 4, 5, 16},
};

DrShdLgtClustered::DrShdLgtClustered(DrMan* drMan, bool flag) : m_pDrMan(drMan), m_bSmallGrid(flag) {
    createWork();
}

void DrShdLgtClustered::createWork() {
    const ClusterSetting& set = getClusterSetting(0);
    int extraSize = m_bSmallGrid ? 0x40 : 0x1D0;
    m_cellLightMax = set.cellLightMax * set.gridX * set.gridY * set.gridZ;
    unsigned int cellSize = set.getCellNum() * sizeof(unsigned long);
    unsigned int sliceSize = 0;
    for (int i = 0; i < 4; i++) {
        sliceSize += (getClusterSetting(i).gridZ + 1) * sizeof(float);
    }
    m_pWork = mtl::MemManager::allocate(m_pDrMan->m_allocHandle, sliceSize + m_cellLightMax * 0x10 + cellSize + cellSize,
                                        0x20, false, "no name", 0);
    unsigned int ofs = 0;
    for (int i = 0; i < 4; i++) {
        const ClusterSetting& s = getClusterSetting(i);
        int pntSize = s.lightMax * 0x30;
        int sptSize = s.lightMax * 0x40;
        int pointerSize = s.gridX * s.gridY * s.gridZ * 8;
        ViewWork& view = m_viewWork[i];
        view.pntLight.setup(pntSize);
        view.sptLight.setup(sptSize);
        view.pointerList.setup(pointerSize);
        view.extra.setup(extraSize);
        view.param.setup(0x30);
        view.pSliceDepth = reinterpret_cast<float*>(static_cast<unsigned char*>(m_pWork) + ofs);
        ofs += (s.gridZ + 1) * 4;
        view.lightList.setup(s.gridX * s.gridZ * s.gridY * s.cellLightMax);
    }
    m_pCellWork[0] = reinterpret_cast<unsigned long*>(static_cast<unsigned char*>(m_pWork) + ofs);
    ofs += cellSize;
    m_pCellWork[1] = reinterpret_cast<unsigned long*>(static_cast<unsigned char*>(m_pWork) + ofs);
    ofs += cellSize;
    m_pCellLight = reinterpret_cast<unsigned int*>(static_cast<unsigned char*>(m_pWork) + ofs);
    addViewInfo(0);
    m_fetch.setLgtVertexParam();
}

DrShdLgtClustered::~DrShdLgtClustered() {
    if (m_pWork) {
        mtl::MemManager::deallocate(m_pWork, 0, false);
        m_pWork = nullptr;
    }
}

void DrShdLgtClustered::stockBegin() {
    const ClusterSetting& s = getClusterSetting(m_cateIdx);
    ViewWork& view = m_viewWork[m_cateIdx];
    view.pntNum = 0;
    view.sptNum = 0;
    view.listNum = 0;
    m_pntBuffRest = view.pntLight.m_size;
    m_sptBuffRest = view.sptLight.m_size;
    m_pPntBuff = reinterpret_cast<PntLightEntry*>(view.pntLight.getBuff());
    m_pSptBuff = reinterpret_cast<SptLightEntry*>(view.sptLight.getBuff());
    unsigned int cellNum = s.gridX * s.gridY * s.gridZ;
    memset(m_pCellWork[0], 0, cellNum * sizeof(unsigned long));
    memset(m_pCellWork[1], 0, cellNum * sizeof(unsigned long));
    m_cellLightNum = 0;
}

void DrShdLgtClustered::stockEnd() {
    ViewWork& view = m_viewWork[m_cateIdx];
    if (view.pntNum == 0 && view.sptNum == 0) {
        memset(view.pointerList.getBuff(), 0, view.pointerList.m_size);
    } else {
        updateCluster();
        if (view.listNum == 0) {
            return;
        }
        ViewWork& cur = m_viewWork[m_cateIdx];
        for (int i = 0; i < cur.pntNum; i++) {
            cur.pntLight.getBuff();
        }
        for (int i = 0; i < cur.sptNum; i++) {
            cur.sptLight.getBuff();
        }
    }
    const ClusterSetting& s = getClusterSetting(m_cateIdx);
    DrCalcViewWork* viewWork = m_pDrMan->m_calcMan->m_pViewWork;
    if (view.pntNum != 0) {
        view.pntLight.updateData();
    }
    if (view.sptNum != 0) {
        view.sptLight.updateData();
    }
    view.pointerList.updateData();
    ClusterParam* param = reinterpret_cast<ClusterParam*>(view.param.getBuff());
    tanf(viewWork->m_fovY * 0.5f);
    param->cellWidth = m_pDrMan->m_curViewInfo->m_width / s.gridX;
    param->cellHeight = m_pDrMan->m_curViewInfo->m_height / s.gridY;
    param->screenWidth = m_pDrMan->m_curViewInfo->m_width;
    param->screenHeight = m_pDrMan->m_curViewInfo->m_height;
    param->gridX = s.gridX;
    param->gridY = s.gridY;
    param->gridZ = s.gridZ;
    param->zero = 0;
    param->slice = mm::Vec4(-logf(view.sliceNear), 1.0f / logf(view.sliceScale), s.gridZ - 1.0f, view.listNum);
    view.param.updateData();
}

void DrShdLgtClustered::update() {}

void DrShdLgtClustered::addViewInfo(int idx) {
    ViewWork& view = m_viewWork[idx];
    const ClusterSetting& s = getClusterSetting(idx);
    view.sliceScale = 1.36f;
    view.sliceNear = 5.0f;
    view.pSliceDepth[0] = 0.0f;
    for (int i = 0; i <= s.gridZ; i++) {
        view.pSliceDepth[i] = i == 0 ? -5.0f : view.pSliceDepth[i - 1] * view.sliceScale;
    }
}

void DrShdLgtClustered::delViewInfo(int) {}

// a light entry's last word: the light's parameter, 2.0 without its flag (a file-static inline helper: the original's
// select tests a bool parameter; the name is not the original's)
static inline float getEntryParam(bool flag, float param) { return flag ? param : 2.0f; }

void DrShdLgtClustered::stockPntList(DrLightObjPnt* light) {
    ViewWork& view = m_viewWork[m_cateIdx];
    if (getClusterSetting(m_cateIdx).lightMax != view.pntNum) {
        const mm::Mat44& mtx = m_pDrMan->m_calcMan->m_pViewWork->m_view;
        m_pntBuffRest -= sizeof(PntLightEntry);
        PntLightEntry* entry = m_pPntBuff++;
        const float* pos = &light->m_pos.x;
        float px = mtx.m[3][0] + (pos[0] * mtx.m[0][0] + pos[1] * mtx.m[1][0] + pos[2] * mtx.m[2][0]);
        float py = mtx.m[3][1] + (pos[0] * mtx.m[0][1] + pos[1] * mtx.m[1][1] + pos[2] * mtx.m[2][1]);
        float pz = (pos[0] * mtx.m[0][2] + pos[1] * mtx.m[1][2] + pos[2] * mtx.m[2][2]) + mtx.m[3][2];
        entry->pos[0] = px;
        entry->pos[1] = py;
        entry->pos[2] = pz;
        entry->size = light->m_size;
        entry->color[0] = light->m_color.r;
        entry->color[1] = light->m_color.g;
        entry->color[2] = light->m_color.b;
        entry->param2 = light->m_lightParam2;
        float param = getEntryParam(light->m_bLightFlag, light->m_lightParam);
        entry->invSize = 1.0f / light->m_size;
        entry->zero = 0.0f;
        entry->rate = light->m_lightRate;
        entry->param = param;
        view.pntNum++;
    }
}

bool DrShdLgtClustered::planeVsCone(const mm::Vec3& planePos, const mm::Vec3& planeNormal, const mm::Vec3& conePos,
                                    const mm::Vec3& coneDir, float range, float angle) const {
    float dist = (conePos - planePos).dot(planeNormal);
    if (dist > range) {
        return false;
    }
    if (dist <= 0.001f) {
        return true;
    }
    float planeAngle = mm::acos(dist / range);
    mm::Vec3 normal;
    normal.setNeg(planeNormal);
    float coneAngle = mm::acos(normal.dot(coneDir));
    return planeAngle + angle >= coneAngle - 0.052;
}

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
