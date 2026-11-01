#ifndef GF_PC_STATEUTILFIELD_H
#define GF_PC_STATEUTILFIELD_H

#include "mm/Vec3.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gf/pc/GfPropertyField.h"

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
    ASM_CMD_ID_FIELD_FALL = 6,           // "C_fall" (the name is not the original's: from the string)
    ASM_CMD_ID_FIELD_WATERIDLE = 7,      // "C_wateridle"
    ASM_CMD_ID_FIELD_SWIM_00 = 8,        // "C_swim_00"
    ASM_CMD_ID_FIELD_SWIM_01 = 9,        // "C_swim_01"
    ASM_CMD_ID_FIELD_WATERHOLE_00 = 10,  // "C_waterhole_00"
    ASM_CMD_ID_FIELD_WATERDEAD = 11,     // "C_waterdead" (the name is not the original's: from the string)
};

// the asm command an ASM_CMD_ID_FIELD stands for (inline: its table is a weak static of this unit's, read through
// the GOT; the table's type and name are the symbols')
inline const char* getASMCmdNameField(ASM_CMD_ID_FIELD id) {
    static const char* TABLE[] = {
        "C_idle", "C_move", "C_jump", "C_jump_end", "C_jumpdmg", "C_walkend",
        "C_fall", "C_wateridle", "C_swim_00", "C_swim_01", "C_waterhole_00", "C_waterdead",
        "C_climbidle", "C_climbup", "C_climbdown", "C_climbright", "C_climbleft", "C_uplanding_00",
        "C_uplanding_01", "C_downlanding_00", "C_downlanding_01", "C_climbjump_00", "C_climbjump_01", "C_climbjump_02",
        "C_access", "C_slope", "C_highjump", "C_highjump_01", "C_lure", "C_dead",
        "C_down_00", "C_down_01", "C_downpose", "C_rise", "C_uniqueA", "C_uniqueB",
        "C_uniqueC", "C_ride", "C_move_ride", "C_rideup_00", "C_rideup_01", "C_ridedown_00",
        "C_ridedown_01", "C_rideclimbidle", "C_ridejump_00", "C_ridejump_02", "C_ridejumpdmg", "C_ridehighjump_00",
        "C_ridehighjump_01", "C_ridefall", "C_ridewaterhole_00",
    };
    return TABLE[id];
}

// a rider event notifyRiderEvent passes on (the type is the symbols'; StateFieldWallPerformance::leave passes 0)
enum VehicleEvent : unsigned int {};

// what the PC's field states share (functions, by its symbols)
// the angle between the stick's direction and the PC's (by its symbol)
float calcInputDiffAngleVel(gf::GfComPropertyPc& property);

class StateUtilField {
public:
    // when resetCameraForWall is called (the type is the symbols'; StateFieldWallAdsorptionGround::enter passes 1,
    // StateFieldWallAdsorptionAir::enter 2: no enumerator names known)
    enum Timing : unsigned int {};
    static void resetCameraForWall(gf::GfComBehaviorPc& behavior, Timing timing);
    static void setAsmSpeedSlideBrake(gf::GfComPropertyPc& property);
    // whether a player is within range of pos (AgentUtilField::isWallEndMove asks it for the wall's end)
    static bool isNearPlayer(gf::GfComPropertyPc& property, const mm::Vec3& pos, float range);
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
    static bool testVechile(gf::GfComBehaviorPc& behavior);  // whether the PC is a vehicle (GfGameRide::isVehicle)
    static void requestGetOffRider(gf::GfComBehaviorPc& behavior);
    static bool testCloud(gf::GfComPropertyPc& property);
    // the climb command a wall move mode plays ("C_climbidle" for none of 0-7)
    static ASM_CMD_ID_FIELD getAsmID(gf::pc::GfPropertyField::WALL_MOVE_MODE mode);
    // the wall the PC is on (GfPropertyField's, status bit 0x40), or while status bit 0x10000 is clear the sensor's
    // own when it found one (by its symbol)
    static const GfPropertyField::WallInfo* getWallInfoBase(gf::GfComPropertyPc& property);
    static bool isSlideStop(gf::GfComPropertyPc& property);  // (by its symbol)
    static bool isWallIdleMotion(gf::GfComAsm& comAsm);  // (by its symbol)
    // no climbable wall (StateUtil::getClimbWallInfo) or the fall action asked for (m_actions bit 3; by its symbol)
    static bool isWallFall(gf::GfComPropertyPc& property);
    // on ground (sensor flag 0, ground attribute bit 4 clear) more than m_downLanding1Height below the PC: the PC
    // lets go of the wall (by its symbol)
    static bool isWallDetach(gf::GfComPropertyPc& property);
    // modes 0, 1 and 7 climb up (by its symbol)
    static bool isWallUpMove(gf::pc::GfPropertyField::WALL_MOVE_MODE mode);
    // whether the PC can climb on in a wall move mode (0-7; none upwards while status bit 7 is set): with a wall
    // object and sensor flag 8, upwards only while the second ground lies more than m_climbUpTime + 1.3 above
    // (by its symbol)
    static bool isMovableWall(gf::GfComPropertyPc& property, gf::pc::GfPropertyField::WALL_MOVE_MODE mode);
    // whether the PC falls fast enough for the big splash (GravityParam m_bigSplashFallSpeed; by its symbol)
    static bool isBigSplashFallSpeed(gf::GfComBehaviorPc& behavior);
    // off the ground, or slide parameter m_fallHeight above it (by its symbol)
    static bool isFallFromSlideState(gf::GfComPropertyPc& property);
};

}}  // namespace gf::pc

#endif
