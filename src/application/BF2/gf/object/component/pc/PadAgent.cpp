#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComPropertyPc.h"
#include "fw/PadRelay.h"
#include "classes/gf/pc/PadBattle.h"
#include "classes/gf/pc/PadField.h"
#include "classes/gf/pc/PadAgent.h"

namespace gf { namespace pc {

void registerAsmCallback(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res, fw::EffectResData*) {
    if (res != nullptr) {
        registerAsmCallbackField(obj, res);
        registerAsmCallbackBattle(obj, res);
    }
}

PadAgent::PadAgent(unsigned int padNo) : m_padNo(padNo) {}

void PadAgent::setup(GfComPropertyPc& property) {
    m_battle.setup(m_padNo, property);
    m_field.setup(m_padNo, property);
}

void PadAgent::cleanup(GfComPropertyPc& property) {
    m_battle.cleanup(property);
    m_field.cleanup(property);
}

void PadAgent::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    property.m_prevInputDir = property.m_inputDir;
    property.m_prevInputFlags = property.m_inputFlags;
    property.m_inputFlags.reset();
    m_battle.update(info, property);
    m_field.update(info, property);
}

PadAgent::~PadAgent() {}

mm::mtl::RTTI PadAgent::m_rtti("PadAgent", &Agent::m_rtti, nullptr);

}}  // namespace gf::pc
