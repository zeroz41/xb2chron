#ifndef ANM_FACTORY_H
#define ANM_FACTORY_H

namespace anm { class ASMControl; }
namespace anm { class Binding; }
namespace anm { class Blender; }
namespace anm { class Control; }
namespace anm { class ExtraTruckBuffer; }
namespace anm { class MirrorMapper; }
namespace anm { class Pose; }
namespace anm { class ResASM; }
namespace anm { class ResResolver; }
namespace anm { class ResStateArray; }
namespace anm { class SimpleMapper; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// the axis a MirrorMapper mirrors across (no value has a name yet)
enum MIRROR_AXIS {};

// anm_factory.cpp: makes anmlib's counted objects in an allocator's memory, each holding its first reference.
// Each gives none (null) for a missing input.
class Factory {
public:
    static Pose* createPose(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    static Control* createControl(const Binding* pBinding, mm::mtl::IAllocator* pAllocator);
    static Blender* createBlender(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    // none either for a slot name the skeleton has not, or a slot without values
    static ExtraTruckBuffer* createExtraTruckBuffer(const Skeleton* pSkeleton, const char* name,
                                                    mm::mtl::IAllocator* pAllocator);
    static MirrorMapper* createMirrorMapper(const Skeleton* pSkeleton, short* pBonePairTable, MIRROR_AXIS axis,
                                            mm::mtl::IAllocator* pAllocator);
    // the mirrored animation's binding; none either for a binding not of the mapper's skeleton
    static Binding* createMirrorAnimation(const Binding* pBinding, const MirrorMapper* pMapper,
                                          mm::mtl::IAllocator* pAllocator);
    static SimpleMapper* createSimpleMapper(const Skeleton* pSrc, const Skeleton* pDst,
                                            mm::mtl::IAllocator* pAllocator);
    // the carried-over animation's binding; none either for a binding not of the mapper's skeleton
    static Binding* createRetargetAnimation(const Binding* pBinding, const SimpleMapper* pMapper,
                                            mm::mtl::IAllocator* pAllocator);
    // the reference pose animation's binding
    static Binding* createReferencePoseAnimation(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    // the state machine resource in *ppAsm; false (printing each) when a clip's bone count is not the skeleton's
    static bool createASMResource(const ResStateArray& states, const ResResolver& resolver,
                                  mm::mtl::IAllocator& allocator, ResASM** ppAsm);
    static ASMControl* createASMControl(const ResASM& res, mm::mtl::IAllocator& allocator);
};
}  // namespace anm

#endif
