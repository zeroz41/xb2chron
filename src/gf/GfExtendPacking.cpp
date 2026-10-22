#include "anm/Array.h"
#include "classes/anm/ResASM.h"
#include "classes/fw/EffectResData.h"
#include "classes/gf/GfExtendResource.h"
#include "classes/gf/GfExtendPacking.h"
#include "classes/gf/GfComSound.h"
#include "fw/SoundResTrigger.h"
#include "anm/AsmAnnotetion.h"

namespace gf {

GfExtendPacking::GfExtendPacking() : GfExtendResource(1), m_pResASM(nullptr), m_pEffectResData(nullptr) {}

GfExtendPacking::~GfExtendPacking() {
    if (m_pResASM != nullptr) {
        m_pResASM->release();
        m_pResASM = nullptr;
    }
    if (m_pEffectResData != nullptr) {
        m_pEffectResData->release();
        m_pEffectResData = nullptr;
    }
}

// registers every queued sound trigger with the state machine resource as an annotation of kind 4
void GfExtendPacking::registerSoundTrigger() {
    if (m_pResASM == nullptr) {
        return;
    }
    for (const fw::ResSoundTrigger* triggers : m_soundTriggers) {
        for (const fw::ResSoundTriggerInfo& info : triggers->m_enterTriggers) {
            anm::AsmAnnotetion annotation;
            annotation.m_name = SOUND_CALLBACK_EVENT_NAME;
            annotation.m_type = 4;
            annotation.m_data = &info;
            m_pResASM->setEnterAnnotation(4, info.m_stateName, annotation);
        }
        for (const fw::ResSoundTriggerInfo& info : triggers->m_leaveTriggers) {
            anm::AsmAnnotetion annotation;
            annotation.m_name = SOUND_CALLBACK_EVENT_NAME;
            annotation.m_type = 4;
            annotation.m_data = &info;
            m_pResASM->setLeaveAnnotation(4, info.m_stateName, annotation);
        }
        if (!triggers->m_frameTriggers.empty()) {
            for (const fw::ResSoundFrameTrigger& trigger : triggers->m_frameTriggers) {
                float frame = trigger.m_frame;
                anm::AsmAnnotetion annotation;
                annotation.m_name = SOUND_CALLBACK_EVENT_NAME;
                annotation.m_type = 4;
                annotation.m_data = &trigger;
                m_pResASM->setFrameAnnotation(4, trigger.m_info.m_stateName, frame, annotation);
            }
            m_pResASM->sortAnnotation(4);
        }
    }
}

mm::mtl::RTTI GfExtendPacking::m_rtti("GfExtendPacking", &GfExtendResource::m_rtti, nullptr);

}  // namespace gf
