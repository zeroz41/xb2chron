#include "math.h"
#include "anm/Array.h"
#include "anm/ExtraBinding.h"
#include "anm/ExtraTruck.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Control.h"
#include "mm/Math.h"
#include "mm/MMStdBase.h"

namespace anm {

Control::Control(const Binding* pBinding, mm::mtl::IAllocator* pAllocator)
    : ReferenceObject(pAllocator), m_pBinding(pBinding), m_trackWeights(pAllocator), m_localTime(0.0f),
      m_weight(1.0f), m_speed(1.0f), m_flags(0), pad_60(nullptr) {
#line 32
    MM_ASSERT(pBinding);
    pBinding->addRef();
    unsigned int count = m_pBinding->m_indexTable.size();
    m_trackWeights.reserve(count, 8);
    for (unsigned int i = 0; i < count; i++) {
        if (m_pBinding->m_indexTable[i] == -1) {
            m_trackWeights.push_back(0.0f);
        } else {
            m_trackWeights.push_back(1.0f);
        }
    }
    const Animation* animation = m_pBinding->m_pAnimation;
    m_length = animation->m_interval * (animation->m_frameCount - 1);
}

Control::~Control() {
    if (m_pBinding != nullptr) {
        m_pBinding->release();
        m_pBinding = nullptr;
    }
}

void Control::update(float dt) {
    m_localTime += m_speed * dt;
    m_localTime = calcLocalTimeInternal(m_localTime);
}

float Control::calcLocalTimeInternal(float time) {
    if (!m_pBinding->m_pAnimation->m_clampTime) {
        float local = fmodf(time, m_length);
        if (local < 0.0f) {
            local += m_length;
        }
        return local;
    }
    return mm::clamp(time, 0.0f, m_length);
}

void Control::sampleTrucks(unsigned int count, QsTransform* pOut) const {
#line 86
    MM_ASSERT(count == m_pBinding->m_indexTable.size());
    m_pBinding->m_pAnimation->sampleTrucks(m_localTime, *m_pBinding, pOut);
}

bool Control::sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut) {
#line 102
    MM_ASSERT(m_pBinding);
    if (m_pBinding->m_extraBindings.size() != 0) {
        const ExtraBinding& extra = m_pBinding->m_extraBindings[slot];
        if (extra.m_indices.size() == count) {
            if (extra.m_pTruck == nullptr) {
                return false;
            }
            extra.m_pTruck->sampleTrucks(m_localTime, *m_pBinding, extra, count, pOut);
            return true;
        }
    }
    return false;
}

}  // namespace anm
