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
    // what a vertical search finds (its constructor builds the ground info first)
    struct VerticalData {
        VerticalData();

        GroundInfo m_ground;
        WaterInfo m_water;
        DeadPlaneInfo m_deadPlane;
        unsigned char pad_b8[0x108];
    };

    EnviromentSensor();

    unsigned char pad_0[0x24];
    // which findings hold: bit 0 m_vertical.m_ground, bit 1 m_water, bit 2 m_deadPlane
    unsigned int m_flags;
    unsigned char pad_28[0x8];
    VerticalData m_vertical;
};

}  // namespace gf

#endif
