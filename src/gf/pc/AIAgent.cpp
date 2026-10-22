#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/AIAgent.h"

namespace gf { namespace pc {

AIAgent::AIAgent() : m_aiFlags(0) {}

AIAgent::~AIAgent() {}

void AIAgent::setup(GfComPropertyPc& property) {
    if (property.m_setupKind != -1) {
        m_field.setup(property);
    }
    m_battle.setup(property);
}

void AIAgent::cleanup(GfComPropertyPc& property) {
    m_battle.cleanup(property);
    if (property.m_setupKind != -1) {
        m_field.cleanup(property);
    }
}

void AIAgent::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    if (property.m_setupKind != -1 && testFiledAI()) {
        m_field.update(info, property);
    }
    if (testBattleAI()) {
        m_battle.update(info, property);
    }
}

void AIAgent::setFieldAI(GfComPropertyPc& property, bool enable) {
    if (testFiledAI() != enable) {
        if (enable) {
            m_aiFlags |= 1;
            m_field.onActivate(property);
        } else {
            m_aiFlags &= ~1;
            m_field.onDeactivate(property);
        }
    }
}

void AIAgent::setBattleAI(GfComPropertyPc& property, bool enable) {
    if (testBattleAI() != enable) {
        if (enable) {
            m_aiFlags |= 2;
            m_field.onActivate(property);
        } else {
            m_aiFlags &= ~2;
            m_field.onDeactivate(property);
        }
    }
}

mm::mtl::RTTI AIAgent::m_rtti("AIAgent", &Agent::m_rtti, nullptr);

}}  // namespace gf::pc
