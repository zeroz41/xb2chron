#include "classes/anm/ExtraTruckBuffer.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ASMControl.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/AnimPoseSamper.h"
#include "classes/fw/AnimAsmPoseSampler.h"
#include "classes/fw/AnimEventAsmPoseSampler.h"
#include "fw/IkResolver.h"
#include "anm/Util.h"
#include "classes/fw/AnimationManager.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ASMControl.h"
#include "classes/anm/Skeleton.h"
#include "classes/anm/Control.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Blender.h"
#include "anm/AsmBlender.h"
#include "anm/ExtraBinding.h"
#include "anm/Util.h"
#include "classes/fw/AnimSinglePoseSamper.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/AnimAfterModifierInterface.h"
#include "classes/fw/AnimPoseSamper.h"
#include "classes/fw/AnimAsmPoseSampler.h"
#include "classes/fw/AnimEventMotPoseSamper.h"
#include "classes/fw/AnimEventAsmPoseSampler.h"
#include <algorithm>


namespace fw {

AnimSinglePoseSamper::AnimSinglePoseSamper()
    : m_control(nullptr), m_pose(nullptr), m_extra(nullptr), m_extraIndex(0xFFFF), m_sampleFlag(true) {}

void AnimSinglePoseSamper::unbind() {
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
    if (m_extra != nullptr) {
        m_extra->release();
        m_extra = nullptr;
    }
    m_extraIndex = 0xFFFF;
}

AnimSinglePoseSamper::~AnimSinglePoseSamper() {
    unbind();
}

void AnimSinglePoseSamper::bind(anm::Control* control, anm::Pose* pose, anm::ExtraTruckBuffer* extra) {
    unbind();
    if (pose->m_pSkeleton->m_bones.size() == control->m_pBinding->m_indexTable.size()) {
        m_control = control;
        control->addRef();
        m_pose = pose;
        pose->addRef();
    }
    if (extra != nullptr) {
        const anm::ExtraTruckSlot* slot = extra->m_pSlot;
        int slotID = extra->m_pSkeleton->getExtraTruckSlotID(slot->m_name);
        m_extraIndex = slotID;
        if (m_extraIndex != 0xFFFF) {
            const anm::Binding* binding = control->m_pBinding;
            if (slotID < binding->m_extraBindings.size() &&
                slot->m_count == binding->m_extraBindings[slotID].m_indices.size()) {
                m_extra = extra;
                extra->addRef();
            }
        }
    }
}

}  // namespace fw

namespace anm {
short Skeleton::getExtraTruckSlotID(const char* name) const {
    if (m_extraTruckSlots.size() != 0) {
        ArrayIterartor<const ExtraTruckSlot> it =
            std::lower_bound(m_extraTruckSlots.begin(), m_extraTruckSlots.end(), name, CompTruck());
        if (it != m_extraTruckSlots.end() && strcmp(it.m_pData->m_name, name) == 0) {
            return std::distance(m_extraTruckSlots.begin(), it);
        }
    }
    return 0xFFFF;
}
}  // namespace anm

namespace fw {

void AnimSinglePoseSamper::samplePose() {
    anm::Util::samplePoseSmartFromControl(m_control, m_pose, m_sampleFlag);
    anm::ExtraTruckBuffer* extra = m_extra;
    if (extra != nullptr) {
        m_control->sampleExtraTrucks(m_extraIndex, extra->m_count, extra->m_pValues);
        anm::Util::clampLimitExtraTruck(*m_extra->m_pSlot, extra->m_count, extra->m_pValues);
    }
}

AnimPoseSamper::~AnimPoseSamper() {
    unbind();
}

void AnimPoseSamper::unbind() {
    if (m_blender != nullptr) {
        m_blender->release();
        m_blender = nullptr;
    }
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
    if (m_extra != nullptr) {
        m_extra->release();
        m_extra = nullptr;
    }
    m_extraIndex = 0xFFFF;
    m_enable = false;
}

void AnimPoseSamper::bind(anm::Blender* blender, anm::Pose* pose, anm::ExtraTruckBuffer* extra) {
    unbind();
    m_blender = blender;
    blender->addRef();
    m_pose = pose;
    pose->addRef();
    if (extra != nullptr) {
        m_extraIndex = extra->m_pSkeleton->getExtraTruckSlotID(extra->m_pSlot->m_name);
        if (m_extraIndex != 0xFFFF) {
            m_extra = extra;
            extra->addRef();
        }
    }
    m_enable = true;
}

void AnimPoseSamper::samplePose() {
    if (m_enable) {
        if (m_sampleFlag) {
            anm::Array<anm::QsTransform>& out = m_pose->accessSyncedPoseLocalSpace();
            m_blender->sampleTrucks(out.size(), out.m_pElements);
            m_pose->syncModelSpace();
        } else {
            anm::Array<anm::QsTransform>& out = m_pose->accessSyncedPoseModelSpace();
            m_blender->sampleTrucksMS(out.size(), out.m_pElements);
        }
        if (m_extra != nullptr) {
            m_blender->sampleExtraTrucks(m_extraIndex, m_extra->m_count, m_extra->m_pValues);
        }
    }
}

AnimAsmPoseSampler::AnimAsmPoseSampler()
    : m_control(nullptr), m_pose(nullptr), m_extra(nullptr), m_extraIndex(0xFFFF), m_sampleFlag(true) {}

AnimAsmPoseSampler::~AnimAsmPoseSampler() {
    unbind();
}

void AnimAsmPoseSampler::unbind() {
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
    if (m_extra != nullptr) {
        m_extra->release();
        m_extra = nullptr;
    }
    m_extraIndex = 0xFFFF;
}

void AnimAsmPoseSampler::bind(anm::ASMControl* control, anm::Pose* pose, anm::ExtraTruckBuffer* extra) {
    unbind();
    m_control = control;
    control->addRef();
    m_pose = pose;
    pose->addRef();
    if (extra != nullptr) {
        m_extraIndex = extra->m_pSkeleton->getExtraTruckSlotID(extra->m_pSlot->m_name);
        if (m_extraIndex != 0xFFFF) {
            m_extra = extra;
            extra->addRef();
        }
    }
}

void AnimAsmPoseSampler::samplePose() {
    if (m_sampleFlag) {
        anm::Array<anm::QsTransform>& out = m_pose->accessSyncedPoseLocalSpace();
        m_control->sampleTrucks(out.size(), out.m_pElements);
        m_pose->syncModelSpace();
    } else {
        anm::Array<anm::QsTransform>& out = m_pose->accessSyncedPoseModelSpace();
        m_control->sampleTrucksMS(out.size(), out.m_pElements);
    }
    if (m_extra != nullptr) {
        m_control->sampleExtraTrucks(m_extraIndex, m_extra->m_count, m_extra->m_pValues);
    }
}

AnimEventMotPoseSamper::AnimEventMotPoseSamper() {}

AnimEventMotPoseSamper::~AnimEventMotPoseSamper() {}

void AnimEventMotPoseSamper::resetPose() {
    if (m_pose != nullptr) {
        m_pose->setReferencePose();
    }
}

AnimEventAsmPoseSampler::AnimEventAsmPoseSampler()
    : m_control(nullptr), m_pose(nullptr), m_extra(nullptr), m_extraIndex(0xFFFF), m_pause(false), m_sampleFlag(true) {}

AnimEventAsmPoseSampler::~AnimEventAsmPoseSampler() {
    unbind();
}

void AnimEventAsmPoseSampler::unbind() {
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
    if (m_extra != nullptr) {
        m_extra->release();
        m_extra = nullptr;
    }
    m_extraIndex = 0xFFFF;
}

void AnimEventAsmPoseSampler::bind(anm::ASMControl* control, anm::Pose* pose, anm::ExtraTruckBuffer* extra) {
    unbind();
    m_control = control;
    if (control != nullptr) {
        control->addRef();
    }
    m_pose = pose;
    pose->addRef();
    if (extra != nullptr) {
        m_extraIndex = extra->m_pSkeleton->getExtraTruckSlotID(extra->m_pSlot->m_name);
        if (m_extraIndex != 0xFFFF) {
            m_extra = extra;
            extra->addRef();
        }
    }
}

void AnimEventAsmPoseSampler::samplePose() {
    if (!m_pause) {
        if (m_control != nullptr) {
            anm::Array<anm::QsTransform>& out = m_pose->accessSyncedPoseLocalSpace();
            m_control->sampleTrucks(out.size(), out.m_pElements);
        } else {
            m_pose->setReferencePose();
        }
        m_pose->syncModelSpace();
        if (m_extra != nullptr) {
            m_control->sampleExtraTrucks(m_extraIndex, m_extra->m_count, m_extra->m_pValues);
        }
    }
}

}  // namespace fw


namespace fw {

const char* AnimAfterModifyJob::_TYPE_NAME = "AnimAfterModifyJob";
const char* AnimIkResolveJob::_TYPE_NAME = "AnimIkResolveJob";
const char* AnimModifyPoseJob::_TYPE_NAME = "AnimModifyPoseJob";
const char* AnimSamplePoseJob::_TYPE_NAME = "AnimSamplePoseJob";

AnimAfterModifyJob::AnimAfterModifyJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(AnimAfterModifyJob), 2), m_count(count) {}

void AnimAfterModifyJob::exec(anm::Job& job) {
    AnimAfterModifyJob& self = static_cast<AnimAfterModifyJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_modifiers[i]->apply();
    }
}

AnimIkResolveJob::AnimIkResolveJob(unsigned int count)
    : anm::Job(_TYPE_NAME, sizeof(AnimIkResolveJob), 3), m_count(count), m_info(nullptr) {}

void AnimIkResolveJob::exec(anm::Job& job) {
    AnimIkResolveJob& self = static_cast<AnimIkResolveJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_resolvers[i]->resolve(*self.m_info);
    }
}


AnimModifyPoseJob::AnimModifyPoseJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(AnimModifyPoseJob), 1), m_count(count) {}

void AnimModifyPoseJob::exec(anm::Job& job) {
    AnimModifyPoseJob& self = static_cast<AnimModifyPoseJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_modifiers[i]->apply();
    }
}

AnimSamplePoseJob::AnimSamplePoseJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(AnimSamplePoseJob), 0), m_count(count) {}

void AnimSamplePoseJob::exec(anm::Job& job) {
    AnimSamplePoseJob& self = static_cast<AnimSamplePoseJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_samplers[i]->samplePose();
    }
}

}  // namespace fw
