#include "mm/Vec4.h"
#include "mm/Quat.h"
#include "classes/anm/Animation.h"
#include "classes/anm/UncompressAnimation.h"
#include "classes/anm/Skeleton.h"
#include "anm/BlendUtil.h"
#include "math.h"
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "anm/SerialiseArg.h"
#include "anm/TransformUtil.h"
#include "classes/anm/Binding.h"
#include "mm/MMStdBase.h"

namespace anm {

UncompressAnimation::UncompressAnimation(const SerialiseArg&) {}

// sampleTrucks (0x71008836B0) is not here yet: written as below its data flow is the original's; the original keeps
// frame0 + 1 in a register for the wrap (csel, where this folds it into csinc), multiplies the track count by the
// first frame the other way round, and orders the normalization's last sum the other way round
// void UncompressAnimation::sampleTrucks(float time, const Binding& binding, QsTransform* pDst) const {
//     float frame = m_frameRate * time;
//     float last = m_frameCount - 1;
//     if (m_clampTime) {
//         float clamped = frame > last ? last : frame;
//         frame = frame < 0.0f ? 0.0f : clamped;
//     } else {
//         frame = fmodf(frame, last);
//     }
//     float whole;
//     float blend = modff(frame, &whole);
//     unsigned int count = binding.m_indexTable.size();
//     if (count == 0) {
//         return;
//     }
//     unsigned int frameCount = m_frameCount;
//     unsigned int trackCount = m_transforms.size() / frameCount;
//     unsigned int frame0 = whole;
//     unsigned int frame1 = frame0 + 1 < frameCount ? frame0 + 1 : 0;
//     float rest = 1.0f - blend;
//     unsigned int base0 = trackCount * frame0;
//     unsigned int base1 = frame1 * trackCount;
//     for (unsigned int i = 0; i != count; i++, pDst++) {
//         short track = binding.m_indexTable[i];
//         if (track < 0) {
//             continue;
//         }
//         const QsTransform& from = m_transforms[track + base0];
//         const QsTransform& to = m_transforms[track + base1];
//         pDst->m_translation = rest * from.m_translation + blend * to.m_translation;
//         pDst->m_rotation = rest * from.m_rotation + blend * to.m_rotation;
//         mm::Quat& rotation = pDst->m_rotation;
//         float scale = 1.0f / sqrtf(rotation.x * rotation.x + rotation.y * rotation.y + rotation.z * rotation.z +
//                                    rotation.w * rotation.w);
//         rotation.x = rotation.x * scale;
//         rotation.y = scale * rotation.y;
//         rotation.z = scale * rotation.z;
//         rotation.w = scale * rotation.w;
//         pDst->m_scale = rest * from.m_scale + blend * to.m_scale;
//     }
// }

int UncompressAnimation::getImplType() const {
    return 0;
}

void BlendUtil::blendNormal(const BlendSrc& src, BlendNormalDst* pDst) {
    for (unsigned int i = 0; i < src.count; i++) {
        float weight = src.weight * src.pWeights[i];
        if (weight > 0.0f) {
            const QsTransform& from = src.pTransforms[i];
            QsTransform& to = pDst->pTransforms[i];
            to.m_translation = weight * from.m_translation + to.m_translation;
            to.m_scale = weight * from.m_scale + to.m_scale;
            float sign = from.m_rotation.x * to.m_rotation.x + from.m_rotation.y * to.m_rotation.y +
                                 from.m_rotation.z * to.m_rotation.z + from.m_rotation.w * to.m_rotation.w >=
                             0.0f
                             ? 1.0f
                             : -1.0f;
            to.m_rotation = to.m_rotation + weight * (from.m_rotation * sign);
        }
        pDst->pWeights[i] = weight + pDst->pWeights[i];
    }
}

void BlendUtil::normalizePose(const NormalizeSrc& src, QsTransform* pTransforms) {
    for (unsigned int i = 0; i < src.count; i++) {
        float weight = src.pWeights[i];
        if (weight == 0.0f) {
            pTransforms[i] = src.pReference[i];
        } else {
            float scale = 1.0f / weight;
            QsTransform& transform = pTransforms[i];
            transform.m_translation.x = scale * transform.m_translation.x;
            transform.m_translation.y = scale * transform.m_translation.y;
            transform.m_translation.z = scale * transform.m_translation.z;
            transform.m_translation.w = scale * transform.m_translation.w;
            transform.m_scale.x = scale * transform.m_scale.x;
            transform.m_scale.y = scale * transform.m_scale.y;
            transform.m_scale.z = scale * transform.m_scale.z;
            transform.m_scale.w = scale * transform.m_scale.w;
            mm::Quat& rotation = transform.m_rotation;
            float x = scale * rotation.x;
            rotation.x = x;
            float y = scale * rotation.y;
            rotation.y = y;
            float z = scale * rotation.z;
            rotation.z = z;
            float w = scale * rotation.w;
            rotation.w = w;
            float length = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
            rotation.x = rotation.x * length;
            rotation.y = length * rotation.y;
            rotation.z = length * rotation.z;
            rotation.w = length * rotation.w;
        }
    }
}

// normalizePoseMS (0x7100883CF4) is not here yet: written as below it differs from the original in one instruction:
// the original recomputes the parent table's index (i & 0xFFFF) in 64 bits for the load, where this reuses the
// assertion's 32-bit one
// void BlendUtil::normalizePoseMS(const NormalizeMSSrc& src, QsTransform* pTransforms) {
//     const Skeleton* skeleton = src.pSkeleton;
//     unsigned int count = skeleton->m_bones.size();
//     for (unsigned int i = 0; i != count; i++) {
//         float weight = src.pWeights[i];
//         if (weight == 0.0f) {
//             short parent = skeleton->m_parents[static_cast<unsigned short>(i)];
//             if (parent == -1) {
//                 pTransforms[i] = skeleton->m_referencePose[i];
//             } else {
//                 TransformUtil::mul(pTransforms[parent], skeleton->m_referencePose[i], &pTransforms[i]);
//             }
//         } else {
//             float scale = 1.0f / weight;
//             QsTransform& transform = pTransforms[i];
//             transform.m_translation.x = scale * transform.m_translation.x;
//             transform.m_translation.y = scale * transform.m_translation.y;
//             transform.m_translation.z = scale * transform.m_translation.z;
//             transform.m_translation.w = scale * transform.m_translation.w;
//             transform.m_scale.x = scale * transform.m_scale.x;
//             transform.m_scale.y = scale * transform.m_scale.y;
//             transform.m_scale.z = scale * transform.m_scale.z;
//             transform.m_scale.w = scale * transform.m_scale.w;
//             mm::Quat& rotation = transform.m_rotation;
//             float x = scale * rotation.x;
//             rotation.x = x;
//             float y = scale * rotation.y;
//             rotation.y = y;
//             float z = scale * rotation.z;
//             rotation.z = z;
//             float w = scale * rotation.w;
//             rotation.w = w;
//             float length = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
//             rotation.x = rotation.x * length;
//             rotation.y = length * rotation.y;
//             rotation.z = length * rotation.z;
//             rotation.w = length * rotation.w;
//         }
//     }
// }

void BlendUtil::blendAdd(const BlendSrc& src, BlendAddDst* pDst) {
    QsTransform* transforms = pDst->pTransforms;
    for (unsigned int i = 0; i < src.count; i++) {
        float weight = src.weight * src.pWeights[i];
        if (weight > 0.0f) {
            QsTransform& to = transforms[i];
            QsTransform added;
            TransformUtil::mul(to, src.pTransforms[i], &added);
            float rest = 1.0f - weight;
            to.m_translation = rest * to.m_translation + weight * added.m_translation;
            mm::Quat& rotation = to.m_rotation;
            float sign = rotation.x * added.m_rotation.x + rotation.y * added.m_rotation.y +
                                 rotation.z * added.m_rotation.z + rotation.w * added.m_rotation.w >=
                             0.0f
                             ? 1.0f
                             : -1.0f;
            mm::Quat signedRotation(added.m_rotation.x * sign, added.m_rotation.y * sign, added.m_rotation.z * sign,
                                    added.m_rotation.w * sign);
            rotation = rest * rotation + weight * signedRotation;
            float lengthSq = rotation.x * rotation.x + rotation.y * rotation.y;
            lengthSq = rotation.z * rotation.z + lengthSq;
            lengthSq = rotation.w * rotation.w + lengthSq;
            float length = 1.0f / sqrtf(lengthSq);
            rotation.x = rotation.x * length;
            rotation.y = length * rotation.y;
            rotation.z = length * rotation.z;
            rotation.w = length * rotation.w;
            to.m_scale = rest * to.m_scale + weight * added.m_scale;
        }
    }
}

void BlendUtil::blendNormalExtraTruck(const BlendExtraTruckSrc& src, BlendNormalExtraTruckDst* pDst) {
    for (unsigned int i = 0; i < src.count; i++) {
        if ((*src.pIndices)[i] != -1) {
            pDst->pValues[i] = src.weight * src.pValues[i] + pDst->pValues[i];
            pDst->pWeights[i] = src.weight + pDst->pWeights[i];
        }
    }
}

void BlendUtil::blendAddExtraTruck(const BlendExtraTruckSrc& src, BlendAddExtraTruckDst* pDst) {
    for (unsigned int i = 0; i < src.count; i++) {
        if ((*src.pIndices)[i] != -1) {
            pDst->pValues[i] = src.weight * src.pValues[i] + pDst->pValues[i];
        }
    }
}

void BlendUtil::normalizeExtraTruck(const NormalizeExtraTruckSrc& src, float* pValues) {
#line 178
    MM_ASSERT(src.pSlot);
    for (unsigned int i = 0; i < src.count; i++) {
        float weight = src.pWeights[i];
        if (weight <= 0.0f) {
            pValues[i] = (*src.pDefaults)[i];
        } else if (weight > 1.0f) {
            pValues[i] = pValues[i] / weight;
        }
    }
}

}  // namespace anm
