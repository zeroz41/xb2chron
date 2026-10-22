#include "mm/Vec4.h"
#include "mm/Quat.h"
#include "mm/mtl/IntrusiveList.h"
#include "anm/AsmBlender.h"
#include "anm/Util.h"
#include "classes/anm/Blender.h"
#include "classes/anm/Skeleton.h"
#include "classes/anm/ResASM.h"
#include "math.h"
#include "anm/Array.h"
#include "anm/Factory.h"
#include "anm/QsTransform.h"
#include "classes/anm/Control.h"
#include "classes/anm/ReferenceObject.h"
#include "mm/Math.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/IntrusivePtr.h"

namespace anm {

// assigned in the body in this order: the original's stores pair up so
AdditiveInfo::AdditiveInfo() {
    m_elapsed = 0.0f;
    m_weight = 1.0f;
    m_scale = 1.0f;
    m_type = InterpolateType(1);
    m_time = 0.01f;
    m_mode = MODE_NONE;
    m_curve = InterpolateCurve(0);
}

void AdditiveInfo::easeIn(AsmBlender* blender, AsmListener* listener, mm::mtl::IntrusivePtr<AsmState> state,
                          float time, float weight, InterpolateType type, InterpolateCurve curve) {
    if (AsmState* current = m_state.get()) {
        current->onLeave(listener);
        m_state->dettach(blender);
        m_state = nullptr;
    }
    m_state = state;
    m_state->setLocalTime(0.0f);
    m_state->attach(blender);
    m_state->onEnter(listener);
    if (fabsf(time) < 1.1920929e-07f) {
        m_state->setWeight(m_scale * weight);
        m_mode = MODE_NONE;
    } else {
        m_time = time;
        m_curve = curve;
        m_type = type;
        m_state->setWeight(0.0f);
        m_mode = MODE_IN;
    }
    m_weight = weight;
    m_elapsed = 0.0f;
}

// easeOut (0x7100877324) is not here yet: 2 words off; the original stores m_elapsed and m_mode as one 64-bit constant:
// void AdditiveInfo::easeOut(AsmBlender* blender, AsmListener* listener, float time, InterpolateType type,
//                            InterpolateCurve curve) {
//     if (!(fabsf(time) < 1.1920929e-07f)) {
//         m_time = time;
//         m_curve = curve;
//         m_type = type;
//         m_elapsed = 0.0f;
//         m_mode = MODE_OUT;
//     } else {
//         if (AsmState* current = m_state.get()) {
//             current->onLeave(listener);
//             m_state->dettach(blender);
//             m_state = nullptr;
//         }
//         m_elapsed = 0.0f;
//         m_mode = MODE_NONE;
//     }
// }

// updateFrame (0x710087742C) is not here yet: the original keeps `m_mode != 0 && m_type == 0` as a value (cset, tbnz) where this branches:
// void AdditiveInfo::updateFrame(float dt, AsmListener* listener) {
//     bool easing = false;
//     if (m_mode != MODE_NONE) {
//         easing = m_type == 0;
//     }
//     if (!easing && m_state.get() != nullptr) {
//         m_state.get()->update(dt, listener);
//     }
// }

// update (0x710087745C) is not here yet: the original computes each branch's weight on its own and shares only the store and the onSetWeight call; this one shares the products too:
// void AdditiveInfo::update(float dt, AsmBlender* blender, AsmListener* listener) {
//     AsmState* state = m_state.get();
//     if (state == nullptr || m_mode == MODE_NONE) {
//         return;
//     }
//     m_elapsed = m_elapsed + dt;
//     float t = m_elapsed / m_time;
//     if (m_mode == MODE_IN) {
//         if (t >= 1.0f) {
//             t = 1.0f;
//             m_mode = MODE_NONE;
//         }
//         if (m_curve == 1) {
//             t = t * (t * t) + t * (t * ((1.0f - t) * 3.0f));
//         }
//         state->setWeight(t * m_weight * m_scale);
//     } else {
//         if (t >= 1.0f) {
//             m_mode = MODE_NONE;
//             state->onLeave(listener);
//             m_state->dettach(blender);
//             m_state = nullptr;
//             return;
//         }
//         if (m_curve == 1) {
//             t = t * (t * t) + t * (t * ((1.0f - t) * 3.0f));
//         }
//         state->setWeight((1.0f - t) * m_weight * m_scale);
//     }
// }

AsmBlender::AsmBlender() : m_pBlender(nullptr), m_skipSample(false) {}

AsmBlender::~AsmBlender() {}

void AsmBlender::setup(const ResASM& res, mm::mtl::IAllocator& allocator) {
    m_pBlender = Factory::createBlender(res.m_pSkeleton, &allocator);
}

void AsmBlender::cleanup() {
    if (m_pBlender != nullptr) {
        m_pBlender->release();
        m_pBlender = nullptr;
    }
    mm::mtl::IntrusiveList<AsmClip>::iterator it = m_clips.begin();
    while (it != m_clips.end()) {
        it = m_clips.erase(it);
    }
    m_skipSample = false;
}

void AsmBlender::sampleTrucks(unsigned int count, QsTransform* pOut) {
    if (m_pBlender != nullptr && !m_skipSample) {
        m_pBlender->sampleTrucks(count, pOut);
    }
    m_skipSample = !m_clips.empty();
    for (mm::mtl::IntrusiveList<AsmClip>::iterator it = m_clips.begin(); it != m_clips.end(); ++it) {
        m_skipSample = m_skipSample & (it->m_pRes->m_pInfo->m_flags >> 2);
    }
}

void AsmBlender::sampleTrucksMS(unsigned int count, QsTransform* pOut) {
    if (m_pBlender != nullptr && !m_skipSample) {
        m_pBlender->sampleTrucksMS(count, pOut);
    }
    m_skipSample = !m_clips.empty();
    for (mm::mtl::IntrusiveList<AsmClip>::iterator it = m_clips.begin(); it != m_clips.end(); ++it) {
        m_skipSample = m_skipSample & (it->m_pRes->m_pInfo->m_flags >> 2);
    }
}

// getDeltaExtractMotion (0x71008778B0) is not here yet: its data flow is the original's; the original schedules the blend's loads and products differently:
// void AsmBlender::getDeltaExtractMotion(float dt, QsTransform* pOut) const {
// #line 133
//     MM_ASSERT(m_pBlender);
//     pOut->m_translation = mm::Vec4::zero;
//     pOut->m_rotation = mm::Quat::zero;
//     pOut->m_scale = mm::Vec4::zero;
//     bool found = false;
//     float total = 0.0f;
//     for (mm::mtl::IntrusiveList<AsmClip>::iterator it = m_clips.begin(); it != m_clips.end(); ++it) {
//         const Control* control = it->m_pControl;
//         const Binding* binding = control->m_pBinding;
//         float weight = control->m_weight;
//         char hint = Util::getBlendHint(*binding);
//         QsTransform delta;
//         if (weight > 1.1920929e-07f && hint != 1 &&
//             Util::calcDeltaExtractMotion(*binding, control->m_localTime, dt, it->m_pRes->m_start, it->m_pRes->m_end,
//                                          &delta)) {
//             pOut->m_translation = weight * delta.m_translation + pOut->m_translation;
//             total += weight;
//             found = true;
//             pOut->m_scale = weight * delta.m_scale + pOut->m_scale;
//             float sign = delta.m_rotation.x * pOut->m_rotation.x + delta.m_rotation.y * pOut->m_rotation.y +
//                                  delta.m_rotation.z * pOut->m_rotation.z + delta.m_rotation.w * pOut->m_rotation.w >=
//                              0.0f
//                              ? 1.0f
//                              : -1.0f;
//             pOut->m_rotation = pOut->m_rotation + weight * (delta.m_rotation * sign);
//         }
//     }
//     if (found && total > 1.1920929e-07f) {
//         float scale = 1.0f / total;
//         pOut->m_translation = scale * pOut->m_translation;
//         pOut->m_scale = scale * pOut->m_scale;
//         mm::Quat& rotation = pOut->m_rotation;
//         float x = scale * rotation.x;
//         rotation.x = x;
//         float y = scale * rotation.y;
//         rotation.y = y;
//         float z = scale * rotation.z;
//         rotation.z = z;
//         float w = scale * rotation.w;
//         rotation.w = w;
//         float length = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
//         rotation.x = rotation.x * length;
//         rotation.y = length * rotation.y;
//         rotation.z = length * rotation.z;
//         rotation.w = length * rotation.w;
//         return;
//     }
//     pOut->m_translation = mm::Vec4::zero;
//     pOut->m_rotation = mm::Quat::identity;
//     pOut->m_scale = mm::Vec4::unit;
// }

void AsmBlender::sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut) {
    if (m_pBlender != nullptr) {
        m_pBlender->sampleExtraTrucks(slot, count, pOut);
        Util::clampLimitExtraTruck(m_pBlender->m_pSkeleton->m_extraTruckSlots[slot], count, pOut);
    }
}

bool AsmBlender::addClip(AsmClip& clip) {
    if (clip.m_pControl == nullptr || !m_pBlender->addControl(clip.m_pControl)) {
        return false;
    }
    m_clips.push_back(&clip);
    m_skipSample = false;
    return true;
}

void AsmBlender::removeClip(AsmClip& clip) {
    if (clip.m_pControl != nullptr && m_pBlender->removeControl(clip.m_pControl)) {
        m_clips.remove(&clip);
    }
    m_skipSample = false;
}

}  // namespace anm
