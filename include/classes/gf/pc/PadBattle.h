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
    // the stick's axes (bound to "move_front" and "move_side"): write the property's input direction
    void moveFront(float value);
    void moveSide(float value);

    fw::PadRelay m_relay0;  // fields: two relays (PadAgent's destructor destroys both)
    fw::PadRelay m_relay1;
    // update's: the property the handlers write while the relays run, null otherwise (the name is not the original's)
    gf::GfComPropertyPc* m_property;
};

bool registerAsmCallbackBattle(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res);
}}  // namespace gf::pc

#endif
