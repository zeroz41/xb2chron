#ifndef GF_PC_STATEUTIL_H
#define GF_PC_STATEUTIL_H

#include "gf/EnviromentSensor.h"

namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {

// what the PC's states share (functions, by its symbols)
class StateUtil {
public:
    static const gf::EnviromentSensor::GroundInfo* getGroundInfo(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::WaterInfo* getWaterInfo(gf::GfComBehaviorPc& behavior);
    static const gf::EnviromentSensor::DeadPlaneInfo* getDeadPlaneInfo(gf::GfComBehaviorPc& behavior);
    static bool isOnSlideGround(gf::GfComBehaviorPc& behavior);
    static void applyDamage(gf::GfComBehaviorPc& behavior, unsigned int damage, bool percent);
};

}}  // namespace gf::pc

#endif
