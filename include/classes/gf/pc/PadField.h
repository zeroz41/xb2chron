#ifndef CLASSES_GF_PC_PADFIELD_H
#define CLASSES_GF_PC_PADFIELD_H

#include "fw/PadRelay.h"  // the tree: "fw/PadRelay.h"

namespace anm { class ResASM; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B67E60
class PadField {
public:
    PadField();
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 0
    void setup(int padNo, gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);

    fw::PadRelay m_relay;  // PadAgent's destructor destroys it
    unsigned char pad_40[0x8];
};

void registerAsmCallbackField(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res);
}}  // namespace gf::pc

#endif
