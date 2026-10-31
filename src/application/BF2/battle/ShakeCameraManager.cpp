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
