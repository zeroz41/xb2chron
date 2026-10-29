#ifndef CLASSES_GF_PC_PADFIELD_H
#define CLASSES_GF_PC_PADFIELD_H

#include "fw/PadRelay.h"  // the tree: "fw/PadRelay.h"

namespace anm { class ResASM; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// the bit PadField::setInput sets in GfComPropertyPc's action flags (1.0.0's symbols name the type; the values'
// names are not known)
enum InputID : int {};

// table 0x7100B67E60
class PadField {
public:
    PadField();
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 0
    void setup(int padNo, gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);

    // the bound actions (setup binds "decide", "jump", "lock", "wall_release", "lure"; 1.0.0's symbols name them)
    void decideAction() const;
    void jumpAction() const;
    void lockAction() const;
    void wallReleaseAction() const;
    void lureAction() const;
    // the bound axes ("move_front", "move_side"; 1.0.0's symbols name them): the stick's y and x
    void moveFront(float value);
    void moveSide(float value);
    // sets bit id of the property's action flags (1.0.0's symbols name it; 3.0.1 keeps no copy)
    void setInput(InputID id) const;

    fw::PadRelay m_relay;  // PadAgent's destructor destroys it
    // update's property while it updates the relay, else null (the name is not the original's)
    gf::GfComPropertyPc* m_property;
};

// the field's animation callback name (GfComBehaviorPc::setup reads it)
extern const char* ASM_CB_NAME_FIELD;
void registerAsmCallbackField(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res);
}}  // namespace gf::pc

#endif
