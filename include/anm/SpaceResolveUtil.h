#ifndef ANM_SPACERESOLVEUTIL_H
#define ANM_SPACERESOLVEUTIL_H

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class Skeleton; }

namespace anm {
// conversions of a pose's transforms between each bone's own (local) space and model space (SpaceResolveUtil.cpp)
class SpaceResolveUtil {
public:
    // the model-space pose of the bones `binding` gives no track, from the skeleton's reference pose; false when
    // the binding's bone count is not the skeleton's
    static bool clacPoseMSNoTruck(const Binding* pBinding, const Skeleton* pSkeleton, QsTransform* pPose);
    // every bone's transform from model space to its parent's space, the last bone first
    static void convertMStoLS(const Skeleton* pSkeleton, QsTransform* pPose);
    // the same for the bones `pFlags` marks
    static void convertMStoLSPartial(const Skeleton* pSkeleton, const bool* pFlags, QsTransform* pPose);
    // the reference pose's transform for the bones `binding` gives no track; false when the binding's bone count
    // is not the skeleton's
    static bool setReferencePoseNoTruck(const Binding* pBinding, const Skeleton* pSkeleton, QsTransform* pPose);
    // every bone's transform from its parent's space to model space, the first bone first
    static void convertLStoMS(const Skeleton* pSkeleton, QsTransform* pPose);
    // the same for the bones `pFlags` marks
    static void convertLStoMSPartial(const Skeleton* pSkeleton, const bool* pFlags, QsTransform* pPose);
};
}  // namespace anm

#endif
