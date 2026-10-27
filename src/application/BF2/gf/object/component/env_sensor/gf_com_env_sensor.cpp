#include "classes/gf/GfComEnvSensor.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComTransform.h"
#include "fw/Message.h"
#include "fw/Transform.h"

namespace gf {

bool GfComEnvSensor::recieveMessage(fw::MessageObject*, fw::Message& msg) {
    return msg.m_id == 0x1000003;
}

GfComEnvSensor::GfComEnvSensor() : m_rootBone(0xFFFF), m_pViewer(nullptr) {
    m_footBones[0] = 0xFFFF;
    m_footBones[1] = 0xFFFF;
    m_footBones[2] = 0xFFFF;
    m_footBones[3] = 0xFFFF;
    m_footBones[4] = 0xFFFF;
    m_footBones[5] = 0xFFFF;
    m_footFromRoot[0] = 0;
    m_footFromRoot[1] = 0;
    m_footFromRoot[2] = 0;
    m_footFromRoot[3] = 0;
    m_footFromRoot[4] = 0;
    m_footFromRoot[5] = 0;
    m_listener.m_owner = this;
}

GfComEnvSensor::~GfComEnvSensor() {}

void GfComEnvSensor::flushRoot() {
    resolveTransform();
    flushEnv(m_owner->findComponent<GfComTransform>(0)->m_frame->m_worldTransform);
}

void GfComEnvSensor::cleanup() {
    m_enemySensor.reset();
    if (fw::SensorManager* manager = fw::SensorManager::sys()) {
        if (m_rootUpdater.m_registered) {
            manager->removeUpdaterBeforeGame(getLayer(), m_rootUpdater);
        }
        if (m_footUpdater.m_registered) {
            manager->removeUpdaterAfterAnimation(getLayer(), m_footUpdater);
        }
    }
}

void GfComEnvSensor::changeLayer(unsigned int oldLayer, unsigned int newLayer) {
    if (fw::SensorManager* manager = fw::SensorManager::sys()) {
        if (m_rootUpdater.m_registered) {
            manager->removeUpdaterBeforeGame(oldLayer, m_rootUpdater);
            manager->addUpdaterBeforeGame(newLayer, m_rootUpdater);
        }
        if (m_footUpdater.m_registered) {
            manager->removeUpdaterAfterAnimation(oldLayer, m_footUpdater);
            manager->addUpdaterAfterAnimation(newLayer, m_footUpdater);
        }
    }
}

void GfComEnvSensor::setEnableSensor(bool enable) {
    if (enable) {
        if (!m_rootUpdater.m_registered) {
            if (fw::SensorManager* manager = fw::SensorManager::sys()) {
                manager->addUpdaterBeforeGame(getLayer(), m_rootUpdater);
            }
        }
    } else {
        if (m_rootUpdater.m_registered) {
            if (fw::SensorManager* manager = fw::SensorManager::sys()) {
                manager->removeUpdaterBeforeGame(getLayer(), m_rootUpdater);
            }
        }
    }
}

void GfComEnvSensor::resolveTransform() {
    GfComTransform* transform = m_owner->findComponent<GfComTransform>(0);
    if (transform->m_frame->m_parent != nullptr) {
        transform->m_frame->getLocalTransformForWrite();
    }
    transform->m_frame->getSyncedWorldTransform();
}

void GfComEnvSensor::EnvListener::onWkStandbyLogout() {
    m_owner->m_pViewer = nullptr;
}

mm::mtl::RTTI GfComEnvSensor::m_rtti("GfComEnvSensor", &GfComponent::m_rtti, nullptr);

}  // namespace gf
