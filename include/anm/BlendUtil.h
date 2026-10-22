#ifndef ANM_BLENDUTIL_H
#define ANM_BLENDUTIL_H

#include "anm/Array.h"

namespace anm { class QsTransform; class Skeleton; }

namespace anm {

// what anm_blend_util.cpp's functions blend (the field names are not the original's but pSlot's, which
// normalizeExtraTruck's check `src.pSlot` names)

// a pose to blend in: count transforms, each weighted by its weight times the pose's
struct BlendSrc {
    unsigned int count;
    const QsTransform* pTransforms;
    const float* pWeights;
    float weight;
};
// blendNormal's sums: the weighted transforms and the weights
struct BlendNormalDst {
    QsTransform* pTransforms;
    float* pWeights;
};
// blendAdd's pose, the source added onto it
struct BlendAddDst {
    QsTransform* pTransforms;
};
// normalizePose's: count bones, the reference pose's transforms for those with no weight
struct NormalizeSrc {
    unsigned int count;
    const QsTransform* pReference;
    const float* pWeights;
};
// normalizePoseMS's: the skeleton's bones (in model space), its reference pose for those with no weight
struct NormalizeMSSrc {
    const Skeleton* pSkeleton;
    const float* pWeights;
};
// an extra track's values to blend in: count values by their slots' indices, each weighted by the weight
struct BlendExtraTruckSrc {
    unsigned int count;
    const float* pValues;
    const Array<short>* pIndices;
    float weight;
};
struct BlendNormalExtraTruckDst {
    float* pValues;
    float* pWeights;
};
struct BlendAddExtraTruckDst {
    float* pValues;
};
// normalizeExtraTruck's: count values, the defaults for those with no weight
struct NormalizeExtraTruckSrc {
    unsigned int count;
    const Array<float>* pDefaults;
    const float* pWeights;
    const void* pSlot;  // normalizeExtraTruck asserts `src.pSlot`
};

// blending poses and extra tracks: sums of weighted transforms, normalized by the weights' sums
class BlendUtil {
public:
    static void blendNormal(const BlendSrc& src, BlendNormalDst* pDst);
    static void normalizePose(const NormalizeSrc& src, QsTransform* pTransforms);
    static void normalizePoseMS(const NormalizeMSSrc& src, QsTransform* pTransforms);
    static void blendAdd(const BlendSrc& src, BlendAddDst* pDst);
    static void blendNormalExtraTruck(const BlendExtraTruckSrc& src, BlendNormalExtraTruckDst* pDst);
    static void blendAddExtraTruck(const BlendExtraTruckSrc& src, BlendAddExtraTruckDst* pDst);
    static void normalizeExtraTruck(const NormalizeExtraTruckSrc& src, float* pValues);
};

}  // namespace anm

#endif
