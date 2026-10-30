#include "classes/anm/SimpleRetargetAnimation.h"
#include "classes/anm/SimpleRetargetAnimation.h"
#include "anm/AnimationObject.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/SimpleMapper.h"
#include "classes/anm/ReferenceObject.h"
#include "anm/ExtraBinding.h"
#include "anm/QsTransform.h"
#include "mm/MMStdBase.h"

namespace anm {

SimpleRetargetAnimation::~SimpleRetargetAnimation() {
    if (m_pMapper != nullptr) {
        m_pMapper->release();
        m_pMapper = nullptr;
    }
    if (m_pOriginal != nullptr) {
        m_pOriginal->release();
        m_pOriginal = nullptr;
    }
    if (m_pAllocator != nullptr && m_pExtraBindings != nullptr) {
        m_pAllocator->deallocate(m_pExtraBindings);
    }
}

void SimpleRetargetAnimation::sampleTrucks(float time, const anm::Binding& binding, anm::QsTransform* pOut) const {
    m_pOriginal->m_pAnimation->sampleTrucks(time, binding, pOut);
}

bool SimpleRetargetAnimation::getExtractMotion(float time, anm::QsTransform* pOut) const {
    return m_pOriginal->m_pAnimation->getExtractMotion(time, pOut);
}

bool SimpleRetargetAnimation::getDeltaExtractMotion(float time, float delta, bool loop, anm::QsTransform* pOut) const {
    return m_pOriginal->m_pAnimation->getDeltaExtractMotion(time, delta, loop, pOut);
}

int SimpleRetargetAnimation::getImplType() const {
    return m_pOriginal->m_pAnimation->getImplType();
}

}  // namespace anm
