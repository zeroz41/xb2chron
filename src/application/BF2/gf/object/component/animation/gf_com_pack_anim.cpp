#include "mm/mtl/FixedVector.h"
#include "classes/anm/ReferenceObject.h"
#include "classes/anm/Control.h"
#include "classes/anm/Binding.h"
#include "classes/fw/AnimControlUpdater.h"
#include "classes/fw/AnimSinglePoseSamper.h"
#include "classes/fw/AnimationManager.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComPackAnim.h"
#include "anm/AnimationImporter.h"
#include "anm/Factory.h"
#include "anm/Util.h"
#include "arc/CArcData.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocator.h"
#include "classes/fw/UpdatableObject.h"
#include "mm/mtl/FixStr.h"

namespace gf {

void GfComPackAnim::Mot::stop(unsigned int layer) {
    if (m_control == nullptr) {
        return;
    }
    m_playBackTime = 0.0f;
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        if (m_sampler.isBind()) {
            manager->removePoseSampler(layer, m_sampler);
        }
        if (m_updater.isBind()) {
            manager->removeControlUpdater(layer, m_updater);
        }
    }
    m_sampler.unbind();
    m_updater.unbind();
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
}

void GfComPackAnim::Mot::play(unsigned int layer, void* data, bool sampleFlag) {
    if (m_model == nullptr) {
        return;
    }
    anm::Pose* pose = m_model->m_pose;
    if (pose == nullptr) {
        return;
    }
    anm::ExtraTruckBuffer* extra = m_model->m_extraTruckBuffer;
    anm::Binding* binding = anm::AnimationImporter::import(data);
    m_playBackTime = anm::Util::getPlayBackTime(*binding);
    m_control = anm::Factory::createControl(binding, getAllocator(ALLOCATOR(7)));
    if (binding != nullptr) {
        binding->release();
    }
    m_updater.bind(m_control);
    m_sampler.m_sampleFlag = sampleFlag;
    m_sampler.bind(m_control, pose, extra);
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        if (m_updater.isBind()) {
            manager->addControlUpdater(layer, m_updater);
        }
        if (m_sampler.isBind()) {
            manager->addPoseSampler(layer, m_sampler);
        }
    }
}

GfComPackAnim::GfComPackAnim() : m_sampleFlag(true) {}

GfComPackAnim::~GfComPackAnim() {}

void GfComPackAnim::cleanup() {
    m_mot.cleanup(getLayer());
    for (arc::CArcData** it = m_archives.begin(); it != m_archives.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
    m_archives.clear();
}

void GfComPackAnim::setup(const SetupInfo& info) {
    cleanup();
    for (void* const* it = info.m_archives.begin(); it != info.m_archives.end(); ++it) {
        if (*it != nullptr) {
#line 208
            m_archives.push_back(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) arc::CArcData(*it));
        }
    }
    m_sampleFlag = info.m_sampleFlag;
    play(info.m_name);
}

void GfComPackAnim::play(const char* name) {
    if (name == nullptr) {
        // stops here: an undefined instruction
        asm volatile(".inst 0xe7ffdefe");
        __builtin_unreachable();
    }
    if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
        m_mot.setup(model, getLayer());
    }
    m_mot.stop(getLayer());
    mm::mtl::FixStr<64> path;
    path.format("%s.anm", name);
    for (arc::CArcData** it = m_archives.begin(); it != m_archives.end(); ++it) {
        if (void* data = (*it)->getFileAdr(path.m_str)) {
            m_mot.play(getLayer(), data, m_sampleFlag);
            return;
        }
    }
}

void GfComPackAnim::play(void* data) {
    if (data == nullptr) {
        return;
    }
    if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
        m_mot.setup(model, getLayer());
    }
    m_mot.stop(getLayer());
    m_mot.play(getLayer(), data, m_sampleFlag);
}

bool GfComPackAnim::isPlayEnd() const { return m_mot.isPlayEnd(); }

void GfComPackAnim::setSpeed(float speed) { m_mot.setSpeed(speed); }

void GfComPackAnim::changeLayer(unsigned int, unsigned int) {}

mm::mtl::RTTI GfComPackAnim::m_rtti("GfComPackAnim", &GfComAnimation::m_rtti, nullptr);

}  // namespace gf
