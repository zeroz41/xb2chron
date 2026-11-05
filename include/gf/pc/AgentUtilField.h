#ifndef GF_PC_AGENTUTILFIELD_H
#define GF_PC_AGENTUTILFIELD_H

#include "fw/ParamAdapter.h"
#include "mm/Vec2.h"

namespace gf { class GfComPropertyPc; }
namespace gf { namespace pc { class BlackBoardField; } }
namespace fw { class Transform; }
namespace mm { class Vec3; }
namespace navi { class NvmshAcObj; }

namespace gf { namespace pc {

// the field AI's parameter entries, by index into the AI agent's parameter list; no value has a name yet
// (funcFollowInput<FollowMainPcParam> reads 0 and 1, funcFollowInput<FollowBuddyPcParam> 2 and 3,
// TaskFieldJump::update 4)
enum PARAM_ID_FIELD_AI {};

// the field AI's parameter blocks: their names and their fields' names are 1.0.0's (each one's createReflection
// registers the fields by name and offset)
struct SensorAIParam {        // entry 3 of the PC's parameter list (TaskFieldSensor::update)
    float stackThreashold;    // the PC is stuck when it moved this much less than its velocity would carry it
    float obstacleAngle;      // degrees from level past which a face is an obstacle
    float enableJumpOffset;   // the PC may jump onto an obstacle its target is this far above
    float enableJumpCeil;     // and not while what is above it is this close
};
struct WarpParam {            // entry 2 of the PC's parameter list (TaskFieldCheckWarp::update)
    float distanceHorz;       // the PC is not left behind while this close to its warp position across the ground
    float distanceVert;       // and this close in height (and stuck no longer than stackTime)
    float stackTime;
    float naviSearchUp;
    float naviSearchDown;
    float fadeTime;
    float wallSearchDist;
    float distanceHorzWall;   // the same two distances on a wall
    float distanceVertWall;
};
struct WallAiParam {          // entry 5 of the field AI's (getAIParamAdapter)
    float prepareRange;
    float minDist;
    float fallDelay;
    float climbEndSafeRange;
    float escapeRange;
    float nearRange;
    int delay;
};
struct FollowMainPcParam {    // entries 0 and 1 (in water)
    float followDist;
    float stopDist;
    float powMinDist;
    float powMaxDist;
    float adjustTime;
    float adjustDist;
    float walkDistStopFollower;
};
// entries 6 and 7 (7 for the water warps): how long the field AI waits before acting on a notice
// (AIAgentField's high jump and water warp handlers); 2.0.0's name and field names, by its createReflection
struct ForceWarpAiParam {
    float baseWaitTime;
    float waitTimeRange;  // up to this much more, at random
};
struct FollowBuddyPcParam {   // entries 2 and 3 (in water)
    float stopDist;
    float powMinDist;
    float powMaxDist;
    float walkDistStopFollower;
};

// what the field AI's tasks share (functions, by its symbols)
class AgentUtilField {
public:
    static void setIdleInput(gf::GfComPropertyPc& property);
    static float setFollowInput(float distance, navi::NvmshAcObj* nvmshAcObj, gf::GfComPropertyPc& property);
    static fw::ParamAdapter getAIParamAdapter(gf::GfComPropertyPc& property, PARAM_ID_FIELD_AI id);
    // the transform a PC on a wall follows; false without one
    static bool getWallFollowTransform(const BlackBoardField& bb, fw::Transform* transform);
    static bool calcParentPlayerPush(gf::GfComPropertyPc& property, const mm::Vec3& pos, float range, mm::Vec3* push);
    // the stick input that follows a wall toward pos
    static mm::Vec2 calcFollowWallInput(const mm::Vec3& pos, gf::GfComPropertyPc& property);
    static bool isEnableWallMove(gf::GfComPropertyPc& property, const mm::Vec2& input);
    static bool isWallEndMove(const BlackBoardField& bb);
    static void setFollowWallEndInput(const mm::Vec3& pos, gf::GfComPropertyPc& property);
    // whether another player climbs near pos
    static bool existNearChimbPlayer(gf::GfComPropertyPc& property, const mm::Vec3& pos);
    static bool isWallJumpAnyPlayer();
};

// setFollowInput's two halves (by their symbols): the stick toward the navigation's move direction, its power the
// distance's place between the parameter block's powMinDist and powMaxDist (entry WATER_ID in deep water)
template <typename PARAM, PARAM_ID_FIELD_AI ID, PARAM_ID_FIELD_AI WATER_ID>
float funcFollowInput(float distance, navi::NvmshAcObj* nvmshAcObj, gf::GfComPropertyPc& property);

}}  // namespace gf::pc

#endif
