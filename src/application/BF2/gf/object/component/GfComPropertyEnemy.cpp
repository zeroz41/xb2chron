#include "gf/FileStaticVec3.h"
#include "gf/GfEnemyBattleProperty.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Transform.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace gf {

GfComPropertyEnemy::GfComPropertyEnemy() {
    m_prevTransform.position = mm::Vec3::zero;
    m_prevTransform.rotation = mm::Quat::identity;
    m_transform.position = mm::Vec3::zero;
    m_transform.rotation = mm::Quat::identity;
}

GfComPropertyEnemy::~GfComPropertyEnemy() {}

void GfComPropertyEnemy::setup(const SetupInfo& info) {
    m_battleProperty.Initialize(*this);
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    m_transform = transform->getFrame()->m_worldTransform;
    m_prevTransform = m_transform;
}

void GfComPropertyEnemy::cleanup() {
    m_battleProperty.Finalize(*this);
}

void GfComPropertyEnemy::flush() {
    m_battleProperty.Update(*this);
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    m_transform = transform->getFrame()->m_worldTransform;
}

void GfComPropertyEnemy::writeBack() {
    m_prevTransform = m_transform;
}

// how far the water surface the env sensor found is above the object; none when it found no water
bool GfComPropertyEnemy::getWaterHeight(float& height) const {
    GfComEnvSensor* sensor = m_owner->getComponent<GfComEnvSensor>(11);
    if (sensor->getSensor().m_flags & 2) {
        GfObjAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
        if (acc.getObj() != nullptr) {
            height = sensor->getSensor().m_vertical.m_water.m_height - acc.getWorldTransformNoSync().position.y;
            return true;
        }
    }
    return false;
}

// the enemy's chest height (its data's, in centimetres) at the object's scale
float GfComPropertyEnemy::getChestHeight() const {
    DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    float height = acc.getChestHeight() * 0.01f;
    GfObjSetup* setup = GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup;
    GfObjSetupEnemy* enemySetup =
        setup->getRTTI()->isKindOf(&GfObjSetupEnemy::m_rtti) ? static_cast<GfObjSetupEnemy*>(setup) : nullptr;
    return height * enemySetup->m_initialScale.x;
}

// the share of the chest height that is water deep enough to die in, by the enemy's act type; none for act types 1
// and 3 (inline: the name is not the original's)
static bool getWaterDeadRate(GF_OBJ_HANDLE* handle, float& rate) {
    DataParamAcc acc(handle);
    switch (acc.getSDataEnemy()->m_actType) {
    case 0:
        rate = btl::BtlSystemBalanceAccess::sys()->m_waterDeadRate0;
        break;
    case 2:
        rate = btl::BtlSystemBalanceAccess::sys()->m_waterDeadRate2;
        break;
    case 1:
    case 3:
        return false;
    default:
        rate = 1.0f;
        break;
    }
    return true;
}

// a field death: the object fell through the dead plane since writeBack, or stands in water deep enough to drown
bool GfComPropertyEnemy::isFieldDeadCondMatched() const {
    GfComEnvSensor* sensor = m_owner->getComponent<GfComEnvSensor>(11);
    if (sensor->getSensor().m_flags & 4) {
        GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
        const fw::Transform& world = transform->getFrame()->getWorldTransform();
        float deadHeight = sensor->getSensor().m_vertical.m_deadPlane.m_height;
        if (deadHeight < m_prevTransform.position.y && world.position.y <= deadHeight) {
            return true;
        }
    }
    float depth;
    bool deep = false;
    bool drowns = true;
    if (getWaterHeight(depth)) {
        float chestHeight = getChestHeight();
        float rate;
        drowns = getWaterDeadRate(static_cast<GfObj*>(m_owner)->m_handle, rate);
        if (!drowns || chestHeight * rate <= depth) {
            deep = true;
        }
    }
    return deep && drowns;
}

mm::mtl::RTTI GfComPropertyEnemy::m_rtti("GfComPropertyEnemy", &GfComProperty::m_rtti, nullptr);

}  // namespace gf
