#ifndef CLASSES_GF_PC_TASKFIELDCHECKWARPBATTLEWATERDEAD_H
#define CLASSES_GF_PC_TASKFIELDCHECKWARPBATTLEWATERDEAD_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "fw/ParamAdapter.h"

namespace ai { class ActivateEvent; }
namespace ai { class BlackBoard; }
namespace ai { class CreateEvent; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67E10; the field AI's task that, in battle, warps a PC dead in water back to the formation after
// a while. Its unit's header (gf_pc_ai_warp_task_field.h, which its citations name) defines the blackboard-typed
// checkCondition and execute
class TaskFieldCheckWarpBattleWaterDead : public ::ai::TaskNode {
public:
    virtual ~TaskFieldCheckWarpBattleWaterDead() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 44 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 44 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    // 1.0.0's own functions, inline in 3.0.1 (it has no copy of any but update)
    void onChangeActivate(gf::pc::BlackBoardField& bb, ai::ActivateEvent const& event);
    void onCreate(gf::pc::BlackBoardField& bb, ai::CreateEvent const& event);
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // how long the task has been active (update adds the frame's time; the name is not the original's)
    float m_time;
    // the first entry of the parameter manager's list 10 (onCreate takes it): its first value is the time after
    // which update warps the PC (the name is not the original's)
    fw::ParamAdapter m_param;
};
}}  // namespace gf::pc

#endif
