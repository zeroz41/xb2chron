#ifndef CLASSES_ANM_ASMCONTROL_H
#define CLASSES_ANM_ASMCONTROL_H

#include "classes/anm/ReferenceObject.h"

namespace anm { class ResASM; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B81178; plays an animation state machine resource
class ASMControl : public ::anm::ReferenceObject {
public:
    ASMControl(const ResASM& res, mm::mtl::IAllocator& allocator);
    virtual ~ASMControl();  // slot 0

    unsigned char pad_18[0x398];  // Factory::createASMControl allocates 0x3B0 bytes (at 16-byte alignment)
};
}  // namespace anm

#endif
