#include "mm/Col4.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/SCOM_FADE.h"
#include "classes/gf/pc/FadePlugin.h"
#include "classes/fw/ComponentObject.h"
#include "fw/UpdateInfo.h"

namespace gf { namespace pc {

FadePlugin::FadePlugin() : m_state(0) {}

FadePlugin::~FadePlugin() {}

bool FadePlugin::setup(gf::GfComBehaviorPc& behavior) {
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    m_param = property->m_field.m_paramList->getAdapter(18);
    return true;
}

void FadePlugin::cleanup(gf::GfComBehaviorPc&) {}

void FadePlugin::onActivate() {
    const Param* param = m_param.get<Param>();
    if (m_state != 3) {
        m_state = 3;
        m_time = 0.0f;
        SCOM_FADE::create(1, static_cast<unsigned int>(param->m_fadeTime * 30.0f), mm::Col4::black);
    }
}

void FadePlugin::onDeactivate() {
    if (m_state != 0) {
        m_state = 0;
        m_time = 0.0f;
    }
}

void FadePlugin::update(gf::GfComBehaviorPc&, const fw::UpdateInfo& info) {
    const Param* param = m_param.get<Param>();
    m_time += info.m_deltaTime;
    switch (m_state) {
    case 3:
        if (m_time >= param->m_fadeOutWait) {
            m_state = 2;
            m_time = 0.0f;
        }
        break;
    case 2:
        if (m_time >= param->m_blackWait) {
            const Param* fadeParam = m_param.get<Param>();
            m_state = 1;
            m_time = 0.0f;
            SCOM_FADE::create(1, static_cast<unsigned int>(fadeParam->m_fadeTime * 30.0f), mm::Col4::zero);
        }
        break;
    case 1:
        if (m_time >= param->m_fadeTime) {
            setActivate(false);
        }
        break;
    }
}

mm::mtl::RTTI FadePlugin::m_rtti("FadePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
