#ifndef GF_GFSEARCHPARAM_H
#define GF_GFSEARCHPARAM_H

#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ReferenceFrame; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// what GfGameSearchObj::createObj searches for (0x68 bytes, copied into the search's info). Its constructor is
// inline: every caller (GfGameTarget::createSearchObj, LookAtPlugin::setup, FallIntoColiPlugin::setup) writes the
// same defaults. The names are not the original's: they follow GfGameSearchObj::updateObj and calcVisible.
class GfSearchParam {
public:
    enum {
        CHECK_RADIUS = 1 << 0,   // calcVisible: horizontally within m_radius (plus the object's own radius)
        CHECK_HEIGHT = 1 << 1,   // calcVisible: from m_heightDown below to m_heightUp above
        CHECK_ANGLE = 1 << 2,    // calcVisible: within m_angle of the forward direction
        CHECK_VISIBLE = 1 << 3,  // calcVisible: GfGameVisible's verdict
    };

    GfSearchParam()
        : m_checks(0), m_listTypes(0x20), m_pos(mm::Vec3::zero), m_rot(mm::Quat::identity), m_heightUp(0.0f),
          m_heightDown(0.0f), m_angle(0.0f), m_radius(0.0f), m_baseObj(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)),
          m_frame(), m_matchAll(true), pad_58(0), m_ignoreObj(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {}

    unsigned int m_checks;     // CHECK_*
    unsigned int m_listTypes;  // updateObj: a bit per GfGameObj list type searched (from type 3)
    mm::Vec3 m_pos;            // the search's centre (updateObj takes it from m_frame when there is one)
    mm::Quat m_rot;            // the search's direction (likewise)
    float m_heightUp;
    float m_heightDown;
    float m_angle;
    float m_radius;
    gf::GF_OBJ_HANDLE* m_baseObj;  // updateObj: the object whose transform centres the search (-1: m_pos/m_rot)
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;
    bool m_matchAll;  // calcVisible: an object passes only when every check does (false: when any one does)
    unsigned long pad_58;
    gf::GF_OBJ_HANDLE* m_ignoreObj;  // updateObj: an object the search skips
};

}  // namespace gf

#endif
