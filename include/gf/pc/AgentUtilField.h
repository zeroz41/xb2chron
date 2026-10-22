#ifndef GF_PC_AGENTUTILFIELD_H
#define GF_PC_AGENTUTILFIELD_H

#include "fw/ParamAdapter.h"

namespace gf { class GfComPropertyPc; }
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
struct FollowMainPcParam {    // entries 0 and 1 (in water)
    float followDist;
    float stopDist;
    float powMinDist;
    float powMaxDist;
    float adjustTime;
    float adjustDist;
    float walkDistStopFollower;
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
};

}}  // namespace gf::pc

#endif
