#include "classes/anm/Control.h"
#include "anm/AsmListener.h"

#include "anm/AsmBlender.h"
#include "anm/Factory.h"
#include "anm/Util.h"
#include "classes/anm/ResASM.h"

namespace anm {

AsmClip::AsmClip() : m_pControl(nullptr), m_pRes(nullptr) {}

AsmClip::~AsmClip() {
    destroyControl();
}

void AsmClip::destroyControl() {
    if (m_pControl != nullptr) {
        m_pControl->release();
        m_pControl = nullptr;
    }
    m_pRes = nullptr;
}

void AsmClip::createControl(const ResClipData& res, mm::mtl::IAllocator& allocator) {
    m_pControl = Factory::createControl(res.m_pBinding, &allocator);
    m_pRes = &res;
}

// update (0x7100877F10) is not matched yet (6 words: the loop-mode test is scheduled after the listener test; see
// the worker's near-miss copy)

void AsmClip::setLocalTime(float time) {
    if (m_pControl != nullptr) {
        m_pControl->setLocalTime(time);
    }
}

float AsmClip::getLocalTime() const {
    if (m_pControl != nullptr) {
        return m_pControl->m_localTime;
    }
    return 0.0f;
}

void AsmClip::setSpeed(float speed) {
    if (m_pControl != nullptr) {
        m_pControl->m_speed = m_pRes->m_pInfo->m_speed * speed;
    }
}

void AsmClip::setWeight(float weight) {
    if (m_pControl != nullptr) {
        m_pControl->m_weight = m_pRes->m_pInfo->m_weight * weight;
    }
}

}  // namespace anm
