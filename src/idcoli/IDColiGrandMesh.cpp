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

namespace idcoli {

bool IDColiUtilColiResult::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isCapsulePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isLineSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineSphere(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiResult::isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, false);
}

bool IDColiUtilColiResult::isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, true);
}

bool IDColiUtilColiResult::isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, false);
}

bool IDColiUtilColiResult::isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, true);
}

bool IDColiUtilColiResult::isLinePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isRaySphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineSphere(result, &ray->m_lines[0], pOther, false)) return true;
    return isPartsLineSphere(result, &ray->m_lines[1], pOther, true);
}

bool IDColiUtilColiResult::isRayBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, false, false)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, true, false);
}

bool IDColiUtilColiResult::isRayInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, false, true)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, true, true);
}

bool IDColiUtilColiResult::isRayCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, false, false)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, true, false);
}

bool IDColiUtilColiResult::isRayInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, false, true)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, true, true);
}

bool IDColiUtilColiResult::isRayPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isSphereBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isCapsuleBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleInBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsulePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isBoxSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(pOther), static_cast<const CLBoxWork*>(input.getShape()));
}

bool IDColiUtilColiSimple::isBoxBox(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isBoxCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(pOther), static_cast<const CLBoxWork*>(input.getShape()));
}

bool IDColiUtilColiSimple::isBoxPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isLinePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, true);
}

bool IDColiUtilColiSimple::isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isRayBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, false)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, false);
}

bool IDColiUtilColiSimple::isRayInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, true)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, true);
}

bool IDColiUtilColiSimple::isRayCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, false)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, false);
}

bool IDColiUtilColiSimple::isRayInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, true)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, true);
}

bool IDColiUtilColiSimple::isRayPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

void IDColiPrimitive::createBaseBox(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size) {
    calcBaseBoxSetup(static_cast<CLBoxWork*>(base), matrix, size);
    type = IDCOLI_BASE_BOX;
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

void IDColiGrandMesh::vecotrNon(IDColiCallArg&, const IDCmfPoliData*) {}

IDColiGrandObj::~IDColiGrandObj() {}

bool IDColiGrandTree::instLineHit(unsigned int index) {
    return instLineHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandTree::instRayHit(unsigned int index) {
    return instRayHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandTree::instSphereHit(unsigned int index) {
    return instSphereHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

bool IDColiGrandTree::instCapsuleHit(unsigned int index) {
    return instCapsuleHitParts(&m_work->m_posData[index], &m_work->m_posInfo[index]);
}

void IDColiGrdMoveObj::setMat(const mm::Mat44& matrix) {
    m_mats[IDColiManager::s_nStkIdx] = matrix;
    m_matRequest |= 1 << IDColiManager::s_nStkIdx;
}

IDColiObjGrand::IDColiObjGrand() {
    m_memBlock = nullptr;
    m_type = 3;  // a ground (fw::ColiObject's isGrand tests 3)
}

IDColiObjGrand::~IDColiObjGrand() {
    if (m_memBlock) {
        if (m_treeTops[0]) m_treeTops[0]->~IDColiTreeTop();
        if (m_treeTops[1]) m_treeTops[1]->~IDColiTreeTop();
        if (m_memBlock) {
            mtl::MemManager::deallocate(m_memBlock, 0, false);
            m_memBlock = nullptr;
        }
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
