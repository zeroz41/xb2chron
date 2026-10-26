#ifndef CLASSES_FW_EFFECTRESDATA_H
#define CLASSES_FW_EFFECTRESDATA_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace anm { class ResASM; }

namespace fw {
// table 0x7100B41350; counted: createEffectResData zeroes the count at 0x8 as ReferenceObject's constructor does and
// takes the first reference, GfExtendPacking's destructor releases it (reference_object.h's `m_RefCount > 0`)
class EffectResData : public ::mm::mtl::ReferenceObject {
public:
    virtual ~EffectResData();  // slot 0
    // GfComEffectCaster::registerAsmCallbackEffect passes its ASM resource, 3 and ASM_CB_NAME_EFFECT ("asm_effect")
    // (the names of the parameters are not the original's)
    void registerAsmAnnotation(anm::ResASM* asmRes, unsigned int type, const char* name);
};
}  // namespace fw

#endif
