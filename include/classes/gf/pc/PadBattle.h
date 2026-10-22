#ifndef CLASSES_GF_PC_PADBATTLE_H
#define CLASSES_GF_PC_PADBATTLE_H

#include "fw/PadRelay.h"  // the tree: "fw/PadRelay.h"

namespace anm { class ResASM; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B66B38
class PadBattle {
public:
    PadBattle();
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 0
    void setup(int padNo, gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);

    fw::PadRelay m_relay0;  // fields: two relays (PadAgent's destructor destroys both)
    fw::PadRelay m_relay1;
    unsigned char pad_78[0x8];
};

bool registerAsmCallbackBattle(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res);
}}  // namespace gf::pc

#endif
