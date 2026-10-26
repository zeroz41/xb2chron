#include "classes/gf/TGfTween.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "gf/GfFieldUndulator.h"
#include "gf/GfFieldPitchRollController.h"
#include "gf/GfGameDepopMeter.h"
#include "gf/GfBigObjUnique.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "gf/GfFieldUndulator.h"
#include "gf/GfFieldPitchRollController.h"
#include "gf/GfGameDepopMeter.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfAssetManager.h"
#include <string.h>
#include "anm/Util.h"
#include "classes/gf/TGfTween.h"
#include "classes/gf/GfSpeedTween.h"
#include "gf/GfFieldMoveSpeed.h"
#include "classes/gf/GfGameDepopMeterManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComAsm.h"
#include "gf/GfObjAcc.h"
#include "ml/MTRand.h"


namespace gf {

bool getMoveVec(mm::Vec3& out, const navi::NvmshAcObj* obj) {
    if (obj != nullptr && (obj->m_flags & 2) && obj->m_state == 1) {
        out = obj->getMoveVec();
        return true;
    }
    return false;
}

GfFieldLocalSteer::GfFieldLocalSteer(const CreateInfo* info) : pad_20(false), pad_24(0.0f), pad_5040(nullptr), pad_5050(0), pad_5054(false) {
    if (info) {
        create(*info);
    }
}

void GfFieldLocalSteer::create(const CreateInfo& info) {
    dispose();
    const char* model = GfAssetManager::getModelInfo(GfObjUtil::getAssetHandle(info.m_handle));
    if (model != nullptr && (strcmp(model, "np510301") == 0 || strcmp(model, "np510311") == 0 ||
                             strcmp(model, "np550401") == 0)) {
        return;
    }
    m_info = info;
    m_angle.m_from = 0.0f;
    m_angle.m_to = 0.0f;
    m_angle.m_duration = 0.0f;
    m_angle.m_time = 0.0f;
}

bool GfFieldLocalSteer::isTimeOutCollide() const {
    if (m_info.m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return pad_24 > 5.0f;
}

float GfFieldLocalSteer::getCurAngle() const {
    return m_angle.getValue();
}

void GfFieldLocalSteer::dispose() {
    m_info = CreateInfo();
}

void GfFieldUndulator::create(const CreateInfo& info) {
    m_bdat.pad_1 = false;
    m_bdat.pad_0 = false;
    m_info = info;
    unsigned short paramId = Bdat::getValCheck(GfDataBdat::getFP(0x8B), "ParamID", info.m_id, 2);
    unsigned int resourceId = (unsigned short)Bdat::getValCheck(GfDataBdat::getFP(0x8C), "ResourceID", paramId, 2);
    m_bdat.create(static_cast<unsigned char>(Bdat::getValCheck(GfDataBdat::getFP(0xA5), "Unduration", resourceId, 1)));
}

void GfFieldUndulator::dispose() {
    m_bdat.pad_0 = false;
    m_bdat.pad_1 = false;
}

GfFieldPitchRollController::GfFieldPitchRollController(const CreateInfo* info) : pad_10(nullptr), m_seq(nullptr), pad_28(0), pad_30(0) {
    if (info) {
        create(*info);
    }
}

void GfFieldPitchRollController::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_seq = &GfFieldPitchRollController::seqInit;
}

void GfFieldPitchRollController::dispose() {
    pad_10 = nullptr;
    m_seq = nullptr;
    m_info = CreateInfo();
}

void GfFieldPitchRollController::update(const gmk::GmkRouteNavi& navi) {
    if (m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_seq) {
        (this->*m_seq)(navi);
    }
}

GfGameDepopMeterManager::~GfGameDepopMeterManager() {}

void GfGameDepopMeterManager::dispose() {
    if (GfGameDepopMeterManager* manager = sys()) {
        delete manager;
    }
}

const char* GfFieldMoveSpeed::s_S_move = "S_move";
const char* GfFieldMoveSpeed::s_V_speed = "V_speed";
const char* GfEnemyFieldMoveSpeed::s_S_move = "S_move";
const char* GfEnemyFieldMoveSpeed::s_V_speed = "V_speed";

GfFieldMoveSpeed::GfFieldMoveSpeed(const CreateInfo* info)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_speedMin(12.0f), m_speedMax(28.0f), m_speed(0.0f) {
    if (info) {
        create(*info);
    }
}

void GfFieldMoveSpeed::setSpeedKmph(float speed, float duration) {
    m_tween.m_from = m_speed;
    m_tween.m_to = speed;
    m_tween.m_duration = duration;
    m_tween.m_time = 0.0f;
}

void GfFieldMoveSpeed::dispose() {
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GfEnemyFieldMoveSpeed::GfEnemyFieldMoveSpeed(const CreateInfo* info)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_speedMin(12.0f), m_speedMax(28.0f), m_speed(0.0f) {
    if (info) {
        create(*info);
    }
}

GfBigObjUnique::GfBigObjUnique(const CreateInfo* info)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_elapsed(0.0f), m_prevTime(0.0f) {
    if (info) {
        create(*info);
    }
}

void GfEnemyFieldMoveSpeed::setSpeedKmph(float speed, float rate) {
    float speedNow = m_tween.m_value;
    m_tween.m_to = speed;
    m_speed = speedNow;
    m_tween.m_from = speedNow;
    m_tween.m_value = rate == 0.0f ? speed : speedNow;
    m_tween.m_rate = rate;
}

GfGameDepopMeter::GfGameDepopMeter(const CreateInfo* info)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_18(true), pad_20(true), pad_30(mm::Vec3::zero), pad_40(false) {
    if (info) {
        create(*info);
    }
}

void GfBigObjUnique::create(

const CreateInfo& info) {
    dispose();
    m_handle = info.m_handle;
    m_elapsed = 0.0f;
    m_prevTime = 0.0f;
}

void GfBigObjUnique::dispose() {
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfBigObjUnique::update(float deltaTime) {
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    GfComAsm* comAsm = obj->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return;
    }
    float time = comAsm->getLocalTime(AnimLayer(0));
    float prevTime = m_prevTime;
    m_elapsed += deltaTime;
    m_prevTime = time;
    if (time < prevTime && m_elapsed >= 120.0f) {
        m_elapsed = 0.0f;
        comAsm->execCmd(ml::mtRand(0, 2) == 0 ? "C_uniqueA" : "C_uniqueB", AnimLayer(0));
    }
}

}  // namespace gf
