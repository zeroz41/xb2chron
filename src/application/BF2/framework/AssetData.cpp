#include "classes/fw/AssetData.h"
#include "classes/fw/AssetManager.h"
#include "mtl/MemManager.h"
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

AssetData::~AssetData() {
    if (m_data != nullptr) {
        if (m_allocator != nullptr) {
            m_allocator->deallocate(m_data);
        } else {
            mtl::MemManager::deallocate(m_data, 0, false);
        }
        m_data = nullptr;
    }
    AssetManager::sys()->removeAsset(this);
}

}  // namespace fw
