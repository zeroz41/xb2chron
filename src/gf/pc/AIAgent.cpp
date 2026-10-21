#include "classes/gf/pc/AIAgent.h"

namespace gf { namespace pc {

AIAgent::AIAgent() : m_aiFlags(0) {}

AIAgent::~AIAgent() {}

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
