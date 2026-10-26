#ifndef CLASSES_GF_PLAYERCAMERA_H
#define CLASSES_GF_PLAYERCAMERA_H

#include "fw/ColiCheck.h"
#include "fw/ParamAdapter.h"
#include "gf/CameraPadData.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// when a climb resets the player camera (GfGamePlayerCamera::resetCameraClimb passes it on); resetClimb takes the
// 0.667 revise rate for 0 and 0.233 for any other value; no names are known
enum ResetCameraWallTiming : int {};

// table 0x7100B45AE8
class PlayerCamera : public ::fw::Camera {
public:
    static void setOnceOff();
    // its parameter block; the names are 1.0.0's createReflection's (snake_case there), at the offsets it registers
    struct Param {
        float m_fov;  // degrees (1.0.0's getFov returns it)
        unsigned char pad_4[0x60];
        // "flag", a bitset: slope_revise_enable 0x10 ... ship_random 0x200
        unsigned int : 4;
        unsigned int m_slopeReviseEnable : 1;
        unsigned int m_horizontalReverseEnable : 1;
        unsigned int m_verticalReverseEnable : 1;
        unsigned int m_semimanualEnable : 1;
        unsigned int m_shipCurve : 1;   // the ship's roll and pitch follow a sine, not a back-and-forth sweep
        unsigned int m_shipRandom : 1;  // each swing's amplitude is drawn between the min and the max
        unsigned int : 22;
        int m_cameraType;
        float m_shipRollMin;    // degrees
        float m_shipRollMax;    // degrees
        float m_shipRollMove;   // degrees per update
        float m_shipPitchMin;
        float m_shipPitchMax;
        float m_shipPitchMove;
    };
    // a manual-control speed set, one per row of BDAT table 0x18A (the constructor reads its percent and degree
    // columns: ZoomSpeed, YawRotSpeed, PitchRotSpeed, RevReset, RevAuto; the names are not the original's)
    struct SpeedSet {
        float m_zoomSpeed;
        float m_yawRotSpeed;    // radians
        float m_pitchRotSpeed;  // radians
        float m_revReset;
        float m_revAuto;
    };

    PlayerCamera(fw::ParamAdapter& param);
    virtual ~PlayerCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const { return "PlayerCamera"; }  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void updateViewMatrix();  // slot 9
    static mm::mtl::RTTI m_rtti;
    static mm::mtl::IntrusivePtr<PlayerCamera> create();
    void updateCollision2(mm::Vec3& eye, mm::Vec3& target);
    void reset();
    void resetClimb(ResetCameraWallTiming timing);
    void resetLoad();
    void resetBattleWarp();
    void setTarget(GF_OBJ_HANDLE* handle);
    bool isManual();
    float getSaveYaw() const;
    float getSavePitch() const;
    float getSaveDistance() const;
    float getSaveHeight() const;
    bool getSaveSide() const;
    bool isSaveFreeMode() const;

    GF_OBJ_HANDLE* m_targetHandle;  // setTarget's (the name is not the original's)
    fw::ParamAdapter m_param;  // the constructor's (PlayerCamera(fw::ParamAdapter&) in 1.0.0): a Param
    // the camera's angles and distances, each as applied and as aimed for: GfGamePlayerCamera saves the aimed ones
    // through getSave*, updateViewMatrix copies the aimed distance to the applied one (the names are not the
    // original's)
    float m_curYaw;
    float m_yaw;
    float m_curPitch;
    float m_pitch;
    unsigned char pad_c8[0x8];
    float m_curDistance;
    float m_distance;
    unsigned char pad_d8[0x4];
    float m_height;
    unsigned char pad_e0[0x8];
    bool m_side;  // the constructor sets it
    unsigned char pad_e9[0x3];
    unsigned char pad_ec[0x4];
    float m_rotateRevise;  // resetClimb sets it from its timing (the name is not the original's)
    unsigned char pad_f4[0x8];
    unsigned char pad_fc[0x4];
    // resetBattleWarp sets both to the target's position (the names are not the original's)
    mm::Vec3 m_targetPos;
    mm::Vec3 m_lookPos;
    bool m_manual;  // isManual and isSaveFreeMode (the name is not the original's)
    unsigned char pad_121[0x3];
    bool m_resetClimb;  // resetClimb sets it (the name is not the original's)
    unsigned char pad_125[0x3];
    unsigned char pad_128[0x4];
    // the collision tests' settings (the names are not the original's)
    fw::ColiCheckConfig m_coliConfig;
    fw::ColiCheckConfig m_coliConfigSide;
    unsigned char pad_15c[0x4];
    fw::TColiCheckResult<256> m_coliResult;  // getHitPosition's (the name is not the original's)
    mm::Vec3 m_offset;  // updateTarget and onActivate write it (the name is not the original's)
    bool m_targetChanged;  // setTarget sets it when a target replaces another (the name is not the original's)
    unsigned char pad_5191[0xf];
    mm::Vec3 m_warpPos;  // resetBattleWarp sets it to the target's position (the name is not the original's)
    float m_trackingHeight;  // updateTracking sets it with m_warpPos.y (the name is not the original's)
    unsigned char pad_51b4[0x4];
    CameraPadData m_padData;  // the name is not the original's
    unsigned char pad_5200[0xc0];
    float m_aspect;  // the root graph's width / height (the name is not the original's)
    ResetCameraWallTiming m_wallTiming;  // resetClimb's
    bool m_lastTargetFlag;  // update compares it with a byte of the target's property (the name is not the original's)
    unsigned char pad_52c9[0x3];
    // the near plane's half width and half height (the names are not the original's)
    float m_nearHalfWidth;
    float m_nearHalfHeight;
    // BDAT table 0x18B row 1's ZoomSpeed, RotSpeed, RevReset, RevAuto (the names are not the original's)
    unsigned char m_zoomSpeed;
    unsigned char m_rotSpeed;
    unsigned char m_revReset;
    unsigned char m_revAuto;
    mm::mtl::FixedVector<SpeedSet, 10> m_speedSets;  // the name is not the original's
};
}  // namespace gf

#endif
