#include "btl/Misc.h"
#include "classes/btl/ShakeCameraElement.h"
#include "classes/btl/ShakeCameraManager.h"
#include "classes/btl/ShakeCameraElementRandom.h"
#include "classes/btl/ShakeCameraElementAxis.h"
#include "classes/btl/ShakeCameraElementCameraAxis.h"
#include "btl/Misc.h"
#include "classes/btl/ShakeCameraManager.h"
#include "classes/btl/ShakeCameraElementRandom.h"
#include "classes/btl/ShakeCameraElementCameraAxis.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjAcc.h"
#include "fw/Transform.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "ml/MTRand.h"
#include <math.h>

namespace btl {

ShakeCameraElement::~ShakeCameraElement() {}
namespace Misc {

bool NormalizeXZ(mm::Vec3& v) {
    float length = ::sqrtf(v.x * v.x + v.z * v.z);
    if (length <= 1e-6f) {
        v = mm::Vec3::unitZ;
        return false;
    }
    float scale = 1.0f / length;
    v.y = 0.0f;
    v.x = scale * v.x;
    v.z = scale * v.z;
    return true;
}

float CalcLength(const mm::Vec3& a, const mm::Vec3& b) {
    return (b - a).length();
}

float CalcSquareLength(const mm::Vec3& a, const mm::Vec3& b) {
    mm::Vec3 d = b - a;
    return d.x * d.x + d.y * d.y + d.z * d.z;
}

float CalcLengthXZ(const mm::Vec3& a, const mm::Vec3& b) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    return ::sqrtf(dx * dx + dz * dz);
}

float CalcSquareLengthXZ(const mm::Vec3& a, const mm::Vec3& b) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    return dx * dx + dz * dz;
}

float CalcLengthXZ(const mm::Vec3& v) {
    return ::sqrtf(v.x * v.x + v.z * v.z);
}

bool CalcDirectionXZ(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& out) {
    out.x = to.x - from.x;
    out.z = to.z - from.z;
    return NormalizeXZ(out);
}

void RandomVector(mm::Vec3& out) {
    out.x = 0.5f - ml::mtRandf1();
    out.y = 0.5f - ml::mtRandf1();
    out.z = 0.5f - ml::mtRandf1();
    Normalize(out);
}

void RandomVectorXZ(mm::Vec3& out) {
    out.x = 0.5f - ml::mtRandf1();
    out.z = 0.5f - ml::mtRandf1();
    NormalizeXZ(out);
}

bool GetObjectTransform(gf::GF_OBJ_HANDLE* handle, mm::Vec3& out, TRANS_TYPE type) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return GetObjectTransform(gf::GfObjUtil::getObj(handle), out, type);
}

bool GetNodePosition(gf::GF_OBJ_HANDLE* handle, const char* node, mm::Vec3& out) {
    gf::GfObj* obj = gf::GfObjUtil::getObj(handle);
    if (obj == nullptr) {
        return false;
    }
    gf::GfObjAcc acc(obj);
    int bone = acc.getBoneIdx(node);
    if (bone < 0) {
        return false;
    }
    fw::Transform transform;
    acc.getBoneTransform(transform, bone);
    out = transform.position;
    return true;
}

// the trust stage's bounds: its row's KizunaMin and KizunaMax in BDAT file 51 (the trust stages' table)
void GetKizunaMinMax(int stage, int& min, int& max) {
    int id = CovertKizunaStageToID(stage);
    unsigned char* fp = gf::GfDataBdat::getFP(51);
    min = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "KizunaMin", id, 2)));
    max = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "KizunaMax", id, 2)));
}

int CovertKizunaStageToID(int stage) {
    return 7 - stage;
}

bool CheckInRange(const mm::Vec3& a, const mm::Vec3& b, float range, bool xz) {
    float length = xz ? CalcLengthXZ(a, b) : (a - b).length();
    return length <= range;
}

}  // namespace Misc

ShakeCameraManager::ShakeCameraManager() : m_stopEternalShake(false) {}

ShakeCameraManager::~ShakeCameraManager() {
    for (ShakeCameraElement* element : m_elements) {
        delete element;
    }
}

void ShakeCameraManager::RegisterData(ShakeCameraElement* element) {
    if (m_elements.size() == m_elements.capacity()) {
        ShakeCameraElement* oldest = *m_elements.begin();
        m_elements.erase(m_elements.begin());
        delete oldest;
    }
    m_elements.push_back(element);
}

void ShakeCameraManager::Update(const fw::UpdateInfo& info) {
    for (ShakeCameraElement** it = m_elements.begin(); it != m_elements.end();) {
        ShakeCameraElement* element = *it;
        if (m_stopEternalShake) {
            element->StopEternalShake();
        }
        float deltaTime = *(element->m_useFrameTime ? &info.m_frameTime : &info.m_deltaTime);
        if (element->Update(deltaTime)) {
            m_elements.erase(it);
            delete element;
        } else {
            ++it;
        }
    }
    m_stopEternalShake = false;
}

ShakeCameraElementRandom::ShakeCameraElementRandom()
    : m_phase(0), m_phaseTimer(0.0f), m_vertical(false), m_started(false) {
    m_shift = mm::Vec3::zero;
    m_nextShift = mm::Vec3::zero;
}

void ShakeCameraElementRandom::StopEternalShake() {
    if (m_duration < 0.0f) {
        m_duration = 0.0f;
    }
}

ShakeCameraElementAxis::ShakeCameraElementAxis() : m_stepCount(0), m_step(0), m_repeated(0), m_flag(false) {}

bool ShakeCameraElementAxis::Update(float deltaTime) {
    float timer = m_timer + deltaTime;
    m_timer = !(timer >= m_interval) ? timer : timer - m_interval;
    if (!(timer >= m_interval)) {
        return false;
    }
    if (++m_step < m_stepCount) {
        return false;
    }
    if (m_repeated == 0 && m_repeat >= 1) {
        m_step = 0;
        m_repeated = 1;
        return false;
    }
    return true;
}

void ShakeCameraElementCameraAxis::SetData(SHAKE_AXIS axis, int stepCount, int repeat, bool flag) {
    m_axis = mm::Vec3::zero;
    m_stepCount = stepCount;
    m_repeat = repeat;
    m_flag = flag;
    m_cameraAxis = axis;
    switch (axis) {
    case SHAKE_AXIS_NEG_X:
    case SHAKE_AXIS_NEG_Y:
    case SHAKE_AXIS_NEG_Z:
        m_negative = true;
        break;
    default:
        m_negative = false;
        break;
    }
}

}  // namespace btl
