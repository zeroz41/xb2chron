#include "classes/ml/DrAPCache.h"
#include "classes/ml/DrCalcClipWorkCone.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "classes/ml/DrEnvironmentObj.h"
#include "classes/ml/DrGlobalIBLPack.h"
#include "classes/ml/DrLightObjLocalIBL.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/ml/DrShdLgtHybrid.h"
#include "classes/ml/DrShdLgtTileBasedDr.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjEnvColiDr.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnRenderDrSys.h"
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
#include "ml/DrCreator.h"
#include "ml/DrEnvColiObj.h"
#include "ml/DrGlobalIBLMan.h"
#include "ml/DrLightMan.h"
#include "ml/DrPixlPostObjExpStencil.h"
#include "ml/DrPixlPostObjUnbranchToDepth.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrShdCubeCapFilter.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrShdLgtMan.h"
#include "mm/Vec3.h"
#include "navi/NvmshAcMan.h"

namespace ml {

inline ScnObjEnvColiDr::ScnObjEnvColiDr(Scn* scn, const void* res, int view) : ScnObjEnvColi(scn) {
    DrCreator creator;
    m_pColiObj = creator.createEnvColi(res, view);
}

ScnObjEnvColiDr::~ScnObjEnvColiDr() {
    if (m_pColiObj != nullptr) {
        m_pColiObj->release();
    }
}

ScnObjEnvColiDr* ScnObjEnvColiDr::create(Scn* scn, const void* res, int view) {
    if (!scn->m_pool->isValidInsert(4)) {
        return nullptr;
    }
    ScnObjEnvColiDr* obj = new (scn->m_allocHandle, nullptr, 0, 4, false) ScnObjEnvColiDr(scn, res, view);
    scn->m_pool->insert(obj);
    return obj;
}

inline ScnObjIBLDr::ScnObjIBLDr(Scn* scn, const void* res, int view) : ScnObjIBL(scn), m_pPack(nullptr), m_view(view) {
    ScnRenderDrSys* render = m_scn->m_renderDrSys;
    if (render != nullptr && render->m_drMan != nullptr && render->m_drMan->m_iblMan[view] != nullptr) {
        m_pPack = render->m_drMan->m_iblMan[view]->createObj(res);
    }
}

ScnObjIBLDr::~ScnObjIBLDr() {
    if (m_pPack != nullptr) {
        ScnRenderDrSys* render = m_scn->m_renderDrSys;
        if (render != nullptr && render->m_drMan != nullptr && render->m_drMan->m_iblMan[m_view] != nullptr) {
            render->m_drMan->m_iblMan[m_view]->releaseObj(m_pPack);
        }
    }
}

ScnObjIBLDr* ScnObjIBLDr::create(Scn* scn, const void* res, int view) {
    if (!scn->m_pool->isValidInsert(5)) {
        return nullptr;
    }
    ScnObjIBLDr* obj = new (scn->m_allocHandle, nullptr, 0, 4, false) ScnObjIBLDr(scn, res, view);
    scn->m_pool->insert(obj);
    return obj;
}

void ScnObjIBLDr::setReferencePos(const mm::Vec3&) {}

const mm::Vec3& ScnObjIBLDr::getReferencePos() const { return mm::Vec3::zero; }

void ScnObjIBLDr::setFromCaptureTool() { m_pPack->m_captureMode = 2; }

void ScnObjIBLDr::dispDebugWindow(bool, const char*, ml::WinProc*) {}

void ScnObjIBLDr::apply() {
    if (DrGlobalIBLPack* pack = m_pPack) {
        pack->m_flags = !isDisp() ? (pack->m_flags | DrGlobalIBLPack::FLAG_HIDE) : (pack->m_flags & ~DrGlobalIBLPack::FLAG_HIDE);
    }
}

void ScnObjIBLDr::setName(const char*) {}

const char* ScnObjIBLDr::getName() const { return "IBLList"; }

inline ScnObjLightDrSys::ScnObjLightDrSys(Scn* scn, const void* res, int view)
    : ScnObjLight(scn), m_pRes(res), m_pEnvObj(nullptr), m_view(view) {
    if (!m_scn->m_pool->isExistLgtEnv()) {
        DrMan* drMan = m_scn->m_renderDrSys->m_drMan;
        drMan->m_viewLightMan[m_view]->releaseFastLight();
    }
    DrCreator creator;
    m_pEnvObj = creator.createLgt(m_pRes, m_view);
}

ScnObjLightDrSys::~ScnObjLightDrSys() {
    if (m_pEnvObj != nullptr) {
        m_pEnvObj->release();
    }
}

void ScnObjLightDrSys::apply() {
    getTrans(false)->update();
    if (DrEnvironmentObj* env = m_pEnvObj) {
        env->m_flags = !isDisp() ? (env->m_flags | DrEnvironmentObj::FLAG_HIDE) : (env->m_flags & ~DrEnvironmentObj::FLAG_HIDE);
        if (isOfsMatrix()) {
            m_pEnvObj->m_flags |= DrEnvironmentObj::FLAG_OFS_MATRIX;
            m_pEnvObj->setOfsMatrix(getTrans(false)->m_worldMat);
        } else {
            m_pEnvObj->m_flags &= ~DrEnvironmentObj::FLAG_BIT2;
        }
    }
}

void ScnObjLightDrSys::tail() {}

float ScnObjLightDrSys::getFrame() const {
    if (m_pEnvObj == nullptr) {
        return 0.0f;
    }
    return m_pEnvObj->getFrame();
}

void ScnObjLightDrSys::setFrame(float frame) {
    if (m_pEnvObj != nullptr) {
        m_pEnvObj->setFrame(frame);
    }
}

float ScnObjLightDrSys::getMaxFrame() const {
    if (m_pEnvObj == nullptr) {
        return 0.0f;
    }
    return m_pEnvObj->getMaxFrame();
}

void ScnObjLightDrSys::setFrameSpd(float spd) {
    if (m_pEnvObj != nullptr) {
        m_pEnvObj->setFrameSpd(spd);
    }
}

float ScnObjLightDrSys::getFrameSpd() const {
    if (m_pEnvObj == nullptr) {
        return 0.0f;
    }
    return m_pEnvObj->getFrameSpd();
}

void ScnObjLightDrSys::setGroup(int group) { m_pEnvObj->m_group = group; }

int ScnObjLightDrSys::getGroup() const { return m_pEnvObj->m_group; }

void ScnObjLightDrSys::setOffsetPos(const mm::Vec3& pos) {
    if (DrEnvironmentObj* env = m_pEnvObj) {
        env->m_offsetPos.x = pos.x;
        env->m_offsetPos.y = pos.y;
        env->m_offsetPos.z = pos.z;
    }
}

const mm::Vec3& ScnObjLightDrSys::getOffsetPos() const { return m_pEnvObj->m_offsetPos; }

void ScnObjLightDrSys::setDeugDisp2D(bool disp) {
    if (disp) {
        m_pEnvObj->m_flags |= DrEnvironmentObj::FLAG_DEBUG_DISP_2D;
    } else {
        m_pEnvObj->m_flags &= ~DrEnvironmentObj::FLAG_DEBUG_DISP_2D;
    }
}

void ScnObjLightDrSys::setFromCaptureTool() { m_pEnvObj->m_captureMode = 2; }

void ScnObjLightDrSys::setLocalIBLName(const char*) {}

ScnObjLightDrSys* ScnObjLightDrSys::create(Scn* scn, const void* res, int view) {
    if (!scn->m_pool->isValidInsert(4)) {
        return nullptr;
    }
    ScnObjLightDrSys* obj = new (scn->m_allocHandle, nullptr, 0, 4, false) ScnObjLightDrSys(scn, res, view);
    scn->m_pool->insert(obj);
    return obj;
}

bool ScnObjLightDrSys::isEnv() const { return m_pEnvObj != nullptr; }

}  // namespace ml
