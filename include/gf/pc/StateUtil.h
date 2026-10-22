#ifndef GF_PC_STATEUTIL_H
#define GF_PC_STATEUTIL_H

#include "gf/EnviromentSensor.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class MsgObjectNotifyDead; }

namespace gf { namespace pc {

// what the PC's states share (functions, by its symbols)
class StateUtil {
public:
    // the handle of the object the PC's property targets
    static gf::GF_OBJ_HANDLE* getTarget(const gf::GfComBehaviorPc& behavior);
    static gf::GF_OBJ_HANDLE* getBuddyHandle(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::GroundInfo* getGroundInfo(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::WaterInfo* getWaterInfo(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::DeadPlaneInfo* getDeadPlaneInfo(gf::GfComBehaviorPc& behavior);
    static bool isOnSlideGround(gf::GfComBehaviorPc& behavior);
    static void applyDamage(gf::GfComBehaviorPc& behavior, unsigned int damage, bool percent);
    static void notifyDead(gf::GfComBehaviorPc& behavior, gf::MsgObjectNotifyDead& msg, bool force);
};

}}  // namespace gf::pc

#endif
