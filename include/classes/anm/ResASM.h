#ifndef CLASSES_ANM_RESASM_H
#define CLASSES_ANM_RESASM_H

#include "anm/Array.h"
#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"

namespace anm { class Binding; }
namespace anm { class ResResolver; }
namespace anm { class ResStateArray; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// a clip's settings (the names are not the original's)
struct ResClipInfo {
    unsigned char pad_0[0xC];
    unsigned int m_flags;  // bit 2: AsmBlender skips sampling while every clip has it
};

// one clip of a state: 0xE8 bytes (the fields' names are not the original's)
struct ResClipData {
    const ResClipInfo* m_pInfo;
    const Binding* m_pBinding;  // Factory::createASMResource checks its bone count against the skeleton's
    float m_start;  // the part of the animation it plays (AsmBlender::getDeltaExtractMotion)
    float m_end;
    unsigned char pad_18[0xD0];
};

// one state of an animation state machine: 0x1E0 bytes
struct ResStateData {
    unsigned char pad_0[0x8];
    mm::mtl::Vector<ResClipData> m_clips;
    unsigned char pad_30[0x1B0];
};

// table 0x7100B81198; an animation state machine's resource: its states and the skeleton their clips are bound to
class ResASM : public ::anm::ReferenceObject {
public:
    ResASM(const ResStateArray& states, const ResResolver& resolver, mm::mtl::IAllocator& allocator);
    virtual ~ResASM();  // slot 0

    const Skeleton* m_pSkeleton;  // the names of the fields are not the original's
    unsigned char pad_20[0x8];
    Array<ResStateData> m_states;
    unsigned char pad_38[0x8];  // Factory::createASMResource allocates 0x40 bytes
};
}  // namespace anm

#endif
