#include "classes/gf/GfMoveWaterSinkControler.h"
#include "classes/gf/EyeBlinkPlugin.h"
#include "ml/MTRand.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/Plugin.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfMoveWaterSinkControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    float speed = packet.m_speed;
    float sign = speed >= 0.0f ? 1.0f : -1.0f;
    float dt = info.m_deltaTime;
    float size = speed * sign;
    float minSpeed = param->m_minSpeed;
    size = size - dt * param->m_deceleration;
    packet.m_speed = sign * (size > minSpeed ? size : minSpeed);
}

EyeBlinkPlugin::EyeBlinkPlugin() : m_behavior(nullptr), m_timer(0.0f), m_mode(MODE_WAIT) {}

bool EyeBlinkPlugin::setup(gf::GfComBehavior& behavior) {
    m_behavior = &behavior;
    m_paramList = fw::ParamManager::get()->m_paramLists[11];
    return true;
}

void EyeBlinkPlugin::cleanup(gf::GfComBehavior&) {}

// 1.0.0's helpers; 3.0.1 keeps no copy of them (inline)
inline void EyeBlinkPlugin::setMode(Mode mode) {
    GfComAsm* asmCom = m_behavior->m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    const Param* param = getParameter();
    if (param == nullptr) {
        return;
    }
    if (m_mode == mode) {
        return;
    }
    switch (mode) {
    case MODE_CLOSE:
    case MODE_CLOSE_DOUBLE:
        asmCom->easeIn("S_eye_close", param->m_closeTime, AnimLayer(3));
        m_timer = param->m_closeTime + param->m_closedTime;
        break;
    case MODE_OPEN:
    case MODE_OPEN_DOUBLE:
        asmCom->easeOut("S_eye_close", param->m_openTime, AnimLayer(3));
        m_timer = param->m_openTime;
        break;
    case MODE_WAIT: {
        float rate = ml::mtRandf1();
        m_timer = rate * param->m_intervalMax + (1.0f - rate) * param->m_intervalMin;
        break;
    }
    }
    m_mode = mode;
}

inline void EyeBlinkPlugin::resetTimer() {
    const Param* param = getParameter();
    if (param != nullptr) {
        float rate = ml::mtRandf1();
        m_timer = rate * param->m_intervalMax + (1.0f - rate) * param->m_intervalMin;
    }
}

inline const EyeBlinkPlugin::Param* EyeBlinkPlugin::getParameter() const {
    fw::ParamList* list = m_paramList.get();
    if (list == nullptr) {
        return nullptr;
    }
    return list->getAdapter(0).get<Param>();
}

inline bool EyeBlinkPlugin::testDouble() {
    const Param* param = getParameter();
    if (param == nullptr) {
        return false;
    }
    return ml::mtRandf1() < param->m_doubleRate;
}


void EyeBlinkPlugin::onActivate() {
    setMode(MODE_WAIT);
    resetTimer();
}

void EyeBlinkPlugin::onDeactivate() {
    if (m_mode != MODE_WAIT) {
        const Param* param = getParameter();
        GfComAsm* asmCom = m_behavior->m_owner->getComponent<GfComAsm>(2);
        if (param != nullptr && asmCom != nullptr) {
            asmCom->easeOut("S_eye_close", param->m_openTime, AnimLayer(3));
        }
    }
}

void EyeBlinkPlugin::update(gf::GfComBehavior&, const fw::UpdateInfo& info) {
    m_timer -= info.m_deltaTime;
    if (m_timer <= 0.0f) {
        switch (m_mode) {
        case MODE_WAIT:
            setMode(MODE_CLOSE);
            break;
        case MODE_CLOSE:
            setMode(MODE_OPEN);
            break;
        case MODE_OPEN:
            if (testDouble()) {
                setMode(MODE_CLOSE_DOUBLE);
            } else {
                setMode(MODE_WAIT);
            }
            break;
        case MODE_CLOSE_DOUBLE:
            setMode(MODE_OPEN_DOUBLE);
            break;
        case MODE_OPEN_DOUBLE:
            setMode(MODE_WAIT);
            break;
        }
    }
}

mm::mtl::RTTI EyeBlinkPlugin::m_rtti("EyeBlinkPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
