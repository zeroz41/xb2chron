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
#include "classes/ml/ScnObj.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ThreadNx.h"
#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnCamMan.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Thread.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/DevClock.h"
#include "ml/CriticalSection.h"
#include "ml/EdianUtil.h"
#include "ml/TimeCount.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include "nn/os.h"
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

ScnObjModel::~ScnObjModel() {}

ScnObjLight::~ScnObjLight() {}

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

}  // namespace ml
