#ifndef BTL_EFFECTMOVECOMPONENT_H
#define BTL_EFFECTMOVECOMPONENT_H

#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// an effect's movement (application/BF2/battle/EffectMoveComponent); EffectObject holds one at 0x1C0, up to its
// 0x270 field, so 0xB0 bytes. Update calls m_apUpdateFuncList[m_type - 1]. The field, type and member-struct
// names are not the original's (only the functions' and m_apUpdateFuncList's are).
class EffectMoveComponent {
public:
    // m_type: which update the move runs (by the functions m_apUpdateFuncList holds; the names are not the
    // original's). 0 does not move.
    enum MOVE_TYPE {
        MOVE_TYPE_NONE = 0,
        MOVE_TYPE_NORMAL = 1,
        MOVE_TYPE_PARABOLA = 2,  // Initialize: a gravity that lands at the target from the start position
        MOVE_TYPE_HOMING = 3,
        MOVE_TYPE_BOUNCE = 4,
        MOVE_TYPE_LINK_OBJ = 5,
        MOVE_TYPE_UP = 6,
    };
    // what EffectObject::SetMoveParam passes on to Initialize (0x64 bytes; the tail by m_type)
    struct MOVE_PARAM {
        mm::Vec3 m_dir;
        float m_speed;
        float m_speedLimit;
        float m_accel;
        float m_accelWait;
        float m_endParam[6];  // IsEnd's per-condition values, copied to the component
        unsigned char m_endFlags;
        unsigned char m_type;  // MOVE_TYPE
        union {
            struct {
                mm::Vec3NA m_start;
                mm::Vec3NA m_target;
            } m_parabola;
            struct {
                gf::GF_OBJ_HANDLE* m_target;  // -1: m_pos instead of a character
                mm::Vec3NA m_pos;
                float m_time;
                float m_turnSpeed;
                float m_turnSpeedLimit;
                float m_turnAccel;
            } m_homing;
            struct {
                gf::GF_OBJ_HANDLE* m_obj;
                const char* m_bone;
                mm::Vec3NA m_pos;
                float m_time;
            } m_linkObj;
            struct {
                float m_time;
            } m_up;
        };
    };
    typedef void (EffectMoveComponent::*UpdateFunc)(float dt, float frame, const mm::Vec3& pos);

    EffectMoveComponent();
    void Initialize();
    void Initialize(const MOVE_PARAM& param);
    bool IsEnd(const mm::Vec3& pos, mm::Vec3& out, float rate) const;
    void UpdateNormal(float dt, float frame, const mm::Vec3& pos);
    void UpdateHoming(float dt, float frame, const mm::Vec3& pos);
    void UpdateBounce(float dt, float frame, const mm::Vec3& pos);
    void UpdateLinkObj(float dt, float frame, const mm::Vec3& pos);
    void UpdateUp(float dt, float frame, const mm::Vec3& pos);
    void Update(const fw::UpdateInfo& info, const mm::Vec3& pos);

    static const UpdateFunc m_apUpdateFuncList[6];

    // by m_type (Initialize fills the one of m_type)
    union {
        struct {
            gf::GF_OBJ_HANDLE* m_target;  // -1: m_pos
            mm::Vec3NA m_pos;
            mm::Vec3NA m_wanderPos;
            float m_time;  // below 0: no limit
            float m_timer;
            float m_delay;
            float m_wanderTime;
            float m_turnSpeed;
            float m_turnSpeedLimit;
            float m_turnAccel;
            bool m_isFar;
        } m_homing;
        struct {
            gf::GF_OBJ_HANDLE* m_obj;
            const char* m_bone;
            float m_time;
        } m_linkObj;
        struct {
            float m_time;
        } m_up;
    };
    mm::Vec3 m_velocity;
    mm::Vec3 m_dir;
    float m_time;
    float m_moveLength;
    float m_moveLengthXZ;
    float m_speed;
    float m_speedLimit;
    float m_speedRate;
    float m_accel;
    float m_accelWait;
    float m_accelTimer;
    float m_gravity;
    float m_gravityTime;
    float m_endParam[6];
    unsigned char m_endFlags;
    unsigned char m_type;  // MOVE_TYPE
    unsigned char pad_a6[0xA];
};
}  // namespace btl

#endif
