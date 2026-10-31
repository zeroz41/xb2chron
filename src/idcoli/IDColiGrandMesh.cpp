#include "idcoli/IDColiGrandObj.h"
#include "classes/idcoli/IDColiObjGrand.h"
#include "classes/ml/WorkCpu.h"
#include "classes/navi/NvmshResMan.h"
#include "classes/navi/NvmshManager.h"
#include "navi/NvmshAcMan.h"
#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiInput.h"
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
void IDColiPrimitive::createBaseSphere(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size) {
    CLSphereWork* sphere = static_cast<CLSphereWork*>(base);
    type = IDCOLI_BASE_SPHERE;
    mm::Vec3 axis(matrix.m[0][0] + matrix.m[1][0] + matrix.m[2][0], matrix.m[0][1] + matrix.m[1][1] + matrix.m[2][1],
                  matrix.m[0][2] + matrix.m[1][2] + matrix.m[2][2]);
    float radius = axis.length() * IDColiObj::OBJ_CALC_RADIUS;
    sphere->m_radius = size.x * radius;
    sphere->m_center = matrix.getTrans();
}

void IDColiPrimitive::createBaseBox(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size) {
    calcBaseBoxSetup(static_cast<CLBoxWork*>(base), matrix, size);
    type = IDCOLI_BASE_BOX;
}

void IDColiPrimitive::createBasePoli(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3&) {
    IDColiObjGrdChar::Part* part = *static_cast<IDColiObjGrdChar::Part**>(base);
    calcPosDataSetup(&part->m_posData, matrix, part->m_corners[0], part->m_corners[1]);
    type = IDCOLI_BASE_POLI;
}

void IDColiPrimitive::createAaBbSphere(mm::Vec3& max, mm::Vec3& min, const void* shape) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(shape);
    float value;
    value = sphere->m_center.x + sphere->m_radius;
    if (max.x < value) max.x = value;
    value = sphere->m_center.x - sphere->m_radius;
    if (min.x > value) min.x = value;
    value = sphere->m_center.y + sphere->m_radius;
    if (max.y < value) max.y = value;
    value = sphere->m_center.y - sphere->m_radius;
    if (min.y > value) min.y = value;
    value = sphere->m_center.z + sphere->m_radius;
    if (max.z < value) max.z = value;
    value = sphere->m_center.z - sphere->m_radius;
    if (min.z > value) min.z = value;
}

void IDColiPrimitive::createAaBbBox(mm::Vec3& max, mm::Vec3& min, const void* shape) {
    const CLBoxWork* box = static_cast<const CLBoxWork*>(shape);
    if (max.x < box->m_max.x) max.x = box->m_max.x;
    if (min.x > box->m_min.x) min.x = box->m_min.x;
    if (max.y < box->m_max.y) max.y = box->m_max.y;
    if (min.y > box->m_min.y) min.y = box->m_min.y;
    if (max.z < box->m_max.z) max.z = box->m_max.z;
    if (min.z > box->m_min.z) min.z = box->m_min.z;
}

void IDColiPrimitive::createAaBbCapsule(mm::Vec3& max, mm::Vec3& min, const void* shape) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(shape);
    if (max.x < capsule->m_max.x) max.x = capsule->m_max.x;
    if (min.x > capsule->m_min.x) min.x = capsule->m_min.x;
    if (max.y < capsule->m_max.y) max.y = capsule->m_max.y;
    if (min.y > capsule->m_min.y) min.y = capsule->m_min.y;
    if (max.z < capsule->m_max.z) max.z = capsule->m_max.z;
    if (min.z > capsule->m_min.z) min.z = capsule->m_min.z;
}

void IDColiPrimitive::createAaBbPoli(mm::Vec3&, mm::Vec3&, const void*) {}

void IDColiPrimitive::createBaPosSphere(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                        const void* shape) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(shape);
    pos = sphere->m_center;
    radius = sphere->m_radius;
    height = sphere->m_radius + sphere->m_radius;
    flag = false;
    offset = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosBox(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                     const void* shape) {
    const CLBoxWork* box = static_cast<const CLBoxWork*>(shape);
    pos = box->m_center;
    radius = box->m_radius;
    height = box->m_height;
    flag = false;
    offset = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosCapsule(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                         const void* shape) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(shape);
    pos = capsule->m_pos;
    radius = capsule->m_radius;
    height = ::sqrtf(capsule->m_lengthSq) + (radius + radius);
    flag = true;
    offset = capsule->m_offset;
}

void IDColiPrimitive::createBaPosPoli(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                      const void* shape) {
    const IDColiObjGrdChar::Part* part = *static_cast<const IDColiObjGrdChar::Part* const*>(shape);
    pos = mm::Vec3(part->m_posData.m_matrix.m[0][3], part->m_posData.m_matrix.m[1][3],
                   part->m_posData.m_matrix.m[2][3]);
    radius = (part->m_posData.m_max.x - part->m_posData.m_min.x) * 0.5f;
    height = radius + radius;
    flag = false;
    offset = mm::Vec3(0.0f, 0.0f, 0.0f);
}

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
