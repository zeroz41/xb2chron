#ifndef GF_ENVIROMENTSENSOR_H
#define GF_ENVIROMENTSENSOR_H

#include "mm/Vec3.h"

namespace gf {

// no table: what a GfComEnvSensor finds around its object (the component holds one at 0x10, its constructor
// builds it); m_flags says which of its findings hold
class EnviromentSensor {
public:
    // the ground under the object
    class GroundInfo {
    public:
        GroundInfo();

        mm::Vec3 m_pos;          // the point found (the constructor: zero)
        mm::Vec3 m_normal;       // the ground's plane: its normal (the constructor: unit Y)
        float m_planeDist;       // and the plane's distance term, -m_normal.dot(m_pos)
        unsigned char pad_24[0x1C];
        mm::Vec3 m_velocity;     // the ground's own movement (the constructor: zero)
        unsigned char pad_50[0x20];
    };
    // the water around the object; the name is not the original's (StateUtil::getWaterInfo returns it)
    struct WaterInfo {
        float m_height;          // the water surface's height
        unsigned char pad_4[0x2C];
        unsigned int m_damageId; // the terrain damage the water deals (GfFieldDmgManager::findBdatInfo's)
        unsigned char pad_34[0xC];
    };
    // the plane below which the object dies; the name is not the original's (StateUtil::getDeadPlaneInfo)
    struct DeadPlaneInfo {
        unsigned char pad_0[0x4];
        float m_height;          // the plane's height
    };
    // with m_flags bit 4, a face in the object's way: TaskFieldSensor::update counts it as an obstacle when it
    // leans further from level than the AI's obstacleAngle, and lets the PC jump onto it when its target is at
    // least enableJumpOffset above it (the name is not the original's)
    struct ObstacleInfo {
        mm::Vec3 m_normal;  // the face's plane: its normal
        float m_planeDist;  // and the plane's distance term
    };
    // what a vertical search finds (its constructor builds the ground info first)
    struct VerticalData {
        VerticalData();

        GroundInfo m_ground;
        WaterInfo m_water;
        DeadPlaneInfo m_deadPlane;
        unsigned char pad_b8[0x28];
        // with m_flags bit 3: the height of what is above the object (TaskFieldSensor::update allows no jump while it
        // is within the AI's enableJumpCeil above the PC; the name is not the original's)
        float m_ceilHeight;
        unsigned char pad_e4[0x3C];
        ObstacleInfo m_obstacle;  // with m_flags bit 4
        unsigned char pad_140[0x80];
    };

    EnviromentSensor();

    // the obstacle a bit 4 in m_flags says it found (the name is not the original's)
    const ObstacleInfo* getObstacleInfo() const { return (m_flags & 0x10) ? &m_vertical.m_obstacle : nullptr; }

    unsigned char pad_0[0x20];
    // what it checks for: GfComPropertyPc::setEnvSensorCheckFlags sets and clears its bits (TaskFieldSensor's
    // onChangeActivate bit 5 while the sensor task is active; the name is not the original's)
    unsigned int m_checkFlags;
    // which findings hold: bit 0 m_vertical.m_ground, bit 1 m_water, bit 2 m_deadPlane, bit 3 m_vertical.m_ceilHeight,
    // bit 4 m_vertical.m_obstacle; with bit 5 TaskFieldSensor::update allows no jump
    unsigned int m_flags;
    unsigned char pad_28[0x8];
    VerticalData m_vertical;
};

}  // namespace gf

#endif
