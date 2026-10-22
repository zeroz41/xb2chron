#include "anm/Util.h"
#include "anm/Array.h"
#include "anm/SerialiseArg.h"
#include "anm/ExtraBinding.h"
#include "classes/anm/UncompressExtraTruck.h"
#include "classes/anm/CubicExtraTruck.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "math.h"
#include "mm/MMStdBase.h"
#include <new>

namespace anm {

ExtraBinding::ExtraBinding(const SerialiseArg& arg) {
    if (m_pTruck != nullptr) {
        switch (m_pTruck->m_type) {
        case 0:
            new (m_pTruck) UncompressExtraTruck(arg);
            break;
        case 1:
            new (m_pTruck) CubicExtraTruck(arg);
            break;
        }
    }
}

void UncompressExtraTruck::sampleTrucks(float time, const Binding& binding, const ExtraBinding& extra,
                                        unsigned int count, float* pOut) const {
#line 27
    MM_ASSERT(binding.m_pAnimation);
    float frame = binding.m_pAnimation->m_frameRate * time;
    bool clampTime = binding.m_pAnimation->m_clampTime;
    float last = binding.m_pAnimation->m_frameCount - 1;
    if (clampTime) {
        frame = clamp(frame, 0.0f, last);
    } else {
        frame = fmodf(frame, last);
    }
    float whole;
    float t = modff(frame, &whole);
    unsigned int frameCount = binding.m_pAnimation->m_frameCount;
    unsigned int frame0 = whole;
    unsigned int stride = m_values.size() / frameCount;
    unsigned int frame1 = frame0 + 1 >= frameCount ? 0 : frame0 + 1;
    for (unsigned int i = 0; i != count; i++) {
        short index = extra.m_indices[i];
        if (index < 0) {
            continue;
        }
        pOut[i] = (1.0f - t) * m_values[index + frame0 * stride] + t * m_values[index + frame1 * stride];
    }
}

}  // namespace anm
