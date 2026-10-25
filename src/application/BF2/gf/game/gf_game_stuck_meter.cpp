#include "gf/GfBigObjUnique.h"
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

void GfBigObjUnique::create(const CreateInfo& info) {
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
