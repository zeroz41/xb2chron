#ifndef CLASSES_GF_PC_TASKFIELDCHECKWARP_H
#define CLASSES_GF_PC_TASKFIELDCHECKWARP_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class ActivateEvent; }
namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67DC8; the field AI's task that warps a PC left behind to the formation (or, on a wall, to the
// wall follow transform). Its unit's header (gf_pc_ai_warp_task_field.h, which its citations name) defines the
// blackboard-typed checkCondition and execute
class TaskFieldCheckWarp : public ::ai::TaskNode {
public:
    // what BehaviorTree::createTask makes (flags from its instance)
    explicit TaskFieldCheckWarp(const char* name) : TaskNode(name, 1) {}
    virtual ~TaskFieldCheckWarp() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 26 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 26 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    // 1.0.0's own functions, inline in 3.0.1 (it has no copy of any but update)
    void onChangeActivate(gf::pc::BlackBoardField& bb, ai::ActivateEvent const& event);
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // how long the PC has been stuck (the blackboard's bit 0): update adds the frame's time while it is, and
    // clears it otherwise and when the task turns active (the name is not the original's)
    float m_stuckTime;
};
}}  // namespace gf::pc

#endif
