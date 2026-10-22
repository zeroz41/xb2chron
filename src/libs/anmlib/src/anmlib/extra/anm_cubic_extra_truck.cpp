#include "anm/Array.h"
#include "algorithm"
#include "anm/CubicCurve.h"
#include "classes/anm/CubicExtraTruck.h"
#include "anm/ExtraBinding.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "math.h"
#include "mm/MMStdBase.h"

namespace anm {

// a cubic track's value at a frame: the cubic of the last key at or before it
inline void calcValue(const Array<CubicCurve>& curves, float time, float* pValue) {
    ArrayIterartor<const CubicCurve> it = std::upper_bound(curves.begin(), curves.end(), time, CmpCubic());
    unsigned int index;
    if (it == curves.end()) {
        index = curves.size() - 1;
    } else if (it == curves.begin()) {
        index = 0;
    } else {
        index = (it - 1) - curves.begin();
    }
    const CubicCurve& curve = curves[index];
    float frame = time - curve.frame;
#line 65
    MM_ASSERT(frame >= 0.0f);
    *pValue = frame * frame * frame * curve.a + frame * frame * curve.b + frame * curve.c + curve.d;
}

void CubicExtraTruck::sampleTrucks(float time, const Binding& binding, const ExtraBinding& extra, unsigned int count,
                                   float* pOut) const {
#line 85
    MM_ASSERT(binding.m_pAnimation);
    float frame = binding.m_pAnimation->m_frameRate * time;
    bool clampTime = binding.m_pAnimation->m_clampTime;
    float last = binding.m_pAnimation->m_frameCount - 1;
    if (clampTime) {
        if (frame < 0.0f) {
            frame = 0.0f;
        } else {
            frame = frame > last ? last : frame;
        }
    } else {
        frame = fmodf(frame, last);
    }
    for (unsigned int i = 0; i != count; i++) {
        short index = extra.m_indices[i];
        if (index < 0) {
            continue;
        }
        calcValue(m_curves[index], frame, &pOut[i]);
    }
}

}  // namespace anm
