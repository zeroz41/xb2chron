#ifndef CLASSES_GF_GIMMICKCAMERA_H
#define CLASSES_GF_GIMMICKCAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "math.h"
#include "fw/ColiCheck.h"
#include "classes/gf/GimmickCameraParams.h"

namespace fw { class UpdateInfo; }

namespace gf {
class GF_OBJ_HANDLE;

// table 0x7100B45E68: a camera that plays the keys of one entry of the camera parameter file
// ("/camera/params.gca"), relative to nothing, an object or a position
class GimmickCamera : public ::fw::Camera {
public:
    // one key (0x40 bytes): setReadFile copies a GimmickCameraParams::Param into it. The names are not the original's.
    struct Param {
        Param(const GimmickCameraParams::Param& src)
            : m_pos(src.m_pos[0], src.m_pos[1], src.m_pos[2]), m_rot(src.m_rot[0], src.m_rot[1], src.m_rot[2]),
              m_fov(src.m_fov), m_keyValueA(src.m_keyValueA), m_keyValueB(src.m_keyValueB), m_speedType(src.m_speedType),
              m_duration(src.m_duration) {}
        mm::Vec3 m_pos;    // where the camera stands
        mm::Vec3 m_rot;    // pitch, yaw, roll (radians)
        float m_fov;       // play copies it into the camera's field of view
        float m_keyValueA;   // the file entry's seventh float (its use is not known yet)
        float m_keyValueB;   // the file entry's eighth float (its use is not known yet)
        int m_speedType;   // how the move to the next key eases (5: at the speed updatePlayCamera keeps)
        float m_duration;  // seconds to the next key
    };

    // the camera parameter file setReadFile reads: named entries, each a GimmickCameraParams file (the names
    // are not the original's)
    struct ParamFile {
        struct Entry {
            int m_dataOffset;  // from the file's m_dataOffset
            int m_nameOffset;  // from the file's m_nameOffset
        };
        unsigned char pad_0[0x4];
        int m_count;       // entries
        int m_dataOffset;  // where the entries' data start
        int m_nameOffset;  // where the entries' names start
        Entry m_entries[1];
    };

    GimmickCamera(fw::CAMERA_PRIO prio);
    virtual ~GimmickCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const { return "GimmickCamera"; }  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    static mm::mtl::RTTI m_rtti;

    // the camera file's entry of that name, as the file places it
    static mm::mtl::IntrusivePtr<GimmickCamera> create(const char* name);
    // the camera file's entry of that name, placed relative to the object
    static mm::mtl::IntrusivePtr<GimmickCamera> create(const char* name, GF_OBJ_HANDLE* target);
    // the camera file's entry of that name, placed at pos turned by rotY
    static mm::mtl::IntrusivePtr<GimmickCamera> create(const char* name, const mm::Vec3& pos, float rotY);
    void setReadFile(const char* name);
    void play();
    void updatePlayCamera(const fw::UpdateInfo& info);
    void updateParams();
    bool isPlayEnd() const;
    bool isLoaded() const;
    void setAuto(bool on);
    void setCollision(bool on);
    void setNearClip(float clip);
    void setPause(bool on);
    void updateParamsByCoordinateType();
    // where the camera looks: unit z turned by m_rot's x and y (half angles, a quaternion; m_rot's z is the roll
    // setLookAt takes), as gf::ScriptCameraEntity's. Inline; the name is not the original's
    __attribute__((always_inline)) mm::Vec3 getDirection() const {
        mm::Vec3 euler(m_rot.x, m_rot.y, 0.0f);
        mm::Vec3 half = euler * 0.5f;
        float hx = half.x, hy = half.y, hz = half.z;
        float sx = ::sinf(hx), cx = ::cosf(hx), sy = ::sinf(hy), cy = ::cosf(hy), sz = ::sinf(hz), cz = ::cosf(hz);
        mm::Quat rotation(sx * cy * cz - cx * sy * sz, sx * cy * sz + cx * sy * cz, cx * cy * sz - sx * sy * cz,
                          sx * sy * sz + cx * cy * cz);
        const mm::Quat& q = rotation;
        const mm::Vec3& v = mm::Vec3::unitZ;
        float tx = (q.y * v.z - q.z * v.y) + q.w * v.x;
        float ty = (q.z * v.x - q.x * v.z) + q.w * v.y;
        float tz = (q.x * v.y - q.y * v.x) + q.w * v.z;
        float tw = -q.x * v.x - q.y * v.y - v.z * q.z;
        return mm::Vec3((-(q.z * ty) + q.y * tz - q.x * tw) + q.w * tx, (-(q.x * tz) + q.z * tx - q.y * tw) + q.w * ty,
                        (-(q.y * tx) + q.x * ty - q.z * tw) + q.w * tz);
    }

    // the names are not the original's
    mm::Vec3 m_pos;  // where the camera stands
    mm::Vec3 m_rot;  // pitch, yaw, roll (radians)
    float m_curFov;  // update copies it into m_fov
    unsigned char pad_d4[0xc];
    mm::mtl::FixedVector<Param, 1024> m_params;  // the keys setReadFile read
    int m_readKind;       // 1 from every create (its use is not known yet)
    int m_coordType;      // 0: as the file places it, 1: relative to m_target, 2: at m_basePos turned by m_baseRotY
    bool m_playing;       // play sets it
    bool m_started;       // play sets it; isPlayEnd answers only once it is set
    bool m_auto;          // update plays the keys as soon as they are read
    bool m_collision;     // setCollision's
    bool m_enabled;     // true from the constructor (its use is not known yet)
    bool m_pause;         // updatePlayCamera does nothing while it is set
    unsigned char pad_100fe[0x2];
    int m_keyIndex;       // the key being left
    float m_keyTime;      // seconds since it
    float m_speed;        // the speed speed type 5 keeps
    unsigned char pad_1010c[0x4];
    mm::Vec3 m_basePos;   // create(name, pos, rotY)'s pos
    float m_baseRotY;     // create(name, pos, rotY)'s rotY
    unsigned char pad_10124[0x4];
    GF_OBJ_HANDLE* m_target;    // create(name, target)'s
    const void* m_readEntry;    // the file entry setReadFile found, until update plays it
    float m_scale;         // 1 from the constructor (its use is not known yet)
    fw::ColiCheckConfig m_coliConfig;
    bool m_hitCollision;           // false from the constructor (its use is not known yet)
    unsigned char pad_10155[0xb];
    mm::Vec3 m_lookOffset;        // zero from the constructor (its use is not known yet)
};
}  // namespace gf

#endif
