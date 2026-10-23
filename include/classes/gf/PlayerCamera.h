#ifndef CLASSES_GF_PLAYERCAMERA_H
#define CLASSES_GF_PLAYERCAMERA_H

#include "fw/ParamAdapter.h"
#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// when a climb resets the player camera (GfGamePlayerCamera::resetCameraClimb passes it on); no values are known
enum ResetCameraWallTiming : int {};

// table 0x7100B45AE8
class PlayerCamera : public ::fw::Camera {
public:
    static void setOnceOff();
    // its parameter block; the names are 1.0.0's createReflection's (snake_case there), at the offsets it registers
    struct Param {
        unsigned char pad_0[0x64];
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

    virtual ~PlayerCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void updateViewMatrix();  // slot 9
    static mm::mtl::RTTI m_rtti;
    static mm::mtl::IntrusivePtr<PlayerCamera> create();
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

    unsigned char pad_a8[0x8];
    fw::ParamAdapter m_param;  // the constructor's (PlayerCamera(fw::ParamAdapter&) in 1.0.0): a Param
};
}  // namespace gf

#endif
