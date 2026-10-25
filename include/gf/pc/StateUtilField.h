#ifndef GF_PC_STATEUTILFIELD_H
#define GF_PC_STATEUTILFIELD_H

#include "mm/Vec3.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { class GfComAsm; }
namespace gf { class GfComPropertyPc; }
namespace gf { class GfComBehaviorPc; }
namespace gf { class GfComponent; }
namespace gf { class GfObj; }
namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Plane; }

namespace gf { namespace pc {
// the PC's field asm commands execAsmCmd takes: an index into getASMCmdNameField's TABLE of command names (the type
// is the symbols'; only the values used so far are named, and those names are not the original's: they spell the
// command name the table holds at that index; callers also pass 0x15 from StateFieldOnWall's wall jump and 1 from
// StateFieldIdle::update)
enum ASM_CMD_ID_FIELD : unsigned int {
    ASM_CMD_ID_FIELD_IDLE = 0,           // "C_idle"
    ASM_CMD_ID_FIELD_MOVE = 1,           // "C_move"
    ASM_CMD_ID_FIELD_WATERIDLE = 7,      // "C_wateridle"
    ASM_CMD_ID_FIELD_SWIM_00 = 8,        // "C_swim_00"
    ASM_CMD_ID_FIELD_SWIM_01 = 9,        // "C_swim_01"
    ASM_CMD_ID_FIELD_WATERHOLE_00 = 10,  // "C_waterhole_00"
};

// a rider event notifyRiderEvent passes on (the type is the symbols'; StateFieldWallPerformance::leave passes 0)
enum VehicleEvent : unsigned int {};

// what the PC's field states share (functions, by its symbols)
class StateUtilField {
public:
    // when resetCameraForWall is called (the type is the symbols'; StateFieldWallAdsorptionGround::enter passes 1,
    // StateFieldWallAdsorptionAir::enter 2: no enumerator names known)
    enum Timing : unsigned int {};
    static void resetCameraForWall(gf::GfComBehaviorPc& behavior, Timing timing);
    static void setAsmSpeedSlideBrake(gf::GfComPropertyPc& property);
    static void setWallMoveMode(gf::GfComBehaviorPc& behavior, bool on);
    static void notifySkillAct(gf::GfComBehaviorPc& behavior, bool act);
    static void notifyRiderEvent(gf::GfComBehaviorPc& behavior, VehicleEvent event);
    // where the PC gets ready to climb a wall: from the wall's point and plane
    static mm::Vec3 calcWallPreparePosition(gf::GfComPropertyPc& property, const mm::Vec3& wallPos,
                                            const mm::Plane& wallPlane);
    static bool isEnableWallAdsorptionStart(gf::GfComPropertyPc& property, const mm::Vec3& wallPos,
                                            const mm::Vec3& preparePos);
    static bool isEnableWallPrepare(gf::GfComPropertyPc& property);
    static bool isWallPreparePosition(gf::GfComPropertyPc& property, const mm::Vec3& preparePos);
    static void setAccessFlag(gf::GfComBehaviorPc& behavior, bool flag);
    // the water states' (by their symbols)
    static bool isInputInverseDir(gf::GfComPropertyPc& property);
    static void startWaterWarpFade(gf::GfComBehaviorPc& behavior);
    static bool isInterruptionWater(gf::GfComPropertyPc& property);
    static bool isTurnRange(gf::GfComPropertyPc& property, mm::mtl::FixedQueue<mm::Vec2, 2>& inputs);
    static void setAsmSpeedSwim(gf::GfComPropertyPc& property);
    // the object the PC can access now, if any (by its symbol)
    static gf::GfObj* getAccessTarget(gf::GfComBehaviorPc& behavior);
    static void setSpecialActStatus(gf::GfComBehaviorPc& behavior, bool status);
    static gf::GF_OBJ_HANDLE* getLureTargetHandle(gf::GfComBehaviorPc& behavior);  // (by its symbol)
    static void setEnableLure(gf::GfComBehaviorPc& behavior, bool enable);  // StateFieldLure::leave's (by its symbol)
    // the auto-run: toggled, set, tested and fed to the input (by their symbols)
    static void flipAutoRun(gf::GfComPropertyPc& property);
    static void setAutoRun(gf::GfComPropertyPc& property, bool on);
    static bool testAutoRun(gf::GfComPropertyPc& property);
    static void setAutoRunInput(gf::GfComPropertyPc& property);
    static bool isInputInverseDirAutoRun(gf::GfComPropertyPc& property);
    static void setWaterMode(gf::GfComBehaviorPc& behavior, bool water);
    static void setLookAtFlag(gf::GfComBehaviorPc& behavior, bool flag);
    static void setIdleStatus(gf::GfComPropertyPc& property, bool idle);
    // runs a field animation command on the PC's animation state machine: whether it ran
    static bool execAsmCmd(gf::GfComAsm& comAsm, ASM_CMD_ID_FIELD id);
    // the water states set it entering a dive and clear it leaving one
    static void setWaterDiveMove(gf::GfComPropertyPc& property, bool dive);
    // StateFieldJump::leave's (by its symbol)
    static void notifyJumpEnd(gf::GfComBehaviorPc& behavior);
    // the air states' (StateFieldAir::enter/leave, StateFieldLand::leave; by their symbols)
    static void setAirStatus(gf::GfComBehaviorPc& behavior, bool air);
    static void setEnableWaterIn(gf::GfComBehaviorPc& behavior, bool enable);
    static void setEnableFallIntoColi(gf::GfComBehaviorPc& behavior, bool enable);
    // the height of the PC's child frame (the water states compare it against the water's depths; by their symbols)
    static float getChildFrameHeight(gf::GfComponent& component);
    static void setChildFrameHeight(gf::GfComponent& component, float height);
    // StateFieldAir::leave's into state 0x36 (by its symbol)
    static void setSlideDirForce(gf::GfComPropertyPc& property);
    static bool isTurnEndRangeCacheInput(gf::GfComPropertyPc& property, const mm::Vec3& dir);  // (by its symbol)
    // the turn states' enter tail-calls it (by its symbol)
    static void notifyTurn(gf::GfComBehaviorPc& behavior);
    static bool isStop(gf::GfComPropertyPc& property, unsigned int noInputFrames);  // (by its symbol)
    static void setAsmSpeedMove(gf::GfComPropertyPc& property);  // (by its symbol)
    // (by their symbols)
    static bool isWallAdsorptionAir(gf::GfComPropertyPc& property);
    static bool isWallAdsorption(gf::GfComPropertyPc& property);
    static bool isWallAdsorptionUnderWall(gf::GfComPropertyPc& property);
    static bool isSwimFromAir(gf::GfComPropertyPc& property);
    static bool isSwimMoveFromAir(gf::GfComPropertyPc& property);
    static bool isSlideGroundLanding(gf::GfComPropertyPc& property);
    static bool isSlideSlope(gf::GfComPropertyPc& property);
    static bool isBackRangeAir(gf::GfComPropertyPc& property);
    static bool isBigLandDistance(gf::GfComBehaviorPc& behavior);
    static void onLandSliding(gf::GfComBehaviorPc& behavior);
    static bool ignoreOnGroundJump(gf::GfComPropertyPc& property, float time);
    static gf::GfObj* getLureTarget(gf::GfComBehaviorPc& behavior);
    static bool isStartSlidePosuture(gf::GfComBehaviorPc& behavior);
    static bool requestBattleStart(gf::GfComPropertyPc& property);
};

}}  // namespace gf::pc

#endif
