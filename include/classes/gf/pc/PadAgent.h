#ifndef CLASSES_GF_PC_PADAGENT_H
#define CLASSES_GF_PC_PADAGENT_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/pc/Agent.h"
#include "classes/gf/pc/PadBattle.h"
#include "classes/gf/pc/PadField.h"

namespace anm { class ResASM; }
namespace fw { class EffectResData; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B694E8
class PadAgent : public ::gf::pc::Agent {
public:
    PadAgent(unsigned int padNo);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~PadAgent();  // slot 1
    virtual void setup(gf::GfComPropertyPc&);  // slot 3
    virtual void cleanup(gf::GfComPropertyPc&);  // slot 4
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 5
    static mm::mtl::RTTI m_rtti;

    unsigned int m_padNo;  // the constructor's: the pad setup binds both halves to
    PadBattle m_battle;
    PadField m_field;
};

void registerAsmCallback(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res, fw::EffectResData* effect);
}}  // namespace gf::pc

#endif
