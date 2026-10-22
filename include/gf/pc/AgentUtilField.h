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

// what the field AI's tasks share (functions, by its symbols)
class AgentUtilField {
public:
    static void setIdleInput(gf::GfComPropertyPc& property);
    static float setFollowInput(float distance, navi::NvmshAcObj* nvmshAcObj, gf::GfComPropertyPc& property);
    static fw::ParamAdapter getAIParamAdapter(gf::GfComPropertyPc& property, PARAM_ID_FIELD_AI id);
};

}}  // namespace gf::pc

#endif
