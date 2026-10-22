#ifndef GF_ENVIROMENTSENSOR_H
#define GF_ENVIROMENTSENSOR_H

#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

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
        unsigned char pad_24[0x14];
        // the object the ground belongs to, -1 for none (AttachPlugin::update attaches the PC to it; the name is
        // not the original's)
        gf::GF_OBJ_HANDLE* m_obj;
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
    // what a vertical search finds (its constructor builds the ground info first); 0x120 bytes:
    // TaskFieldCheckWarpBattleWaterDead::update keeps one on its stack right below its search packet
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
    };

    // a search along a direction from a position (searchVertical's): what to look for, which way and how far, and
    // where to put what it finds. The field names are not the original's.
    struct VerticalPacket {
        VerticalPacket() : m_rangeMin(0.0f), m_rangeMax(0.0f), m_resultFlags(0), m_data(nullptr) {}

        int m_type;
        mm::Vec3 m_dir;
        float m_rangeMin;            // the search's reach along m_dir, from (negative: behind the position) and to
        float m_rangeMax;
        unsigned int m_resultFlags;  // which findings hold, as m_flags (bit 1: m_data's m_water)
        VerticalData* m_data;
    };

    EnviromentSensor();
    static void searchVertical(const mm::Vec3& pos, VerticalPacket* packet);

    // the obstacle a bit 4 in m_flags says it found (the name is not the original's)
    const ObstacleInfo* getObstacleInfo() const { return (m_flags & 0x10) ? &m_obstacle : nullptr; }

    unsigned char pad_0[0x20];
    // what it checks for: GfComPropertyPc::setEnvSensorCheckFlags sets and clears its bits (TaskFieldSensor's
    // onChangeActivate bit 5 while the sensor task is active; the name is not the original's)
    unsigned int m_checkFlags;
    // which findings hold: bit 0 m_vertical.m_ground, bit 1 m_water (AttachPlugin::changeWallMode reads m_wallObj
    // with it), bit 2 m_deadPlane, bit 3 m_vertical.m_ceilHeight, bit 4 m_obstacle; with bit 5
    // TaskFieldSensor::update allows no jump
    unsigned int m_flags;
    unsigned char pad_28[0x8];
    VerticalData m_vertical;
    ObstacleInfo m_obstacle;  // with m_flags bit 4
    unsigned char pad_170[0x70];
    // with m_flags bit 1, the object of a wall by the object: AttachPlugin::changeWallMode attaches the PC to it
    // (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_wallObj;
    unsigned char pad_1e8[0x8];
};

}  // namespace gf

#endif
