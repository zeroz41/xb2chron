#ifndef GF_PC_STATEUTIL_H
#define GF_PC_STATEUTIL_H

#include "gf/EnviromentSensor.h"
#include "classes/gf/pc/TimerPlugin.h"

namespace fw { class Message; }
namespace fw { enum VibrationID : int; }
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
    // GfComBehaviorPc::integrateMove calls it first, before the move of the property's integrate mode
    static void reflectionAdsorption(gf::GfComBehaviorPc& behavior);
    // StateFieldFall::enter's (by its symbol): switches the PC's TimerPlugin timer
    static void setActivateTimer(gf::GfComBehaviorPc& behavior, TimerPlugin::TYPE type, bool activate);
    // the time of the TimerPlugin's timer of a type while it is active, else none (by its symbol; the return type
    // is inferred)
    static const float* getActivateTimer(gf::GfComBehaviorPc& behavior, TimerPlugin::TYPE type);
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
    // the sensor's wall (its m_flags bit 6) when that wall's m_flags bit 4 is set, else none (by its symbol)
    static const gf::EnviromentSensor::WallInfo* getClimbWallInfo(gf::GfComBehaviorPc& behavior);
    // the sensor's second ground (its m_flags bit 8), else none (by its symbol)
    static const gf::EnviromentSensor::GroundInfo* getClimbEndGroundInfo(gf::GfComBehaviorPc& behavior);
    static void setTargetLock(bool lock);
    // the property's target, then the change told to the PC itself (the game target's when m_setupKind is 0: its
    // answer; else false) (by its symbol; the return type from its code)
    static bool setTarget(gf::GfComBehaviorPc& behavior, gf::GF_OBJ_HANDLE* target);
    static void setEnableHeadDetectForSwitcher(gf::GfComBehaviorPc& behavior, bool enable);  // (by its symbol)
    static void setEnableSpineIK(gf::GfComBehaviorPc& behavior, bool enable);  // (by its symbol)
    static void setEnableSpineRotate(gf::GfComBehaviorPc& behavior, bool enable, float time);  // (by its symbol)
    static void setSpineRotateAngles(gf::GfComBehaviorPc& behavior, float angleX, float angleY);  // (by its symbol)
    static void setEnableAttach(gf::GfComBehaviorPc& behavior, bool enable);  // (by its symbol)
    static void setEnableTimer(gf::GfComBehaviorPc& behavior, bool enable);  // (by its symbol)
    static void setLipSpeed(gf::GfComBehaviorPc& behavior, float speed);  // (by its symbol)
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
    static void changeGroundAnglesForMotion(gf::GfComBehaviorPc& behavior, const mm::Vec3& angles);
    static const gf::EnviromentSensor::WaterInfo* getWaterInfo(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::DeadPlaneInfo* getDeadPlaneInfo(gf::GfComBehaviorPc& behavior);
    static bool isOnSlideGround(gf::GfComBehaviorPc& behavior);
    static void setEnableFootStep(gf::GfComBehaviorPc& behavior, bool enable);  // (by its symbol)
    static void playVibration(gf::GfComBehaviorPc& behavior, fw::VibrationID id);  // (by its symbol)
    static void changePlacementDownDist(gf::GfComBehaviorPc& behavior, float dist);  // (by its symbol)
    static void applyDamage(gf::GfComBehaviorPc& behavior, unsigned int percent, bool flag);
    static void notifyDead(gf::GfComBehaviorPc& behavior, gf::MsgObjectNotifyDead& msg, bool force);
    // the PC's revival on a heal (StateFieldDead and StateFieldWaterDead::onAlive hand it the heal message)
    static void notifyRevival(gf::GfComBehaviorPc& behavior, gf::MsgObjectNotifyHealHp& msg);
};

}}  // namespace gf::pc

#endif
