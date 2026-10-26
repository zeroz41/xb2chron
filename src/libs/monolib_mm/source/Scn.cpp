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
