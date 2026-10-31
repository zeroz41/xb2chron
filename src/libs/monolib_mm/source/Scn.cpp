#define MM_LIB_FROM_MONOLIB_MM
#include "math.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/DevGraph.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/FileResTh.h"
#include <math.h>
#include "mm/Mat44.h"
#include "ml/AttrTransform.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnObjModel.h"
#include "ml/AttrTransform.h"
#include "classes/ml/threadval.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/Scn.h"
#include "ml/ScnCamUtil.h"
#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/ScnObj.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnCamMan.h"
#include "classes/ml/WinViewRoot.h"
#include "classes/ml/DebDraw.h"
#include "nn/os.h"
#include "ml/CriticalSection.h"
#include "classes/ml/Thread.h"
#include "classes/ml/ThreadNx.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/threadval.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/DevClock.h"
#include "ml/EdianUtil.h"
#include "ml/TimeCount.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include <string.h>

namespace ml {

void ScnDebugManipuRot::update() {}

void ScnDebugManipuTrans::setRadius(float) {}

void ScnDebugManipuTrans::update() {}

void ScnObjCam::renderDebug(ml::DebDraw*) {}

bool ScnObjLight::isDisp() const {
    return m_disp;
}

bool ScnObjLight::isOfsMatrix() const {
    return m_ofsMatrix;
}

ScnObjClip::~ScnObjClip() {}

ScnObjEnvColi::~ScnObjEnvColi() {}

void ScnObjModel::setDelete() {
    m_delete = true;
}

void ScnObj::setDelete() {
    m_delete = true;
}

void ScnObjModel::setFrameSpd(float spd) {
    m_frameSpd = spd;
}

bool ScnObjModel::isDisp() const {
    return m_disp;
}

bool ScnObjModel::isClip() const {
    return m_clip;
}

ScnObjIBL::~ScnObjIBL() {}

bool ScnObjIBL::isDisp() const {
    return m_disp;
}

void ScnObjModel::renderDebug(ml::DebDraw*) {}

ScnDebugManipuObj::~ScnDebugManipuObj() {}

ScnRender::~ScnRender() {}

Scn::~Scn() {
    term();
}

void Scn::term() {
    if (m_grpHandle != -1) {
        WorkCpu::removeAutoExecGrp(m_grpHandle);
        WorkCpu::releaseGroupHandle(m_grpHandle);
        m_grpHandle = -1;
    }
    if (m_pool != nullptr) {
        delete m_pool;
        m_pool = nullptr;
    }
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thRenderKillTerminate, this, nullptr, nullptr, true,
                       static_cast<WKCPU_SYNC>(0));
    if (m_camMan != nullptr) {
        delete m_camMan;
        m_camMan = nullptr;
    }
    if (m_debug != nullptr) {
        delete m_debug;
        m_debug = nullptr;
    }
    for (FileResTh** it = m_entryRes.begin(); it != m_entryRes.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Release();
            *it = nullptr;
        }
    }
    m_entryRes.clear();
    if (m_cs != nullptr) {
        delete m_cs;
        m_cs = nullptr;
    }
    if (m_entryResCs != nullptr) {
        delete m_entryResCs;
        m_entryResCs = nullptr;
    }
    if (m_allocHandle.m_handle != 0) {
        mtl::MemManager::erase(m_allocHandle);
        m_allocHandle = mtl::ALLOC_HANDLE();
    }
}

ScnObjModel* Scn::createMdl(const void* resource, const char* name, int arg) {
    ScnObjModel* mdl = m_renderDrSys->createMdl(this, resource, name, arg);
    if (mdl != nullptr) {
        mdl->setAlwaysTexStm(!m_noAlwaysTexStm);
    }
    return mdl;
}

ScnObj* Scn::createLgt(const void* resource, int arg) {
    return m_renderDrSys->createLgt(this, resource, arg);
}

ScnObjIBL* Scn::createIBL(const void* resource, int arg) {
    return m_renderDrSys->createIBL(this, resource, arg);
}

void Scn::releaseItem(ScnObj* item) {
    if (item != nullptr) {
        m_pool->release(item);
    }
}

void Scn::setView(WinView* view, int index) {
    m_camMan->setView(view, index);
}

void ScnCamMan::setView(WinView* view, int index) {
    if (m_views[index] != -1 && m_views[index] != view->m_wid) {
        WinView* old = WinViewRoot::getView(m_views[index]);
        if (old != nullptr) {
            old->detachWorkEvent(m_scn);
        }
    }
    view->attachWorkEvent(m_scn, false);
    m_views[index] = view->m_wid;
}

WinView* Scn::getView(int index) {
    return m_camMan->getView(index);
}

ScnCamMan::~ScnCamMan() {
    for (unsigned int i = 0; i < m_views.size(); i++) {
        WinView* view = WinViewRoot::getView(*m_views.at(i));
        if (view != nullptr) {
            view->detachWorkEvent(m_scn);
        }
    }
}

ScnObjCam* ScnPoolObj::getCam(const WinView* view) {
    if (view != nullptr) {
        for (reslist<ScnObj*>::iterator it = m_cam.begin(); it != m_cam.end(); ++it) {
            ScnObjCam* cam = static_cast<ScnObjCam*>(*it);
            if (m_scn->getView(cam->m_index) == view) {
                return cam;
            }
        }
    }
    return nullptr;
}

ScnObjCam* ScnObjCam::create(Scn* scn, int index) {
    if (!scn->m_pool->isValidInsert(2)) {
        return nullptr;
    }
    mm::mtl::FixStr<32> name;
    name.format("Camera%d", index);
    ScnObjCam* cam = new (scn->m_allocHandle, nullptr, 0, 4, false) ScnObjCam(scn, name.m_str);
    cam->m_index = index;
    cam->setDefault();
    scn->m_pool->insert(cam);
    return cam;
}

bool ScnPoolObj::isValidInsert(unsigned short type) const {
    CS cs(m_cs);
    const reslist<ScnObj*>* list = getList(type);
    return list->m_capacity > list->size();
}

bool ScnPoolObj::isExistLgtEnv() const {
    CS cs(m_cs);
    bool exist = false;
    for (reslist<ScnObj*>::iterator it = m_lgt.begin(); it != m_lgt.end(); ++it) {
        exist |= static_cast<ScnObjLight*>(*it)->isEnv();
    }
    return exist;
}

ScnObjEnvColi::ScnObjEnvColi(Scn* scn) : ScnObj(scn, 6), m_name("envColi") {}

ScnRender::ScnRender(Scn* scn) : m_scn(scn) {}

const char* ScnObjModel::getName() const {
    return m_name.m_str;
}

const char* ScnObjCam::getName() const {
    return m_name.m_str;
}

const char* ScnObjClip::getName() const {
    return m_name.m_str;
}

const char* ScnObjEnvColi::getName() const {
    return m_name.m_str;
}

bool ScnRender::attachModel(ScnObjModel*) {
    return false;
}

ScnObjModel* ScnRender::createMdl(Scn*, const void*, const char*, int) {
    return nullptr;
}

ScnObj* ScnRender::createLgt(Scn*, const void*, int) {
    return nullptr;
}

// the base renderer has no loop count to wait for (ScnRenderDrSys asks DrMan::loopCnt)
bool ScnRender::applyLoopCnt() {
    return true;
}

const char* ScnObjLight::getName() const {
    return m_name.m_str;
}

ScnDebugManipu* ScnDebug::getManipulator() {
    return m_manipu;
}

void ScnDebug::setManipulatorTrans(const mm::Mat44* mtx, const mm::Vec3* pos) {
    m_manipu->createTrans(mtx, pos);
}

void ScnDebug::setManipulatorRot(const mm::Mat44* mtx, const mm::Vec3* pos) {
    m_manipu->createRot(mtx, pos);
}

void ScnObjModel::setPos(const mm::Vec3& pos) {
    m_info.m_cpu->m_trans.m_pos = pos;
}

void ScnObjModel::setPosWarp(const mm::Vec3& pos) {
    m_info.m_cpu->m_trans.m_pos = pos;
    m_warp = true;
}

void ScnObjModel::addPos(const mm::Vec3& pos) {
    m_info.m_cpu->m_trans.m_pos += pos;
}

void ScnObjModel::setRot(const mm::Vec3& rot) {
    m_info.m_cpu->m_trans.m_rot = rot;
}

void ScnObjModel::addRot(const mm::Vec3& rot) {
    m_info.m_cpu->m_trans.m_rot += rot;
}

void ScnObjModel::addRot(const mm::Quat& rot) {
    AttrTransform* trans = &m_info.m_cpu->m_trans;
    trans->m_quat = rot;
    trans->m_flags |= 2;
}

void ScnObjModel::setScl(const mm::Vec3& scl) {
    m_info.m_cpu->m_trans.m_scl = scl;
}

void ScnObjModel::setMat(const mm::Mat44& mat) {
    AttrTransform* trans = &m_info.m_cpu->m_trans;
    trans->m_mat = mat;
    trans->m_flags |= 1;
}

AttrTransform* ScnObjModel::getTrans(bool cpu) {
    return &(cpu ? m_info.m_cpu : m_info.m_render)->m_trans;
}

const AttrTransform* ScnObjModel::getTrans(bool cpu) const {
    return &(cpu ? m_info.m_cpu : m_info.m_render)->m_trans;
}

mm::Vec3& ScnObjModel::getOffsetInfo(bool cpu) {
    return (cpu ? m_offsetInfo.m_cpu : m_offsetInfo.m_render)->m_ofs;
}

void ScnObjModel::setDisp(bool on) {
    if (on) {
        m_dispReq = true;
    } else {
        m_dispReq = false;
    }
}

void ScnObjModel::setClip(bool on) {
    if (on) {
        m_clip = true;
    } else {
        m_clip = false;
    }
}

void ScnObjLight::setPos(const mm::Vec3& pos) {
    m_info.m_cpu->m_trans.m_pos = pos;
}

void ScnObjLight::setRot(const mm::Vec3& rot) {
    m_info.m_cpu->m_trans.m_rot = rot;
}

void ScnObjLight::setScl(const mm::Vec3& scl) {
    m_info.m_cpu->m_trans.m_scl = scl;
}

void ScnObjLight::setMat(const mm::Mat44& mat) {
    AttrTransform* trans = &m_info.m_cpu->m_trans;
    trans->m_mat = mat;
    trans->m_flags |= 1;
}

AttrTransform* ScnObjLight::getTrans(bool cpu) {
    return &(cpu ? m_info.m_cpu : m_info.m_render)->m_trans;
}

const mm::Plane& ScnObjCam::getPlaneGbl(unsigned int index, bool cpu) const {
    const RENDER_INFO* info = cpu ? m_info.m_cpu : m_info.m_render;
    return info->m_planeGbl[index];
}

void ScnObjCam::setCopydataCam(bool) {}

// Proposed names, not the original's: the symbols leave them unnamed (lbl_71009C7E40, lbl_71009C7E50)
static const mm::Vec3 s_defaultEye(0.0f, 5.0f, 20.0f);
static const mm::Vec3 s_defaultTarget(0.0f, 0.0f, 0.0f);

void ScnObjCam::setDefault() {
    setLookAt(s_defaultEye, s_defaultTarget, 0.0f);
    m_info.m_cpu->m_fov = 40.0f;
    updateViewMatrix(false);
}

void ScnObjCam::updateFovNearFar() {
    RENDER_INFO* info = m_info.m_cpu;
    info->m_invTan = 1.0f / tanf(info->m_fov * 0.0174532924f * 0.5f);
    float extent = -info->m_near / info->m_invTan;
    info->m_nearExtent[0] = extent;
    info->m_nearExtent[1] = -extent;
    info->m_nearExtent[2] = extent * info->m_aspect;
    info->m_nearExtent[3] = info->m_aspect * -extent;
}

void ScnObjCam::apply() {
    RENDER_INFO* info = m_info.m_render;
    const mm::Rect<int>& viewport = DevGraph::getViewport();
    if (viewport.w != 0 && viewport.h != 0) {
        info->m_aspect = static_cast<float>(viewport.w) / static_cast<float>(viewport.h);
    } else {
        info->m_aspect = 1.0f;
    }
    if (m_scn->m_renderDrSys != nullptr) {
        m_scn->m_renderDrSys->applyCamera(this);
    }
}

void Scn::setDebDraw(SCNCAM cam, SCNPRIO_CB prio) {
    m_debDraw[cam].m_prio = prio;
}

void Scn::renderStop() {
    m_renderStop = true;
}

bool ScnCamUtil::getScreenPos(mm::Vec3& out, const ScnObjCam* cam, const mm::Vec3& pos) {
    return getScreenPos(out, cam, false, pos);
}

void ScnDebugManipu::clear() {
    CS cs(m_cs);
    if (m_obj != nullptr) {
        delete m_obj;
        m_obj = nullptr;
    }
}

bool ScnDebugManipu::isPick() const {
    CS cs(m_cs);
    if (m_obj != nullptr) {
        return m_obj->m_pick != 0;
    }
    return false;
}

const AttrTransform* ScnDebugManipu::getTrans(bool cpu) const {
    CS cs(m_cs);
    if (m_obj != nullptr) {
        return &(cpu ? m_obj->m_info.m_cpu : m_obj->m_info.m_render)->m_trans;
    }
    return nullptr;
}

ScnDebugManipu::~ScnDebugManipu() {
    clear();
}

ScnDebug::~ScnDebug() {
    if (m_manipu != nullptr) {
        delete m_manipu;
        m_manipu = nullptr;
    }
}

bool ScnDebug::isPickManipu() const {
    if (m_manipu != nullptr) {
        return m_manipu->isPick();
    }
    return false;
}

void ScnDebug::clrManipulator() {
    m_manipu->clear();
}

void ScnDebug::cbRenderAfter(Scn*, SCNPRIO_CB) {
    render(DebDraw::get(-1));
}

// not an alias of ScnDebugManipuObj's: the original has its own copy (an empty statement keeps it)
ScnDebugManipuRot::~ScnDebugManipuRot() {
    ;
}

bool ScnDebugManipuRot::checkMouseButtonUp(EventView*) {
    if (!m_disp) {
        return false;
    }
    if (m_pick == 0) {
        return false;
    }
    m_pick = 0;
    return true;
}

void ScnDebugManipuRot::setRadius(float radius) {
    if (radius > 0.0f) {
        m_radius = radius;
        m_radiusOuter = radius + 10.0f;
    } else {
        m_radius = 70.0f;
        m_radiusOuter = 80.0f;
    }
}

// not an alias of ScnDebugManipuObj's: the original has its own copy (an empty statement keeps it)
ScnDebugManipuTrans::~ScnDebugManipuTrans() {
    ;
}

bool ScnDebugManipuTrans::checkMouseButtonUp(EventView*) {
    if (!m_disp) {
        return false;
    }
    m_axis = 7;
    if (m_pick == 0) {
        return false;
    }
    m_pick = 0;
    return true;
}

ScnObjIBL::ScnObjIBL(Scn* scn) : ScnObj(scn, 5), m_disp(true), pad_bits(0) {}

unsigned int Scn::thRenderKillTerminate(void* scn, void*) {
    Scn* self = static_cast<Scn*>(scn);
    if (self->m_renderDrSys != nullptr) {
        delete self->m_renderDrSys;
        self->m_renderDrSys = nullptr;
    }
    return 0;
}

}  // namespace ml
