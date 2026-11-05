#include "layer/LayerAccManager.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/layer/LayerObjLayout.h"
#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccFontStyle.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccAction.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccDefObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjFont.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/navi/NvmshAcObjBaseDef.h"
#include "classes/navi/NvmshResMan.h"
#include "navi/NvmshAcMan.h"
#include "navi/NvmshResData.h"
#include "navi/NvmshUtil.h"
#include "mtl/MemManager.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/layer/LayerObjTopFont.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjSortDef.h"
#include "classes/layer/LayerObjSortFont.h"
#include "classes/layer/LayerObjSortTexObj.h"
#include "classes/layer/LayerObjSortPolyObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerTagStr.h"

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

namespace navi {

NvmshAcMan::~NvmshAcMan() {
    for (int i = 0; i < 256; i++) {
        m_objs[i]->~NvmshAcObjBaseDef();
    }
    if (m_gbl != nullptr) {
        delete m_gbl;
        m_gbl = nullptr;
    }
    if (m_objBuf != nullptr) {
        mtl::MemManager::deallocate(m_objBuf, 0, false);
        m_objBuf = nullptr;
    }
}

void NvmshAcMan::tail() { m_entryList = m_entryList == 0; }

NvmshAcObjBase* NvmshAcMan::createObj(mtl::ALLOC_HANDLE handle, NvmshResMan* resMan) {
    for (int i = 0; i < 256; i++) {
        NvmshAcObjBase* obj = m_objs[i];
        if (!(obj->m_flags & 1)) {
            obj->reset();
            obj->m_flags |= 1;
            m_entryLists[m_entryList].pushBack(obj);
            return m_objs[i];
        }
    }
    return nullptr;
}

void NvmshAcMan::releaseObj(NvmshAcObjBase* object) { object->m_request |= 1; }

void NvmshAcMan::update(NvmshResMan* resMan) {
    m_updateList = m_entryList == 0;
    NvmshAcObjBase* obj = m_entryLists[m_updateList].m_head;
    while (obj != nullptr) {
        NvmshAcObjBase* next = obj->m_next;
        m_activeList.pushBack(obj);
        obj = next;
    }
    m_entryLists[m_updateList].clear();
    objectUpdate(resMan);
}

void NvmshAcMan::objectUpdate(NvmshResMan* resMan) {
    NvmshAcObjBase* obj = m_activeList.m_head;
    if (resMan->m_flags & 4) {
        for (; obj != nullptr; obj = obj->m_next) {
            obj->m_status &= 0xFF4FE3E0;
        }
        obj = m_activeList.m_head;
    }
    bool canSearch = true;
    int searchNum = 0;
    while (obj != nullptr) {
        bool searched = false;
        if (obj->update(searched, resMan, canSearch)) {
            NvmshAcObjBase* next = obj->m_next;
            m_activeList.remove(obj);
            obj->reset();
            obj = next;
        } else {
            if (searched) {
                if (searchNum >= 23) {
                    canSearch = false;
                }
                searchNum++;
            }
            obj = obj->m_next;
        }
    }
}

void NvmshAcObjBase::setMeshNum(int num) { m_isMeshNum = num > 0; }

int NvmshAcObjBase::seachNaviMesh(_NaviTempColiResl& result, _NaviCalcResTbl* tbl, _NaviCalcResInfo* info) {
    NvmshColiResult coli;
    result.m_flags = 0;
    coli.m_tbl = tbl;
    coli.m_info = info;
    if (!seachNaviMesh(coli, 0)) {
        return 2;
    }
    result.m_mesh[0] = coli.m_hitMesh;
    result.m_pos[0].x = coli.m_hitPos.x;
    result.m_pos[0].y = coli.m_hitPos.y;
    result.m_pos[0].z = coli.m_hitPos.z;
    result.m_radiusSq[0] = coli.m_radiusSq;
    if (coli.m_isHit) {
        result.m_flags |= 1;
    }
    if (coli.m_isWayPoint) {
        result.m_flags |= 4;
    }
    if (!seachNaviMesh(coli, 1)) {
        return 3;
    }
    result.m_mesh[1] = coli.m_hitMesh;
    result.m_pos[1].x = coli.m_hitPos.x;
    result.m_pos[1].y = coli.m_hitPos.y;
    result.m_pos[1].z = coli.m_hitPos.z;
    result.m_radiusSq[1] = coli.m_radiusSq;
    if (coli.m_isHit) {
        result.m_flags |= 2;
    }
    if ((result.m_flags & 4) && !stockWayPointMesh(result, tbl)) {
        return 2;
    }
    return 6;
}

int NvmshAcObjBase::seachWideAreaNaviMesh(_NaviTempColiResl& result, _NaviCalcResTbl* tbl, _NaviCalcResInfo* info) {
    NvmshColiResult coli;
    result.m_flags = 0;
    coli.m_tbl = tbl;
    coli.m_info = info;
    if (!seachNaviMesh(coli, 0)) {
        return 2;
    }
    result.m_mesh[0] = coli.m_hitMesh;
    result.m_pos[0].x = coli.m_hitPos.x;
    result.m_pos[0].y = coli.m_hitPos.y;
    result.m_pos[0].z = coli.m_hitPos.z;
    result.m_radiusSq[0] = coli.m_radiusSq;
    if (coli.m_isHit) {
        result.m_flags |= 1;
    }
    if (coli.m_isWayPoint) {
        result.m_flags |= 4;
    }
    if (!seachWideAreaNaviMesh(coli, 1)) {
        return 3;
    }
    result.m_mesh[1] = coli.m_hitMesh;
    result.m_pos[1].x = coli.m_hitPos.x;
    result.m_pos[1].y = coli.m_hitPos.y;
    result.m_pos[1].z = coli.m_hitPos.z;
    result.m_radiusSq[1] = coli.m_radiusSq;
    if (coli.m_isHit) {
        result.m_flags |= 2;
    }
    if ((result.m_flags & 4) && !stockWayPointMesh(result, tbl)) {
        return 2;
    }
    return 6;
}

int NvmshAcObjBase::findPosRoot(_NaviCalcResTbl* tbl, _NaviCalcResInfo* info, const _NaviTempColiResl& result) {
    m_route50 = 0;
    m_route52 = 0;
    m_flag5E = 0;
    m_route54 = 0;
    m_route5A = 0;
    m_route5C = -1;
    if (result.m_mesh[0].m_id == result.m_mesh[1].m_id) {
        return 1;
    }
    NvmshAStarResult aStar;
    aStar.m_startPos = result.m_pos[0];
    aStar.m_goalPos = result.m_pos[1];
    aStar.m_start = result.m_mesh[0];
    aStar.m_goal = result.m_mesh[1];
    aStar.m_tbl = tbl;
    aStar.m_info = info;
    aStar.m_route = m_workCur;
    aStar.m_routeMax = (m_workSize - m_route56 * sizeof(short)) / sizeof(_NaviStMeshId);
    aStar.m_cells = m_readCells;
    NvmshUtilSeach seach;
    if (m_status & 0x20000) {
        seach.m_option0 = true;
    }
    if (m_status & 0x40000) {
        seach.m_option1 = true;
    }
    if (!seach.seachAStar(&aStar)) {
        return 4;
    }
    m_route52 = 0;
    m_route50 = aStar.m_routeNum;
    m_flag5E = aStar.m_count;
    m_route54 = 0;
    return 1;
}

// to length 1, or zero when shorter than 1e-6 (Vec3::normalize without its isZero test; the name is not the
// original's)
static inline void normalizeVec(mm::Vec3& vec) {
    float length = vec.length();
    if (length <= 1e-6f) {
        vec = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        vec.x = scale * vec.x;
        vec.y = scale * vec.y;
        vec.z = scale * vec.z;
    }
}

void NvmshAcObjBase::setMoveVec(const mm::Vec3& vec) {
    float dot = m_moveVec.x * vec.x + m_moveVec.z * vec.z;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71015E9CB0, with its guard)
    static const float turnCos = ::cosf(0.50265485f);
    if (dot < turnCos) {
        m_moveVec += vec * 0.25f;
        normalizeVec(m_moveVec);
    } else {
        m_moveVec = vec;
    }
}

void NvmshAcObjBase::calcTargetVecLine(const mm::Vec3& from, const mm::Vec3& to) {
    mm::Vec3 vec;
    vec.x = to.x - from.x;
    vec.y = to.y - from.y;
    vec.z = to.z - from.z;
    if (m_flags & 0x10) {
        if (::fabsf(vec.x) <= 0.001f && ::fabsf(vec.z) <= 0.001f) {
            vec = mm::Vec3(0.0f, 0.0f, 1.0f);
        } else {
            vec.y = 0.0f;
            normalizeVec(vec);
        }
    } else if (::fabsf(vec.x) <= 0.001f && ::fabsf(vec.z) <= 0.001f && ::fabsf(vec.y) <= 0.001f) {
        vec = mm::Vec3(0.0f, 0.0f, 1.0f);
    } else {
        normalizeVec(vec);
    }
    setMoveVec(vec);
}

void NvmshAcObjBase::createPosRootReadInfo(const _NaviCalcResTbl* tbl) {
    const NaviCalcGrid* info = tbl->m_info;
    unsigned int bits = 0;
    const _NaviStMeshId* id = &m_workCur[m_route52];
    for (int i = m_route52; i < m_route50; i++, id++) {
        NaviCalcGrid::Cell base = info->getBase();
        bits |= 1 << ((id->m_cellX - base.x) + (id->m_cellY - base.y) * 5);
    }
    int num = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (bits & (1 << (y * 5 + x))) {
                m_readCells[num].x = info->m_base.x + x;
                m_readCells[num].y = info->m_base.y + y;
                num++;
            }
        }
    }
    m_flag5E = num;
}

void NvmshAcObjBase::calcWayPointOptimization(_NaviCalcResTbl* tbl) {
    const _NvMhWayPoint* wayPoint = reinterpret_cast<const _NvMhWayPoint*>(tbl->m_treeBlocks[1]) + m_route5A;
    // every field of an end is compared with the route mesh's cell x
    const _NaviStMeshId* route = m_workCur;
    if (wayPoint->m_ends[0].m_cellX == route[0].m_cellX && wayPoint->m_ends[0].m_cellY == route[0].m_cellX &&
        wayPoint->m_ends[0].m_mesh == route[0].m_cellX) {
        if (!(wayPoint->m_ends[1].m_cellX == route[1].m_cellX && wayPoint->m_ends[1].m_cellY == route[1].m_cellX &&
              wayPoint->m_ends[1].m_mesh == route[1].m_cellX)) {
            return;
        }
    } else if (!(wayPoint->m_ends[0].m_cellX == route[1].m_cellX && wayPoint->m_ends[0].m_cellY == route[1].m_cellX &&
                 wayPoint->m_ends[0].m_mesh == route[1].m_cellX)) {
        return;
    }
    m_route52 = 1;
    createPosRootReadInfo(tbl);
}

void NvmshAcObjBaseDef::stateUpdate() {
    if (m_meshNum != m_isMeshNum) {
        m_meshNum = m_isMeshNum;
        m_status &= 0xFF4FE3E0;
    }
    if (m_flags & 8) {
        if (!(m_status & 0x8000)) {
            m_status = (m_status & 0xFF4F63E0) | 0x8000;
        }
    } else if (m_status & 0x8000) {
        m_status &= 0xFF4F63E0;
    }
    if (m_flags & 4) {
        if (!(m_status & 0x10000)) {
            m_status = (m_status & 0xFF4EE3E0) | 0x10000;
        }
    } else if (m_status & 0x10000) {
        m_status &= 0xFF4EE3E0;
    }
    if (m_flags & 0x20) {
        if (!(m_status & 0x20000)) {
            m_status = (m_status & 0xFF4DE3E0) | 0x20000;
        }
    } else if (m_status & 0x20000) {
        m_status &= 0xFF4DE3E0;
    }
    if (m_flags & 0x40) {
        if (!(m_status & 0x40000)) {
            m_status = (m_status & 0xFF4BE3E0) | 0x40000;
        }
    } else if (m_status & 0x40000) {
        m_status &= 0xFF4BE3E0;
    }
    if (m_status & 4) {
        float x = m_vec130.x - m_vec110.x;
        float y = m_vec130.y - m_vec110.y;
        float z = m_vec130.z - m_vec110.z;
        if (x * x + y * y + z * z >= 16.0f) {
            m_status &= 0xFF6FE3FF;
            m_flag5F = 0;
        }
    }
}

NvmshAcObjBaseGbl::~NvmshAcObjBaseGbl() {}

void NvmshAcObjBaseGbl::release() { reset(); }

const mm::Vec3& NvmshAcObjBase::getMoveVec() const { return m_moveVec; }

void NvmshAcObjBase::setBeginPos(const mm::Vec3& pos) { m_beginPos = pos; }

void NvmshAcObjBase::setEndPos(const mm::Vec3& pos) { m_endPos = pos; }

void NvmshAcObjBase::setBeginRadius(float radius) { m_beginRadius = radius; }

void NvmshAcObjBase::setEndRadius(float radius) { m_endRadius = radius; }

void NvmshAcObjBase::setBeginSeachRadius(float radius) { m_beginSeachRadius = radius; }

void NvmshAcObjBase::setEndSeachRadius(float radius) { m_endSeachRadius = radius; }

void NvmshAcObjBase::setBeginHeight(float a, float b) {
    m_beginHeight[0] = a;
    m_beginHeight[1] = b;
}

void NvmshAcObjBase::setEndHeight(float a, float b) {
    m_endHeight[0] = a;
    m_endHeight[1] = b;
}

int NvmshAcObjBase::getMeshNum() const { return m_meshNum; }

void NvmshAcObjBase::setMoveSpd(float spd) { m_moveSpd = spd; }

NvmshAcObjBaseDef::~NvmshAcObjBaseDef() { release(); }

void NvmshAcObjBaseDef::release() { m_flags = 0; }


bool NvmshAcObjBaseGbl::update(bool& searched, NvmshResMan* resMan, bool canSearch) {
    m_meshNum = m_isMeshNum;
    if (m_request & 1) {
        m_request = 0;
        return true;
    }
    return false;
}

}  // namespace navi
