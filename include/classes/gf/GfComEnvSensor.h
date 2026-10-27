#ifndef CLASSES_GF_GFCOMENVSENSOR_H
#define CLASSES_GF_GFCOMENVSENSOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/SensorManager.h"
#include "gf/EnviromentSensor.h"
#include "gf/GfEnvProperty.h"
#include "fw/ParamAdapter.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/UniquePtr.h"
#include "mm/Vec3.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class Transform; }

namespace gf {
// no table: 2 bytes setup makes on request (its info's last flag); flushEnv keeps what a line test from the
// controlled character to the enemy found in it (the field names are not the original's)
class GfEnemySensor {
public:
    GfEnemySensor() : m_blocked(false), m_counter(0) {}
    bool m_blocked;           // the line test's result
    unsigned char m_counter;  // flushEnv tests again each time it wraps past 10
};

// table 0x7100B66108; its m_rtti names GfComponent's as its base
class GfComEnvSensor : public ::gf::GfComponent {
public:
    class EnvListener {
    public:
        EnvListener() {}  // the owner's constructor sets m_owner last
        virtual void onWkStandbyLogout();  // slot 0
        GfComEnvSensor* m_owner;  // its owner (the name is not the original's)
    };
    // setup's argument (the field names are not the original's)
    struct SetupInfo {
        unsigned int m_checkFlags;  // or'ed into m_sensor's
        unsigned int m_paramIndex;  // m_param's entry in the parameter list
        unsigned int m_footMode;    // 2: flushFoot runs after the animation, 1: flushFakeFoot
        bool m_enemySensor;         // makes m_enemySensor
    };
    // m_footParam's parameter block (the names are not the original's)
    struct FootParam {
        float m_retryOffset;    // flushFoot searches again this far ahead of a foot that found no ground
        float m_footReachUp;    // a foot's ground search reaches this far above and below it
        float m_footReachDown;
        float m_rootReachUp;    // the root's
        float m_rootReachDown;
    };

    GfComEnvSensor();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEnvSensor();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void setup(const SetupInfo& info);
    void cleanup();
    void flushRoot();
    void flushFoot();
    void flushFakeFoot();
    void setEnableSensor(bool enable);
    void flushEnv(const fw::Transform& transform);
    void resolveTransform();
    void flushRootAfterMovement();
    bool flushGroundSingle(GfEnvProperty* property, const mm::Vec3& pos, float reachUp, float reachDown,
                           GfEnvProperty::GROUND_INDEX index);
    // m_sensor (inline: the name is not the original's)
    const gf::EnviromentSensor& getSensor() const { return m_sensor; }
    static mm::mtl::RTTI m_rtti;

    gf::EnviromentSensor m_sensor;  // the constructor builds it, flushEnv checks around the object with it
    // the bones setup finds by their labels, 0xFFFF for none: per foot (label kind 0 or 1, index 0-2, at
    // [index * 2 + kind]) and the root (label 15, 2); the names are not the original's
    unsigned short m_footBones[6];
    unsigned short m_rootBone;
    unsigned char pad_2be[0x2];
    // per foot, bit 0: flushFoot places it from the root's ground (setup sets the middle pair's when the root has
    // a bone; the name is not the original's)
    unsigned int m_footFromRoot[6];
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // ParamManager's list 8 (the name is not the original's)
    // its parameter entry (setup takes it from m_paramList by its setup info's index); its first two
    // values reach below and above (TaskFieldCheckWarpBattleWaterDead::update searches that far for water)
    fw::ParamAdapter m_param;
    fw::ParamAdapter m_footParam;  // m_paramList's entry 2, a FootParam (the name is not the original's)
    fw::SensorUpdater m_rootUpdater;  // runs flushRoot before the game (the name is not the original's)
    fw::SensorUpdater m_footUpdater;  // flushFoot or flushFakeFoot after the animation (the name is not the original's)
    mm::mtl::UniquePtr<GfEnemySensor> m_enemySensor;  // (the name is not the original's)
    void* m_pViewer;  // the listener's onWkStandbyLogout clears it (as GfComTransform's does its m_pViewer)
    EnvListener m_listener;  // (the name is not the original's)
};
}  // namespace gf

#endif
