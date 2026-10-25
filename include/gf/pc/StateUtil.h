#ifndef GF_PC_STATEUTIL_H
#define GF_PC_STATEUTIL_H

#include "gf/EnviromentSensor.h"
#include "classes/gf/pc/TimerPlugin.h"

namespace fw { class Message; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgObjectNotifyDead; }
namespace gf { class MsgObjectNotifyHealHp; }

namespace gf { namespace pc {

// what the PC's states share (functions, by its symbols)
class StateUtil {
public:
    // hands msg from the PC to the party's drivers and blades (each but the PC itself)
    // StateFieldMove::leave's (by its symbol)
    static void resetPlacementDownDist(gf::GfComBehaviorPc& behavior);
    // StateFieldFall::enter's (by its symbol): switches the PC's TimerPlugin timer
    static void setActivateTimer(gf::GfComBehaviorPc& behavior, TimerPlugin::TYPE type, bool activate);
    // StateFieldAir::enter's and leave's (by its symbol)
    static void setEnableFallDistChecker(gf::GfComBehaviorPc& behavior, bool enable);
    static void broadcastPlayer(gf::GfComBehaviorPc& behavior, fw::Message& msg);
    static void broadcastDriver(gf::GfComBehaviorPc& behavior, fw::Message& msg);
    static void broadcastBlade(gf::GfComBehaviorPc& behavior, fw::Message& msg);
    // to the formation's players that stand alone
    static void broadcastMainChar(gf::GfComBehaviorPc& behavior, fw::Message& msg);
    static void sendMessageGfObj(gf::GfComBehaviorPc& behavior, gf::GF_OBJ_HANDLE* handle, fw::Message& msg);
    static void sendMessageToBuddy(gf::GfComBehaviorPc& behavior, fw::Message& msg);
    // the player paired with the PC in the formation (index 0 with 1, 2 with 3, ...), -1 without a formation
    static gf::GF_OBJ_HANDLE* getBuddyHandle(gf::GfComBehaviorPc& behavior);
    // to the buddy while the PC is a vehicle: whether it was handled
    static bool sendMessageToRider(gf::GfComBehaviorPc& behavior, fw::Message& msg);
    static bool isManualCamera();
    // the handle of the object the PC's property targets
    static gf::GF_OBJ_HANDLE* getTarget(const gf::GfComBehaviorPc& behavior);
    static void setTargetLock(bool lock);
    static unsigned int getFwPadKey(const char* name);
    static void setEnableAgentField(gf::GfComBehaviorPc& behavior, bool enable);
    static void setEnableAgentBattle(gf::GfComBehaviorPc& behavior, bool enable);
    // sets or clears the property's m_stateFlags bit 3
    static void setEnableGravity(gf::GfComBehaviorPc& behavior, bool enable);
    static const gf::EnviromentSensor::GroundInfo* getGroundInfo(gf::GfComBehaviorPc& behavior);
    // sets or clears bits of the env sensor component's sensor's m_checkFlags
    // the fall damage plugin's m_damageDisable, the foot IK controller's m_enableDownIK
    static void setFallDamageDisable(gf::GfComBehaviorPc& behavior, bool disable);
    static void setEnableDownIK(gf::GfComBehaviorPc& behavior, bool enable);
    static void setEnableLookIK(gf::GfComBehaviorPc& behavior, bool enable);
    // switches the foot IK controller's mode: set, to its slope solver (MODE_SLOPE); clear, to its placement one
    static void switchPlacementIK(gf::GfComBehaviorPc& behavior, bool placement);
    static void setEnvSensor(gf::GfComBehaviorPc& behavior, unsigned int flags, bool on);
    static void changeGroundAnglesForMotion(gf::GfComBehaviorPc& behavior, const mm::Vec3& normal);
    static const gf::EnviromentSensor::WaterInfo* getWaterInfo(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::DeadPlaneInfo* getDeadPlaneInfo(gf::GfComBehaviorPc& behavior);
    static bool isOnSlideGround(gf::GfComBehaviorPc& behavior);
    static void applyDamage(gf::GfComBehaviorPc& behavior, unsigned int damage, bool percent);
    static void notifyDead(gf::GfComBehaviorPc& behavior, gf::MsgObjectNotifyDead& msg, bool force);
    // the PC's revival on a heal (StateFieldDead and StateFieldWaterDead::onAlive hand it the heal message)
    static void notifyRevival(gf::GfComBehaviorPc& behavior, gf::MsgObjectNotifyHealHp& msg);
};

}}  // namespace gf::pc

#endif
