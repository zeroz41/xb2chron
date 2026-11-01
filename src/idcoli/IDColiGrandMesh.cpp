#include "idcoli/IDColiGrandObj.h"
#include "classes/idcoli/IDColiObjGrand.h"
#include "classes/ml/WorkCpu.h"
#include "classes/navi/NvmshResMan.h"
#include "classes/navi/NvmshManager.h"
#include "navi/NvmshAcMan.h"
#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiInputUtil.h"
#include "idcoli/IDColiResult.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiGrandMesh.h"
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
#include "idcoli/IDColiPrimitive.h"
#include "mm/Math.h"
#include "idcoli/IDColiTreeTop.h"
#include "idcoli/IDColiUtilColi.h"
#include "idcoli/IDColiShapeWork.h"
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
#include "classes/idcoli/IDColiManager.h"
#include "classes/idcoli/IDColiObjGrand.h"
#include "classes/ml/WorkCpu.h"
#include "mtl/MemManager.h"
#include "classes/idcoli/IDColiObjGrdChar.h"
#include "idcoli/IDColiResult.h"
#include "classes/fw/ColiCheckCallback.h"
#include "idcoli/IDColiUtilTreeAcc.h"

namespace idcoli {

bool IDColiGrandMesh::lenghtLine(float length) { return length >= 0.0f && length <= 1.0f; }

bool IDColiGrandMesh::lenghtRay(float length) {
    if (m_input->m_lengthMin <= length) {
        return m_input->m_lengthMax >= length;
    }
    return false;
}

bool IDColiGrandMesh::lenghtSphere(float length) { return mm::fabs(length) <= m_input->m_lengthMax; }

bool IDColiGrandMesh::lenghtWallSphere(float length) {
    if (length >= 0.0f) {
        return m_input->m_lengthMax > length;
    }
    return false;
}

void IDColiGrandMesh::stockNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length) {
    if (m_result->m_nearLength > length) {
        m_result->m_near.m_pos = arg.m_pos;
        m_result->m_near.m_normal = arg.m_normal;
        m_result->m_nearLength = length;
        m_result->m_near.m_poli = arg.m_poli;
        m_result->m_nearHit = true;
        m_result->m_nearObj = m_result->m_obj;
        (this->*m_vecotr)(m_result->m_near, poli);
    }
}

void IDColiGrandMesh::stockSecNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length) {
    if (length < 0.0f) {
        if (m_result->m_secNearLength <= length) {
            m_result->m_secNear.m_pos = arg.m_pos;
            m_result->m_secNear.m_normal = arg.m_normal;
            m_result->m_secNearLength = length;
            m_result->m_secNear.m_poli = arg.m_poli;
            m_result->m_secNearHit = true;
            m_result->m_secNearObj = m_result->m_obj;
            (this->*m_vecotr)(m_result->m_secNear, poli);
        }
    } else {
        stockNear(arg, poli, length);
    }
}

void IDColiGrandMesh::stockTbl(IDColiCallArg& arg, const IDCmfPoliData* poli, float) {
    (this->*m_vecotr)(arg, poli);
    if (m_result->m_tblMax > m_result->m_tblNum) {
        if (m_result->m_tblPos) m_result->m_tblPos[m_result->m_tblNum] = arg.m_pos;
        if (m_result->m_tblNormal) m_result->m_tblNormal[m_result->m_tblNum] = arg.m_normal;
        if (m_result->m_tblVector) m_result->m_tblVector[m_result->m_tblNum] = arg.m_vector;
        if (m_result->m_tblPoli) m_result->m_tblPoli[m_result->m_tblNum] = arg.m_poli;
        m_result->m_nearHit = true;
        m_result->m_tblNum++;
    }
    if (m_result->m_callback) m_result->m_callback->coli_param_callback(m_result->m_obj, arg);
}

void IDColiGrandMesh::vecotrNon(IDColiCallArg&, const IDCmfPoliData*) {}

void IDColiGrandMesh::vecotrDef(IDColiCallArg& arg, const IDCmfPoliData* poli) {
    if (!(arg.m_poli->m_flags & 0x80)) {
        arg.m_vector = mm::Vec3::zero;
        return;
    }
    const unsigned short* index =
        reinterpret_cast<const unsigned short*>(reinterpret_cast<const char*>(m_work->m_data) + poli->m_offset);
    const mm::Vec3NA& vector = m_work->m_vectors[poli->m_table][index[poli->m_num * 2 + 2]];
    arg.m_vector.x = vector.x;
    arg.m_vector.y = vector.y;
    arg.m_vector.z = vector.z;
}

void IDColiGrandMesh::vecotrInst(IDColiCallArg& arg, const IDCmfPoliData* poli) {
    if (!(arg.m_poli->m_flags & 0x80)) {
        arg.m_vector = mm::Vec3::zero;
        return;
    }
    const unsigned short* index =
        reinterpret_cast<const unsigned short*>(reinterpret_cast<const char*>(m_work->m_data) + poli->m_offset);
    const mm::Vec3NA& vector = m_work->m_vectors[poli->m_table][index[poli->m_num * 2 + 2]];
    float x = vector.x;
    float y = vector.y;
    float z = vector.z;
    arg.m_vector.x = x * m_instPosData->m_matrix.m[0][0] + y * m_instPosData->m_matrix.m[0][1] +
                     z * m_instPosData->m_matrix.m[0][2];
    arg.m_vector.y = x * m_instPosData->m_matrix.m[1][0] + y * m_instPosData->m_matrix.m[1][1] +
                     z * m_instPosData->m_matrix.m[1][2];
    arg.m_vector.z = x * m_instPosData->m_matrix.m[2][0] + y * m_instPosData->m_matrix.m[2][1] +
                     z * m_instPosData->m_matrix.m[2][2];
}

IDColiGrandObj::IDColiGrandObj(wrkIDCmfWork* work) {
    m_work = work;
    m_instPosData = nullptr;
}

IDColiGrandObj::~IDColiGrandObj() {}

bool IDColiGrandObj::testLine(IDColiResult& result, const IDColiInput& input) {
    m_result = &result;
    m_input = &input;
    m_mesh = &IDColiGrandMesh::meshLine;
    m_isAaBb = &IDColiGrandTree::isLineAaBb;
    m_instHit = &IDColiGrandTree::instLineHit;
    m_lenght = &IDColiGrandMesh::lenghtLine;
    if (result.m_type == 0) {
        m_treeHit = &IDColiGrandTree::treeHitEnd;
        m_stock = nullptr;
        m_stockInst = nullptr;
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
        return coliCallCheck(&IDColiGrandTree::instLineHitParts);
    }
    m_treeHit = &IDColiGrandTree::treeHitDef;
    if (result.m_type == 2) {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstTbl;
        else m_stock = &IDColiGrandMesh::stockTbl;
        m_stockInst = &IDColiGrandMesh::stockInstTbl;
    } else {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstNear;
        else m_stock = &IDColiGrandMesh::stockNear;
        m_stockInst = &IDColiGrandMesh::stockInstNear;
    }
    if (result.m_calcVector) {
        if (m_instPosData) m_vecotr = &IDColiGrandMesh::vecotrInst;
        else m_vecotr = &IDColiGrandMesh::vecotrDef;
        m_vecotrInst = &IDColiGrandMesh::vecotrInst;
    } else {
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
    }
    return coliCallResl(&IDColiGrandTree::instLineHitParts);
}

bool IDColiGrandTree::isLineAaBb(const float* max, const float* min) {
    if (isAaBbToAaBb(max, min)) return true;
    const IDColiInput* input = m_input;
    mm::Vec3 half = (mm::Vec3(max[0], max[1], max[2]) - mm::Vec3(min[0], min[1], min[2])) * 0.5f;
    mm::Vec3 center = mm::Vec3(min[0], min[1], min[2]) + half;
    mm::Vec3 d = input->m_lineCenter - center;
    const mm::Vec3& w = input->m_lineHalf;
    const mm::Vec3& a = input->m_lineHalfAbs;
    if (mm::fabs(d.y * w.z - d.z * w.y) > half.y * a.z + half.z * a.y) return true;
    if (mm::fabs(d.z * w.x - d.x * w.z) > half.x * a.z + half.z * a.x) return true;
    return mm::fabs(d.x * w.y - d.y * w.x) > half.x * a.y + half.y * a.x;
}

bool IDColiGrandTree::instLineHit(unsigned int index) {
    return instLineHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandObj::coliCallCheck(bool (IDColiGrandTree::*parts)(const IDCmfPosData* posData,
                                                                    const IDCmfPosInfo* posInfo)) {
    if (m_work->m_instNum == 0) {
        if ((this->*m_treeHit)(0)) return true;
    } else {
        const wrkIDCmfWork::Inst* inst = m_work->m_insts;
        for (int i = 0; i < m_work->m_instNum; i++, inst++) {
            if (inst->m_id != 0 && IDColiManager::sys()->isGblId(inst->m_id)) continue;
            if ((inst->m_flags & 1) && (inst->m_flags >> 8) != IDColiManager::sys()->m_subNum) continue;
            if ((this->*m_treeHit)(inst->m_index)) return true;
        }
    }
    if (m_work->m_moveObjNum != 0) {
        IDColiUtilTreeAcc acc(m_work->m_treeTops[m_work->m_bank]);
        acc.startTreeAaBbMode(m_input->m_max, m_input->m_min);
        for (ColiLinkList<IDColiTreeObj>* list = acc.nextList(); list != nullptr; list = acc.nextList()) {
            for (IDColiTreeObj* node = list->m_head; node != nullptr; node = node->m_next) {
                IDColiGrdMoveObj* obj = static_cast<IDColiGrdMoveObj*>(node->m_owner);
                m_result->m_obj = obj->m_userData;
                if ((this->*parts)(&obj->m_posData, &obj->m_posInfo)) return true;
            }
        }
    }
    return false;
}

bool IDColiGrandTree::instLineHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo) {
    if (IDColiManager::sys()->isGblId(posInfo->m_id)) return false;
    if (isLineAaBb(&posData->m_max.x, &posData->m_min.x)) return false;
    const IDColiInput* input = m_input;
    if (input->m_instSizeMin != 0.0f) {
        mm::Vec3 half = (posData->m_max - posData->m_min) * 0.5f;
        if (half.dot(half) <= input->m_instSizeMin) return false;
    }
    const IDCmfPosData* instPosData = m_instPosData;
    void (IDColiGrandMesh::*stock)(IDColiCallArg& arg, const IDCmfPoliData* poli, float length) = m_stock;
    void (IDColiGrandMesh::*vecotr)(IDColiCallArg& arg, const IDCmfPoliData* poli) = m_vecotr;
    IDColiInput instInput;
    IDColiInputUtil::getLine(instInput, *input, posData, false);
    m_input = &instInput;
    m_instPosData = posData;
    m_stock = m_stockInst;
    m_vecotr = m_vecotrInst;
    bool hit = (this->*m_treeHit)(m_work->m_trees[posInfo->m_tree].m_index);
    m_input = input;
    m_instPosData = instPosData;
    m_stock = stock;
    m_vecotr = vecotr;
    return hit;
}

bool IDColiGrandObj::coliCallResl(bool (IDColiGrandTree::*parts)(const IDCmfPosData* posData,
                                                                   const IDCmfPosInfo* posInfo)) {
    bool hit = false;
    if (m_work->m_instNum != 0) {
        const wrkIDCmfWork::Inst* inst = m_work->m_insts;
        for (int i = 0; i < m_work->m_instNum; i++, inst++) {
            if (inst->m_id != 0 && IDColiManager::sys()->isGblId(inst->m_id)) continue;
            if ((inst->m_flags & 1) && (inst->m_flags >> 8) != IDColiManager::sys()->m_subNum) continue;
            hit |= (this->*m_treeHit)(inst->m_index);
        }
    } else {
        hit = (this->*m_treeHit)(0);
    }
    if (m_work->m_moveObjNum != 0) {
        IDColiUtilTreeAcc acc(m_work->m_treeTops[m_work->m_bank]);
        acc.startTreeAaBbMode(m_input->m_max, m_input->m_min);
        for (ColiLinkList<IDColiTreeObj>* list = acc.nextList(); list != nullptr; list = acc.nextList()) {
            for (IDColiTreeObj* node = list->m_head; node != nullptr; node = node->m_next) {
                IDColiGrdMoveObj* obj = static_cast<IDColiGrdMoveObj*>(node->m_owner);
                m_result->m_obj = obj->m_userData;
                hit |= (this->*parts)(&obj->m_posData, &obj->m_posInfo);
            }
        }
    }
    return hit;
}

bool IDColiGrandObj::testRay(IDColiResult& result, const IDColiInput& input) {
    m_result = &result;
    m_input = &input;
    m_mesh = &IDColiGrandMesh::meshLine;
    m_isAaBb = &IDColiGrandTree::isLineAaBb;
    m_instHit = &IDColiGrandTree::instRayHit;
    m_lenght = &IDColiGrandMesh::lenghtRay;
    if (result.m_type == 0) {
        m_treeHit = &IDColiGrandTree::treeHitEnd;
        m_stock = nullptr;
        m_stockInst = nullptr;
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
        return coliCallCheck(&IDColiGrandTree::instRayHitParts);
    }
    m_treeHit = &IDColiGrandTree::treeHitDef;
    if (result.m_type == 2) {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstTbl;
        else m_stock = &IDColiGrandMesh::stockTbl;
        m_stockInst = &IDColiGrandMesh::stockInstTbl;
    } else {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstSecNear;
        else m_stock = &IDColiGrandMesh::stockSecNear;
        m_stockInst = &IDColiGrandMesh::stockInstSecNear;
    }
    if (result.m_calcVector) {
        if (m_instPosData) m_vecotr = &IDColiGrandMesh::vecotrInst;
        else m_vecotr = &IDColiGrandMesh::vecotrDef;
        m_vecotrInst = &IDColiGrandMesh::vecotrInst;
    } else {
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
    }
    return coliCallResl(&IDColiGrandTree::instRayHitParts);
}

bool IDColiGrandTree::instRayHit(unsigned int index) {
    return instRayHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandTree::instRayHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo) {
    if (IDColiManager::sys()->isGblId(posInfo->m_id)) return false;
    if (isLineAaBb(&posData->m_max.x, &posData->m_min.x)) return false;
    const IDColiInput* input = m_input;
    if (input->m_instSizeMin != 0.0f) {
        mm::Vec3 half = (posData->m_max - posData->m_min) * 0.5f;
        if (half.dot(half) <= input->m_instSizeMin) return false;
    }
    const IDCmfPosData* instPosData = m_instPosData;
    void (IDColiGrandMesh::*stock)(IDColiCallArg& arg, const IDCmfPoliData* poli, float length) = m_stock;
    void (IDColiGrandMesh::*vecotr)(IDColiCallArg& arg, const IDCmfPoliData* poli) = m_vecotr;
    IDColiInput instInput;
    IDColiInputUtil::getRay(instInput, *input, posData, false);
    m_input = &instInput;
    m_instPosData = posData;
    m_stock = m_stockInst;
    m_vecotr = m_vecotrInst;
    bool hit = (this->*m_treeHit)(m_work->m_trees[posInfo->m_tree].m_index);
    m_input = input;
    m_instPosData = instPosData;
    m_stock = stock;
    m_vecotr = vecotr;
    return hit;
}

bool IDColiGrandObj::testSphere(IDColiResult& result, const IDColiInput& input, bool wall) {
    m_result = &result;
    m_input = &input;
    m_mesh = &IDColiGrandMesh::meshSphere;
    m_instHit = &IDColiGrandTree::instSphereHit;
    m_isAaBb = &IDColiGrandTree::isAaBbToAaBb;
    m_lenght = wall ? &IDColiGrandMesh::lenghtWallSphere : &IDColiGrandMesh::lenghtSphere;
    if (result.m_type == 0) {
        m_treeHit = &IDColiGrandTree::treeHitEnd;
        m_stock = nullptr;
        m_stockInst = nullptr;
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
        return coliCallCheck(&IDColiGrandTree::instSphereHitParts);
    }
    m_treeHit = &IDColiGrandTree::treeHitDef;
    if (result.m_type == 2) {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstTbl;
        else m_stock = &IDColiGrandMesh::stockTbl;
        m_stockInst = &IDColiGrandMesh::stockInstTbl;
    } else {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstNear;
        else m_stock = &IDColiGrandMesh::stockNear;
        m_stockInst = &IDColiGrandMesh::stockInstNear;
    }
    if (result.m_calcVector) {
        if (m_instPosData) m_vecotr = &IDColiGrandMesh::vecotrInst;
        else m_vecotr = &IDColiGrandMesh::vecotrDef;
        m_vecotrInst = &IDColiGrandMesh::vecotrInst;
    } else {
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
    }
    return coliCallResl(&IDColiGrandTree::instSphereHitParts);
}

bool IDColiGrandTree::instSphereHit(unsigned int index) {
    return instSphereHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandTree::instSphereHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo) {
    if (IDColiManager::sys()->isGblId(posInfo->m_id)) return false;
    if (isAaBbToAaBb(&posData->m_max.x, &posData->m_min.x)) return false;
    const IDColiInput* input = m_input;
    if (input->m_instSizeMin != 0.0f) {
        mm::Vec3 half = (posData->m_max - posData->m_min) * 0.5f;
        if (half.dot(half) <= input->m_instSizeMin) return false;
    }
    const IDCmfPosData* instPosData = m_instPosData;
    void (IDColiGrandMesh::*stock)(IDColiCallArg& arg, const IDCmfPoliData* poli, float length) = m_stock;
    void (IDColiGrandMesh::*vecotr)(IDColiCallArg& arg, const IDCmfPoliData* poli) = m_vecotr;
    IDColiInput instInput;
    IDColiInputUtil::getSphere(instInput, *input, posData, false);
    m_stock = m_stockInst;
    m_vecotr = m_vecotrInst;
    m_input = &instInput;
    m_instPosData = posData;
    bool hit = (this->*m_treeHit)(m_work->m_trees[posInfo->m_tree].m_index);
    m_input = input;
    m_instPosData = instPosData;
    m_stock = stock;
    m_vecotr = vecotr;
    return hit;
}

bool IDColiGrandObj::testCapsule(IDColiResult& result, const IDColiInput& input, bool wall) {
    m_result = &result;
    m_input = &input;
    m_mesh = &IDColiGrandMesh::meshCapsule;
    m_isAaBb = &IDColiGrandTree::isAaBbToAaBb;
    m_instHit = &IDColiGrandTree::instCapsuleHit;
    m_lenght = &IDColiGrandMesh::lenghtLine;
    m_lenghtSub = wall ? &IDColiGrandMesh::lenghtWallSphere : &IDColiGrandMesh::lenghtSphere;
    if (result.m_type == 0) {
        m_treeHit = &IDColiGrandTree::treeHitEnd;
        m_stock = nullptr;
        m_stockInst = nullptr;
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
        return coliCallCheck(&IDColiGrandTree::instCapsuleHitParts);
    }
    m_treeHit = &IDColiGrandTree::treeHitDef;
    if (result.m_type == 2) {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstTbl;
        else m_stock = &IDColiGrandMesh::stockTbl;
        m_stockInst = &IDColiGrandMesh::stockInstTbl;
    } else {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstNear;
        else m_stock = &IDColiGrandMesh::stockNear;
        m_stockInst = &IDColiGrandMesh::stockInstNear;
    }
    if (result.m_calcVector) {
        if (m_instPosData) m_vecotr = &IDColiGrandMesh::vecotrInst;
        else m_vecotr = &IDColiGrandMesh::vecotrDef;
        m_vecotrInst = &IDColiGrandMesh::vecotrInst;
    } else {
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
    }
    return coliCallResl(&IDColiGrandTree::instCapsuleHitParts);
}

bool IDColiGrandTree::instCapsuleHit(unsigned int index) {
    return instCapsuleHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandTree::instCapsuleHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo) {
    if (IDColiManager::sys()->isGblId(posInfo->m_id)) return false;
    if (isAaBbToAaBb(&posData->m_max.x, &posData->m_min.x)) return false;
    const IDColiInput* input = m_input;
    if (input->m_instSizeMin != 0.0f) {
        mm::Vec3 half = (posData->m_max - posData->m_min) * 0.5f;
        if (half.dot(half) <= input->m_instSizeMin) return false;
    }
    const IDCmfPosData* instPosData = m_instPosData;
    void (IDColiGrandMesh::*stock)(IDColiCallArg& arg, const IDCmfPoliData* poli, float length) = m_stock;
    void (IDColiGrandMesh::*vecotr)(IDColiCallArg& arg, const IDCmfPoliData* poli) = m_vecotr;
    IDColiInput instInput;
    IDColiInputUtil::getCapsule(instInput, *input, posData, false);
    m_input = &instInput;
    m_instPosData = posData;
    m_stock = m_stockInst;
    m_vecotr = m_vecotrInst;
    bool hit = (this->*m_treeHit)(m_work->m_trees[posInfo->m_tree].m_index);
    m_input = input;
    m_instPosData = instPosData;
    m_stock = stock;
    m_vecotr = vecotr;
    return hit;
}

bool IDColiGrandTree::isAaBbToAaBb(const float* max, const float* min) {
    if (m_input->m_max.x < min[0]) return true;
    if (m_input->m_min.x > max[0]) return true;
    if (m_input->m_max.z < min[2]) return true;
    if (m_input->m_min.z > max[2]) return true;
    if (m_input->m_min.y > max[1]) return true;
    return m_input->m_max.y < min[1];
}

bool IDColiGrandObj::testMoveSphere(IDColiResult& result, const IDColiInput& input, bool wall) {
    m_result = &result;
    m_input = &input;
    m_mesh = &IDColiGrandMesh::meshSphere;
    m_instHit = &IDColiGrandTree::instSphereHit;
    m_isAaBb = &IDColiGrandTree::isAaBbToAaBb;
    m_lenght = &IDColiGrandMesh::lenghtWallSphere;
    m_treeHit = &IDColiGrandTree::treeHitDef;
    if (result.m_type == 2) {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstTbl;
        else m_stock = &IDColiGrandMesh::stockTbl;
        m_stockInst = &IDColiGrandMesh::stockInstTbl;
    } else {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstNear;
        else m_stock = &IDColiGrandMesh::stockNear;
        m_stockInst = &IDColiGrandMesh::stockInstNear;
    }
    if (result.m_calcVector) {
        if (m_instPosData) m_vecotr = &IDColiGrandMesh::vecotrInst;
        else m_vecotr = &IDColiGrandMesh::vecotrDef;
        m_vecotrInst = &IDColiGrandMesh::vecotrInst;
    } else {
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
    }
    return coliMoveCallResl(&IDColiGrandTree::instSphereHitParts, wall);
}

bool IDColiGrandObj::testMoveCapsule(IDColiResult& result, const IDColiInput& input, bool wall) {
    m_result = &result;
    m_input = &input;
    m_mesh = &IDColiGrandMesh::meshCapsule;
    m_isAaBb = &IDColiGrandTree::isAaBbToAaBb;
    m_instHit = &IDColiGrandTree::instCapsuleHit;
    m_lenght = &IDColiGrandMesh::lenghtLine;
    m_lenghtSub = &IDColiGrandMesh::lenghtWallSphere;
    m_treeHit = &IDColiGrandTree::treeHitDef;
    if (result.m_type == 2) {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstTbl;
        else m_stock = &IDColiGrandMesh::stockTbl;
        m_stockInst = &IDColiGrandMesh::stockInstTbl;
    } else {
        if (m_instPosData) m_stock = &IDColiGrandMesh::stockInstNear;
        else m_stock = &IDColiGrandMesh::stockNear;
        m_stockInst = &IDColiGrandMesh::stockInstNear;
    }
    if (result.m_calcVector) {
        if (m_instPosData) m_vecotr = &IDColiGrandMesh::vecotrInst;
        else m_vecotr = &IDColiGrandMesh::vecotrDef;
        m_vecotrInst = &IDColiGrandMesh::vecotrInst;
    } else {
        m_vecotr = &IDColiGrandMesh::vecotrNon;
        m_vecotrInst = &IDColiGrandMesh::vecotrNon;
    }
    return coliMoveCallResl(&IDColiGrandTree::instCapsuleHitParts, wall);
}

void IDColiGrdMoveObj::setMat(const mm::Mat44& matrix) {
    m_mats[IDColiManager::s_nStkIdx] = matrix;
    m_matRequest |= 1 << IDColiManager::s_nStkIdx;
}

IDColiObjGrand::IDColiObjGrand() {
    m_work.m_memBlock = nullptr;
    m_type = 3;  // a ground (fw::ColiObject's isGrand tests 3)
}

IDColiObjGrand::~IDColiObjGrand() {
    if (m_work.m_memBlock) {
        if (m_work.m_treeTops[0]) m_work.m_treeTops[0]->~IDColiTreeTop();
        if (m_work.m_treeTops[1]) m_work.m_treeTops[1]->~IDColiTreeTop();
        if (m_work.m_memBlock) {
            mtl::MemManager::deallocate(m_work.m_memBlock, 0, false);
            m_work.m_memBlock = nullptr;
        }
    }
}

void IDColiObjGrand::update() {
    if (m_work.m_moveObjNum != 0) {
        int bank = m_work.m_bank == 0;
        m_work.m_treeTops[bank]->begin();
        for (int i = 0; i < m_work.m_moveObjNum; i++) {
            m_work.m_moveObjs[i].update();
            m_work.m_treeTops[bank]->setupTreeList(&m_work.m_moveObjs[i].m_treeObjs[bank],
                                                   m_work.m_moveObjs[i].m_posData.m_max,
                                                   m_work.m_moveObjs[i].m_posData.m_min);
        }
        m_work.m_treeTops[bank]->end();
        m_work.m_bank = bank;
    }
}

void IDColiObjGrand::getGrandAABB(mm::Vec3& max, mm::Vec3& min) const {
    const wrkIDCmfWork::Header* data = m_work.m_data;
    long offset;
    if (data->m_flags & 2) {
        offset = data->m_boxOffset;
    } else {
        offset = data->m_size - 0x28L;
    }
    const wrkIDCmfWork::Box* box =
        reinterpret_cast<const wrkIDCmfWork::Box*>(reinterpret_cast<const char*>(data) + offset);
    float x = box->m_max[0];
    float y = box->m_max[1];
    float z = box->m_max[2];
    max.x = max.x > x ? max.x : x;
    max.y = max.y > y ? max.y : y;
    max.z = max.z > z ? max.z : z;
    x = box->m_min[0];
    y = box->m_min[1];
    z = box->m_min[2];
    min.x = min.x < x ? min.x : x;
    min.y = min.y < y ? min.y : y;
    min.z = min.z < z ? min.z : z;
}

IDColiObjGrdChar::IDColiObjGrdChar() {
    m_partNum = 0;
    m_parts = nullptr;
    m_owner = nullptr;
    m_memBlock = nullptr;
    m_max = mm::Vec3(1.0f, 1.0f, 1.0f);
    m_min = mm::Vec3(-1.0f, -1.0f, -1.0f);
}

IDColiObjGrdChar::~IDColiObjGrdChar() {
    if (m_partNum != 0) {
        for (int i = 0; i < m_partNum; i++) {
            m_parts[i].m_grand->~IDColiObjGrand();
        }
        m_partNum = 0;
        m_parts = nullptr;
        if (m_memBlock) {
            mtl::MemManager::deallocate(m_memBlock, 0, false);
            m_memBlock = nullptr;
        }
    }
}

void IDColiObjGrdChar::update() {
    m_max = mm::Vec3(-1000000.0f, -1000000.0f, -1000000.0f);
    m_min = mm::Vec3(1000000.0f, 1000000.0f, 1000000.0f);
    for (int i = 0; i < m_partNum; i++) {
        const Part& part = m_parts[i];
        if (m_max.x < part.m_posData.m_max.x) m_max.x = part.m_posData.m_max.x;
        if (m_min.x > part.m_posData.m_min.x) m_min.x = part.m_posData.m_min.x;
        if (m_max.y < part.m_posData.m_max.y) m_max.y = part.m_posData.m_max.y;
        if (m_min.y > part.m_posData.m_min.y) m_min.y = part.m_posData.m_min.y;
        if (m_max.z < part.m_posData.m_max.z) m_max.z = part.m_posData.m_max.z;
        if (m_min.z > part.m_posData.m_min.z) m_min.z = part.m_posData.m_min.z;
    }
}


bool IDColiObjGrdChar::testLine(IDColiResult& result, const IDColiInput& input) {
    if ((m_owner->m_flags & 0x80) || result.m_skipObj == m_owner || (result.m_ignoreMaterial & m_owner->m_materialBit)) {
        return false;
    }
    if (m_max.x < input.m_min.x || m_min.x > input.m_max.x) return false;
    if (m_max.z < input.m_min.z || m_min.z > input.m_max.z) return false;
    if (m_max.y < input.m_min.y || m_min.y > input.m_max.y) return false;
    bool hit = false;
    bool found = false;
    for (int i = 0; i < m_partNum; i++) {
        const IDCmfPosData* posData = &m_parts[i].m_posData;
        IDColiObjGrand* grand = m_parts[i].m_grand;
        int type = result.m_type;
        bool partHit;
        if (grand->m_flags & 0x80) {
            partHit = false;
        } else {
            IDColiInput partInput;
            IDColiGrandObj obj(&grand->m_work);
            obj.m_instPosData = posData;
            IDColiInputUtil::getLine(partInput, input, posData, false);
            partHit = obj.testLine(result, partInput);
        }
        if (type == 0) {
            if (partHit) {
                found = true;
                break;
            }
        } else {
            hit |= partHit;
        }
    }
    return hit | found;
}

bool IDColiObjGrdChar::testRay(IDColiResult& result, const IDColiInput& input) {
    if ((m_owner->m_flags & 0x80) || result.m_skipObj == m_owner || (result.m_ignoreMaterial & m_owner->m_materialBit)) {
        return false;
    }
    if (m_max.x < input.m_min.x || m_min.x > input.m_max.x) return false;
    if (m_max.z < input.m_min.z || m_min.z > input.m_max.z) return false;
    if (m_max.y < input.m_min.y || m_min.y > input.m_max.y) return false;
    bool hit = false;
    bool found = false;
    for (int i = 0; i < m_partNum; i++) {
        const IDCmfPosData* posData = &m_parts[i].m_posData;
        IDColiObjGrand* grand = m_parts[i].m_grand;
        int type = result.m_type;
        bool partHit;
        if (grand->m_flags & 0x80) {
            partHit = false;
        } else {
            IDColiInput partInput;
            IDColiGrandObj obj(&grand->m_work);
            obj.m_instPosData = posData;
            IDColiInputUtil::getRay(partInput, input, posData, false);
            partHit = obj.testRay(result, partInput);
        }
        if (type == 0) {
            if (partHit) {
                found = true;
                break;
            }
        } else {
            hit |= partHit;
        }
    }
    return hit | found;
}

bool IDColiObjGrdChar::testSphere(IDColiResult& result, const IDColiInput& input) {
    if ((m_owner->m_flags & 0x80) || result.m_skipObj == m_owner || (result.m_ignoreMaterial & m_owner->m_materialBit)) {
        return false;
    }
    if (m_max.x < input.m_min.x || m_min.x > input.m_max.x) return false;
    if (m_max.z < input.m_min.z || m_min.z > input.m_max.z) return false;
    if (m_max.y < input.m_min.y || m_min.y > input.m_max.y) return false;
    bool hit = false;
    bool found = false;
    for (int i = 0; i < m_partNum; i++) {
        const IDCmfPosData* posData = &m_parts[i].m_posData;
        IDColiObjGrand* grand = m_parts[i].m_grand;
        int type = result.m_type;
        bool partHit;
        if (grand->m_flags & 0x80) {
            partHit = false;
        } else {
            IDColiInput partInput;
            IDColiGrandObj obj(&grand->m_work);
            obj.m_instPosData = posData;
            IDColiInputUtil::getSphere(partInput, input, posData, false);
            partHit = obj.testSphere(result, partInput, false);
        }
        if (type == 0) {
            if (partHit) {
                found = true;
                break;
            }
        } else {
            hit |= partHit;
        }
    }
    return hit | found;
}

bool IDColiObjGrdChar::testCapsule(IDColiResult& result, const IDColiInput& input) {
    if ((m_owner->m_flags & 0x80) || result.m_skipObj == m_owner || (result.m_ignoreMaterial & m_owner->m_materialBit)) {
        return false;
    }
    if (m_max.x < input.m_min.x || m_min.x > input.m_max.x) return false;
    if (m_max.z < input.m_min.z || m_min.z > input.m_max.z) return false;
    if (m_max.y < input.m_min.y || m_min.y > input.m_max.y) return false;
    bool hit = false;
    bool found = false;
    for (int i = 0; i < m_partNum; i++) {
        const IDCmfPosData* posData = &m_parts[i].m_posData;
        IDColiObjGrand* grand = m_parts[i].m_grand;
        int type = result.m_type;
        bool partHit;
        if (grand->m_flags & 0x80) {
            partHit = false;
        } else {
            IDColiInput partInput;
            IDColiGrandObj obj(&grand->m_work);
            obj.m_instPosData = posData;
            IDColiInputUtil::getCapsule(partInput, input, posData, false);
            partHit = obj.testCapsule(result, partInput, false);
        }
        if (type == 0) {
            if (partHit) {
                found = true;
                break;
            }
        } else {
            hit |= partHit;
        }
    }
    return hit | found;
}

bool IDColiObjGrdChar::testWallSphere(IDColiResult& result, const IDColiInput& input) {
    if ((m_owner->m_flags & 0x80) || result.m_skipObj == m_owner || (result.m_ignoreMaterial & m_owner->m_materialBit)) {
        return false;
    }
    if (m_max.x < input.m_min.x || m_min.x > input.m_max.x) return false;
    if (m_max.z < input.m_min.z || m_min.z > input.m_max.z) return false;
    if (m_max.y < input.m_min.y || m_min.y > input.m_max.y) return false;
    bool hit = false;
    bool found = false;
    for (int i = 0; i < m_partNum; i++) {
        const IDCmfPosData* posData = &m_parts[i].m_posData;
        IDColiObjGrand* grand = m_parts[i].m_grand;
        int type = result.m_type;
        bool partHit;
        if (grand->m_flags & 0x80) {
            partHit = false;
        } else {
            IDColiInput partInput;
            IDColiGrandObj obj(&grand->m_work);
            obj.m_instPosData = posData;
            IDColiInputUtil::getSphere(partInput, input, posData, false);
            partHit = obj.testSphere(result, partInput, true);
        }
        if (type == 0) {
            if (partHit) {
                found = true;
                break;
            }
        } else {
            hit |= partHit;
        }
    }
    return hit | found;
}

bool IDColiObjGrdChar::testWallCapsule(IDColiResult& result, const IDColiInput& input) {
    if ((m_owner->m_flags & 0x80) || result.m_skipObj == m_owner || (result.m_ignoreMaterial & m_owner->m_materialBit)) {
        return false;
    }
    if (m_max.x < input.m_min.x || m_min.x > input.m_max.x) return false;
    if (m_max.z < input.m_min.z || m_min.z > input.m_max.z) return false;
    if (m_max.y < input.m_min.y || m_min.y > input.m_max.y) return false;
    bool hit = false;
    bool found = false;
    for (int i = 0; i < m_partNum; i++) {
        const IDCmfPosData* posData = &m_parts[i].m_posData;
        IDColiObjGrand* grand = m_parts[i].m_grand;
        int type = result.m_type;
        bool partHit;
        if (grand->m_flags & 0x80) {
            partHit = false;
        } else {
            IDColiInput partInput;
            IDColiGrandObj obj(&grand->m_work);
            obj.m_instPosData = posData;
            IDColiInputUtil::getCapsule(partInput, input, posData, false);
            partHit = obj.testCapsule(result, partInput, true);
        }
        if (type == 0) {
            if (partHit) {
                found = true;
                break;
            }
        } else {
            hit |= partHit;
        }
    }
    return hit | found;
}

}  // namespace idcoli
namespace navi {

unsigned int NvmshManager::jobUpdate(void* man, void*) {
    NvmshManager* manager = static_cast<NvmshManager*>(man);
    manager->m_flags |= 0x20000;
    if (!(manager->m_flags & (!(manager->m_flags & 0x4) ? 0x1 : 0x8))) {
        manager->m_pResMan->update();
        manager->m_pAcMan->update(manager->m_pResMan);
    }
    manager->m_flags &= ~0x20000;
    return 0;
}

NvmshManager::~NvmshManager() {
    ml::WorkCpu::sync(m_jobGroup, static_cast<ml::WKCPU_SYNC>(0), static_cast<ml::CPUID>(0));
    ml::WorkCpu::removeAutoExecGrp(m_jobGroup);
    ml::WorkCpu::releaseGroupHandle(m_jobGroup);
    if (m_pResMan) {
        delete m_pResMan;
        m_pResMan = nullptr;
    }
    if (m_pAcMan) {
        delete m_pAcMan;
        m_pAcMan = nullptr;
    }
    if (m_hAlloc.m_handle != 0) {
        mtl::MemManager::erase(m_hAlloc);
        m_hAlloc = mtl::ALLOC_HANDLE();
    }
}

void NvmshManager::setupResource(const void* resource, const char* name) {
    m_pResMan->setupResource(static_cast<const unsigned char*>(resource), name);
}

void NvmshManager::releaseResource() { m_pResMan->releaseResource(); }

NvmshAcObj* NvmshManager::createObj() {
    static ml::CriticalSection s_cs;  // the name is not the original's
    ml::CS lock(s_cs);
    return static_cast<NvmshAcObj*>(m_pAcMan->createObj(m_hAlloc, m_pResMan));
}

void NvmshManager::releaseObj(NvmshAcObj* object) { m_pAcMan->releaseObj(object); }

}  // namespace navi
