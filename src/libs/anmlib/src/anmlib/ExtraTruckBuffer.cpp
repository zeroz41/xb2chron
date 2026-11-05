#include "anm/Array.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "classes/anm/Skeleton.h"
#include "mm/MMStdBase.h"

namespace anm {

ExtraTruckBuffer::ExtraTruckBuffer(const Skeleton& skeleton, const ExtraTruckSlot& slot,
                                   mm::mtl::IAllocator* pAllocator)
    : ReferenceObject(pAllocator), m_pSkeleton(&skeleton), m_pSlot(&slot), m_values(pAllocator) {
    m_pSkeleton->addRef();
    m_values.resize(m_pSlot->m_defaults.size());
    ArrayIterartor<const float> src = m_pSlot->m_defaults.begin();
    ArrayIterartor<const float> end = m_pSlot->m_defaults.end();
    for (float* dst = m_values.begin(); src != end; ++src, ++dst) {
        *dst = *src;
    }
}

ExtraTruckBuffer::~ExtraTruckBuffer() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
}

}  // namespace anm
