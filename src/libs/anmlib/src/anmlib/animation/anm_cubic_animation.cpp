#include "anm/AnimationObject.h"
#include "classes/anm/Animation.h"
#include "anm/CubicCurve.h"
#include "classes/anm/Binding.h"
#include "classes/anm/CubicAnimation.h"
#include "anm/Array.h"
#include "algorithm"
#include "new"
#include "anm/ExtraBinding.h"
#include "anm/Locomotion.h"
#include "anm/QsTransform.h"
#include "anm/SerialiseArg.h"
#include "math.h"
#include "mm/MMStdBase.h"
#include "mm/Quat.h"

namespace anm {

Binding::Binding(mm::mtl::IAllocator* pAllocator) : ReferenceObject(pAllocator) {
    m_indexTable.m_pElements = nullptr;
    m_indexTable.m_size = 0;
    m_extraBindings.m_pElements = nullptr;
    m_extraBindings.m_size = 0;
}

Binding::Binding(const SerialiseArg& arg) {
    ExtraBinding* pExtraBindings = m_extraBindings.m_pElements;
    for (unsigned int i = 0; i < m_extraBindings.size(); i++) {
        new (&pExtraBindings[i]) ExtraBinding(arg);
    }
}

Binding::~Binding() {
    if (m_pAnimation != nullptr) {
        m_pAnimation->release();
        m_pAnimation = nullptr;
    }
}

CubicAnimation::CubicAnimation(const SerialiseArg& arg) {}

void CubicAnimation::sampleTrucks(float time, const Binding& binding, QsTransform* pOut) const {
    float frame = m_frameRate * time;
    bool clampTime = m_clampTime;
    float last = m_frameCount - 1;
    if (clampTime) {
        if (frame < 0.0f) {
            frame = 0.0f;
        } else {
            frame = frame > last ? last : frame;
        }
    } else {
        frame = fmodf(frame, last);
    }
    unsigned int count = binding.m_indexTable.size();
    for (unsigned int i = 0; i != count; i++) {
        short index = binding.m_indexTable[i];
        if (index < 0) {
            continue;
        }
        const CubicTrack& track = m_tracks[index];
        calcVec3(track.m_translation, frame, &pOut[i].m_translation.x);
        pOut[i].m_translation.w = 1.0f;
        calcQuat(track.m_rotation, frame, &pOut[i].m_rotation);
        calcVec3(track.m_scale, frame, &pOut[i].m_scale.x);
        pOut[i].m_scale.w = 1.0f;
    }
}

void calcVec3(const Array<Cubic3Curve>& curves, float time, float* pValue) {
    ArrayIterartor<const Cubic3Curve> it = std::upper_bound(curves.begin(), curves.end(), time, CmpCubic());
    unsigned int index;
    if (it == curves.end()) {
        index = curves.size() - 1;
    } else if (it == curves.begin()) {
        index = 0;
    } else {
        index = (it - 1) - curves.begin();
    }
    const Cubic3Curve& curve = curves[index];
    float frame = time - curve.frame;
#line 74
    MM_ASSERT(frame >= 0.0f);
    for (int i = 0; i < 3; i++) {
        const float* c = curve.coefficients[i];
        pValue[i] = frame * frame * frame * c[0] + frame * frame * c[1] + frame * c[2] + c[3];
    }
}

void calcQuat(const Array<Cubic4Curve>& curves, float time, mm::Quat* pValue) {
    ArrayIterartor<const Cubic4Curve> it = std::upper_bound(curves.begin(), curves.end(), time, CmpCubic());
    unsigned int index;
    if (it == curves.end()) {
        index = curves.size() - 1;
    } else if (it == curves.begin()) {
        index = 0;
    } else {
        index = (it - 1) - curves.begin();
    }
    const Cubic4Curve& curve = curves[index];
    float frame = time - curve.frame;
#line 126
    MM_ASSERT(frame >= 0.0f);
    float* values = &pValue->x;
    for (int i = 0; i < 4; i++) {
        const float* c = curve.coefficients[i];
        values[i] = frame * frame * frame * c[0] + frame * frame * c[1] + frame * c[2] + c[3];
    }
    float lengthSq = pValue->x * pValue->x + pValue->y * pValue->y + pValue->z * pValue->z;
    lengthSq = pValue->w * pValue->w + lengthSq;
    float length = 1.0f / sqrtf(lengthSq);
    pValue->x = pValue->x * length;
    pValue->y = length * pValue->y;
    pValue->z = length * pValue->z;
    pValue->w = length * pValue->w;
}

int CubicAnimation::getImplType() const {
    return 1;
}

}  // namespace anm
