#include "classes/gf/GfComEnvSensor.h"
#include "anm/QsTransform.h"
#include "classes/anm/Pose.h"
#include "classes/fw/ParamManager.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComProperty.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComTransform.h"
#include "fw/Message.h"
#include "fw/Transform.h"
#include "fw/ColiCheck.h"
#include "gf/GfEnvProperty.h"
#include "mm/Plane.h"

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

void GfComEnvSensor::flushRootAfterMovement() {
    if (m_rootBone == 0xFFFF) {
        return;
    }
    anm::Pose* pose = m_owner->findComponent<GfComModel>(1)->m_pose;
    if (pose == nullptr) {
        return;
    }
    fw::ReferenceFrame* frame = m_owner->findComponent<GfComTransform>(0)->m_frame.operator->();
    GfComProperty* property = m_owner->getComponent<GfComProperty>(5);
    if (property == nullptr) {
        return;
    }
    GfEnvProperty* env = property->m_env.get();
    if (env == nullptr) {
        return;
    }
    const anm::QsTransform& bone = pose->getBoneModelSpace(m_rootBone);
    const fw::Transform& world = frame->m_worldTransform;
    mm::Vec3 pos;
    world.rotation.rotate(pos, mm::Vec3(bone.m_translation.x, bone.m_translation.y, bone.m_translation.z));
    pos += world.position;
    const FootParam* param = m_footParam.get<FootParam>();
    flushGroundSingle(env, pos, param->m_rootReachUp, param->m_rootReachDown,
                      static_cast<GfEnvProperty::GROUND_INDEX>(7));
}

bool GfComEnvSensor::flushGroundSingle(GfEnvProperty* property, const mm::Vec3& pos, float reachUp, float reachDown,
                                       GfEnvProperty::GROUND_INDEX index) {
    mm::Vec3 start = pos + mm::Vec3(0.0f, reachUp, 0.0f);
    mm::Vec3 end = pos + mm::Vec3(0.0f, -reachDown, 0.0f);
    fw::ColiCheckConfig config;
    config.m_option = false;
    config.m_flags = 9;
    config.m_mask = ~5u;
    fw::TColiCheckResult<256> result;
    fw::ColiCheck::testLine(result, start, end, config);
    if (result.getHitNum() == 0) {
        return false;
    }
    GfEnvProperty::Ground ground;
    ground.m_position = result.getPosition(0);
    const mm::Vec3& point = result.getPosition(0);
    ground.m_plane = mm::Plane(result.getNormal(0), point);
    ground.m_attribute = result.getMaterial(0).m_attribute;
    ground.m_material = result.getMaterial(0).m_id;
    const unsigned char* params = result.getMaterial(0).m_params;
    ground.m_params[0] = params[0];
    ground.m_params[1] = params[1];
    ground.m_params[2] = params[2];
    ground.m_params[3] = params[3];
    ground.m_materialOverride = 0;
    property->m_flags |= 1 << (index + 1);
    property->m_grounds[index] = ground;
    return true;
}

void GfComEnvSensor::EnvListener::onWkStandbyLogout() {
    m_owner->m_pViewer = nullptr;
}

mm::mtl::RTTI GfComEnvSensor::m_rtti("GfComEnvSensor", &GfComponent::m_rtti, nullptr);

}  // namespace gf
