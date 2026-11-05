#include "classes/gf/TGfTween.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/gmk/GmkRouteNavi.h"
#include "gf/GfFieldUndulator.h"
#include "gf/GfFieldPitchRollController.h"
#include "gf/GfGameDepopMeter.h"
#include "gf/GfBigObjUnique.h"
#include "gf/GfFieldLookIk.h"
#include "gf/GfObjAcc.h"
#include "gf/GfExecSchedule.h"
#include "mm/mtl/FixStr.h"
#include "classes/fw/ComponentObject.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComIK.h"
#include "classes/fw/LookIkSolver.h"
#include "gf/MsgPcGetLookPoint.h"
#include "fw/Transform.h"
#include "mm/Mat44.h"
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
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComAsm.h"
#include "gf/GfObjAcc.h"
#include "ml/MTRand.h"
#include "gf/GfGameStuckMeter.h"
#include "classes/fw/ColiMoveObject.h"


namespace gf {

void validateGmkRouteNaviConsideringGfLocalSteer(gmk::GmkRouteNavi& navi, const GfFieldLocalSteer& steer,
                                                 const mm::Vec3& pos) {
    if (navi.m_info.isValid() && navi.m_acc.isValid() && navi.pad_80 &&
        steer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && steer.pad_20) {
        if ((navi.pad_90 - pos).length() < steer.m_info.pad_8) {
            navi.updateNextPos();
        }
    }
}

bool getMoveVec(mm::Vec3& out, const navi::NvmshAcObj* obj) {
    if (obj != nullptr && (obj->m_flags & 2) && obj->m_state == 1) {
        out = obj->getMoveVec();
        return true;
    }
    return false;
}

bool execEndSchedule(fw::ComponentObject& com) {
    GfComAsm* comAsm = com.m_owner->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return false;
    }
    const char* state = comAsm->getStateName(AnimLayer(0));
    if (state == nullptr || strstr(state, "S_schedule_") == nullptr) {
        return false;
    }
    mm::mtl::FixStr<32> cmd(state);
    cmd.m_str[0] = 'C';
    cmd[cmd.length() - 1] = '2';
    return comAsm->execCmd(cmd.m_str, AnimLayer(0));
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

void GfFieldLocalSteer::apply(mm::Vec3& out, const mm::Vec3& in) const {
    float angle = getCurAngle();
    if (angle == 0.0f) {
        out = in;
        return;
    }
    mm::Mat44 rot;
    rot.setRotY(angle);
    out = mm::Vec3(in.x * rot.m[0][0] + in.y * rot.m[1][0] + in.z * rot.m[2][0],
                   in.x * rot.m[0][1] + in.y * rot.m[1][1] + in.z * rot.m[2][1],
                   in.x * rot.m[0][2] + in.y * rot.m[1][2] + in.z * rot.m[2][2]);
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

GfFieldPitchRollController::GfFieldPitchRollController(const CreateInfo* info) : pad_10(nullptr), m_seq(nullptr), pad_28(0), pad_30(false), pad_31(false) {
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

void GfFieldMoveSpeed::create(const CreateInfo& info) {
    dispose();
    m_handle = info.m_handle;
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    // one early exit for both misses (separate exits leave the minimum reloaded at the end)
    GfComAsm* comAsm = obj != nullptr ? obj->getComponent<GfComAsm>(2) : nullptr;
    if (comAsm == nullptr) {
        setSpeedKmph(m_speedMin, 0.0f);
        return;
    }
    const anm::ResASM* res = comAsm->getResource();
    if (res == nullptr) {
        dispose();
        return;
    }
    anm::Util::getVariableMinMax(*res, s_S_move, s_V_speed, &m_speedMin, &m_speedMax);
    if (m_speedMin < 1e-6f) {
        m_speedMin = 1e-6f;
    }
    if (m_speedMax < m_speedMin) {
        m_speedMax = m_speedMin;
    }
    setSpeedKmph(m_speedMin, 0.0f);
}

void GfFieldMoveSpeed::setSpeedKmph(float speed, float duration) {
    m_tween.m_from = m_speed;
    m_tween.m_to = speed;
    m_tween.m_duration = duration;
    m_tween.m_time = 0.0f;
}

void GfFieldMoveSpeed::update(float deltaTime) {
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (m_tween.m_time < m_tween.m_duration) {
        float time = m_tween.m_time + deltaTime;
        m_tween.m_time = m_tween.m_duration < time ? m_tween.m_duration : time;
    }
    m_speed = m_tween.getValue();
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    GfComAsm* comAsm = obj->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return;
    }
    comAsm->setVariable(s_V_speed, m_speed);
    float playSpeed;
    if (m_speedMin < 1e-6f) {
        playSpeed = 0.0f;
    } else {
        float rate = m_speed / m_speedMin;
        float maxRate;
        if (rate < 1.0f) {
            playSpeed = rate;
        } else if ((maxRate = m_speedMax / m_speedMin) < rate) {
            playSpeed = rate / maxRate;
        } else {
            playSpeed = 1.0f;
        }
    }
    comAsm->setSpeed(playSpeed, AnimLayer(0));
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

void GfEnemyFieldMoveSpeed::update(float deltaTime) {
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (m_tween.m_from < m_tween.m_to) {
        m_tween.m_value += m_tween.m_rate * deltaTime;
        if (m_tween.m_to <= m_tween.m_value) {
            m_tween.m_value = m_tween.m_to;
        }
    } else {
        m_tween.m_value -= m_tween.m_rate * deltaTime;
        if (m_tween.m_value <= m_tween.m_to) {
            m_tween.m_value = m_tween.m_to;
        }
    }
    m_speed = m_tween.m_value;
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    GfComAsm* comAsm = obj->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return;
    }
    comAsm->setVariable(s_V_speed, m_speed);
}

GfFieldLookIk::GfFieldLookIk(GF_OBJ_HANDLE* handle)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_solverIndex(3), pad_c(5.0f), pad_10(2.35619450f),
      pad_14(1.04719758f), m_fadeTime(0.7f), pad_1c(true), pad_20(mm::Vec3::zero), pad_30(false) {
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        dispose();
        m_handle = handle;
    }
}

void GfFieldLookIk::dispose() {
    pad_30 = false;
    if (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjAcc acc(m_handle);
        if (!acc.isDestroy() && !acc.testFlag(17)) {
            if (GfObj* obj = acc.getObj()) {
                if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
                    if (fw::LookIkSolver* solver = ik->getSolver<fw::LookIkSolver>(m_solverIndex)) {
                        solver->fadeOut(m_fadeTime);
                    }
                }
            }
        }
        m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
}

// the GfComIK solver of each LookAt value (lbl_71009BB654; the name is not the original's)
static const unsigned int s_lookAtSolvers[] = {9, 5, 3};

void GfFieldLookIk::create(GF_OBJ_HANDLE* handle, const CBdatWrapper& bdat, int id) {
    dispose();
    m_handle = handle;
    unsigned char lookAt = Bdat::getValCheckU8(bdat.m_fp, "LookAt", id);
    if (lookAt != 0) {
        pad_c = Bdat::getValCheckU16(bdat.m_fp, "LookAtRange", id);
        if (lookAt >= 3) {
            dispose();
        } else {
            m_solverIndex = s_lookAtSolvers[lookAt];
            pad_1c = true;
        }
    } else {
        pad_1c = false;
    }
}

void GfFieldLookIk::update(float) {
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1) || !pad_1c) {
        return;
    }
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        dispose();
        return;
    }
    GfComIK* ik = obj->getComponent<GfComIK>(3);
    if (ik == nullptr) {
        return;
    }
    switch (m_solverIndex) {
    case 3:
        if (fw::LookIkSolver* solver = ik->getSolver<fw::LookIkSolver>(3)) {
            updateIkSolver(*solver);
        }
        break;
    case 5:
        if (fw::LookIkSolver* solver = ik->getSolver<fw::LookIkSolver>(3)) {
            if (fw::LookAtIkSolver* lookAt = solver->m_lookAt.get()) {
                updateIkSolver(*lookAt);
            }
        }
        break;
    }
}

bool GfFieldLookIk::findPos(mm::Vec3& pos) const {
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    MsgPcGetLookPoint msg;
    bool taken = static_cast<fw::MessageObject*>(obj)->recieveMessage(obj, msg);
    if (msg.m_found && taken) {
        pos = msg.m_point;
        return true;
    }
    if (acc.isValidTransform()) {
        pos = acc.getWorldTransform().position;
        return true;
    }
    return false;
}

GfGameDepopMeter::GfGameDepopMeter(const CreateInfo* info)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_18(true), pad_20(true), pad_30(mm::Vec3::zero), pad_40(false) {
    if (info) {
        create(*info);
    }
}

void GfGameDepopMeter::dispose() {
    if (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfGameDepopMeter* cursor = &*GfGameDepopMeterManager::sys()->m_cursor;
        GfGameDepopMeterManager* manager = GfGameDepopMeterManager::sys();
        if (cursor == this) {
            ++manager->m_cursor;
        }
        manager->m_meters.remove(this);
        manager = GfGameDepopMeterManager::sys();
        if (manager->m_meters.end() == manager->m_cursor) {
            manager->m_cursor = manager->m_meters.begin();
        }
    }
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    pad_40 = false;
    pad_18 = true;
}

void GfGameDepopMeterManager::create(unsigned int updateCount) {
    dispose();
#line 1598
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameDepopMeterManager(updateCount);
}

void GfGameStuckMeter::CreateInfo::dispose() {
    if (m_coli != nullptr) {
        m_coli->release();
        m_coli = nullptr;
    }
}

void GfGameStuckMeter::CreateInfo::setColiObj(fw::ColiMoveObject* coli) {
    dispose();
    m_coli = coli;
    if (coli != nullptr) {
        coli->addRef();
    }
}

GfGameStuckMeter::GfGameStuckMeter(const CreateInfo* info)
    : m_height(0.0f), m_radius(0.0f), m_scale(1.0f), m_pos(mm::Vec3::zero), m_avgPos(mm::Vec3::zero),
      m_freeTime(0.0f), m_stuckTime(0.0f) {
    if (info) {
        create(*info);
    }
}

void GfGameStuckMeter::create(const CreateInfo& info) {
    dispose();
    m_info.pad_0 = info.pad_0;
    m_info.m_stuckDelay = info.m_stuckDelay;
    m_info.m_coli = info.m_coli;
    if (m_info.m_coli != nullptr) {
        m_info.m_coli->addRef();
    }
    m_info.m_minSpeedSq = info.m_minSpeedSq;
    // written as a test: the original keeps a null constant on the path without one
    fw::ColiMoveObject* coli = m_info.m_coli != nullptr ? m_info.m_coli : nullptr;
    fw::ColiShape* shape = coli->m_shape.get();
    if (shape != nullptr && shape->m_kind == 3) {
        fw::ColiShapeCharacter* character = static_cast<fw::ColiShapeCharacter*>(shape);
        m_height = character->m_height;
        m_radius = character->m_radius;
    } else {
        m_scale = coli->m_scale;
    }
    m_pos = coli->getMatrix().getTrans();
    m_avgPos = m_pos;
    m_freeTime = 0.0f;
    m_stuckTime = 0.0f;
}

void GfGameStuckMeter::dispose() {
    if (m_info.m_coli != nullptr) {
        m_info.m_coli->resetCharacter(m_height, m_radius);
        m_info.dispose();
    }
}

void GfGameStuckMeter::update(float deltaTime) {
    if (deltaTime <= 0.0f || m_info.m_coli == nullptr) {
        return;
    }
    bool restore;
    if (checkStuck(deltaTime)) {
        m_freeTime = 0.0f;
        m_stuckTime += deltaTime;
        restore = false;
    } else {
        m_freeTime += deltaTime;
        restore = false;
        if (m_freeTime > 3.0f) {
            m_stuckTime = 0.0f;
            restore = true;
        }
    }
    fw::ColiMoveObject* coli = m_info.m_coli;
    if (static_cast<int>(coli->m_followType) != 1) {
        return;
    }
    fw::ColiShape* shape = coli->m_shape.get();
    fw::ColiShapeCharacter* character =
        shape != nullptr && shape->m_kind == 3 ? static_cast<fw::ColiShapeCharacter*>(shape) : nullptr;
    if (m_info.m_stuckDelay <= m_stuckTime) {
        if (character != nullptr) {
            float height = character->m_height * 0.99f;
            height = height < 0.05f ? 0.05f : height;
            float radius = character->m_radius * 0.99f;
            radius = radius < 0.05f ? 0.05f : radius;
            coli->resetCharacter(height, radius);
        } else {
            float scale = coli->m_scale * 0.99f;
            coli->m_scale = scale < 0.05f ? 0.05f : scale;
        }
    } else {
        if (!restore) {
            return;
        }
        if (character != nullptr) {
            float height = character->m_height * 1.1f;
            height = m_height < height ? m_height : height;
            float radius = character->m_radius * 1.1f;
            radius = m_radius < radius ? m_radius : radius;
            coli->resetCharacter(height, radius);
        } else {
            float scale = coli->m_scale * 1.1f;
            coli->m_scale = m_scale < scale ? m_scale : scale;
        }
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
