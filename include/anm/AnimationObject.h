#ifndef ANM_ANIMATIONOBJECT_H
#define ANM_ANIMATIONOBJECT_H

#include "mm/MMStdBase.h"
#include "classes/anm/ReferenceObject.h"
#include "classes/mm/mtl/IAllocator.h"

namespace anm {
// the base of anmlib's objects. Its destructor is trivial and inline: the slot-0 destructor of CubicAnimation's,
// EmptyAnimation's, UncompressAnimation's, FootPlacementIKSolver's and Skeleton's tables is this one (clang
// points a trivial inline destructor's slot at its base's), the copy the linker kept lying in
// anm_foot_placement_ik_solver.cpp's range.
// It keeps ReferenceObject's count and allocator at 0x8 to 0x18 and releases itself by the same code
// (Binding's destructor releases its animation with anm_reference_object.h's assertion of `m_pAllocator` at line
// 82), but it cannot derive from ReferenceObject: clang would then point every animation table's slot 0 at
// ReferenceObject's destructor, not at this one. The fields' names are ReferenceObject's (not the original's).
class AnimationObject {
public:
    virtual ~AnimationObject() {}
    void release() const {
        if (m_refEnable != 0) {
            if (--m_refCount <= 0) {
#line 82 ANM_REFERENCE_OBJECT_PATH
                MM_ASSERT(m_pAllocator);
                const_cast<AnimationObject*>(this)->~AnimationObject();
                m_pAllocator->deallocate(const_cast<AnimationObject*>(this));
            }
        }
    }

    mutable short m_refCount;
    unsigned short m_refEnable;
    mm::mtl::IAllocator* m_pAllocator;
};
}  // namespace anm

#endif
