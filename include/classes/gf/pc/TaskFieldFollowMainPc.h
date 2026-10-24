#ifndef CLASSES_GF_PC_TASKFIELDFOLLOWMAINPC_H
#define CLASSES_GF_PC_TASKFIELDFOLLOWMAINPC_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class ActivateEvent; }
namespace ai { class BlackBoard; }
namespace ai { class CreateEvent; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67BB8; the field AI's task that follows the main PC (isFollowMainPc), holding on for the AI's
// adjustTime after the test stops passing. Its unit's header defines the blackboard-typed checkCondition and execute
class TaskFieldFollowMainPc : public ::ai::TaskNode {
public:
    // what BehaviorTree::createTask makes (flags from its instance)
    explicit TaskFieldFollowMainPc(const char* name) : TaskNode(name, 3) {}
    virtual ~TaskFieldFollowMainPc() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 36 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_follow_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 36 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_follow_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    // 1.0.0's own functions, inline in 3.0.1 (it has no copy of any)
    void onChangeActivate(gf::pc::BlackBoardField& bb, ai::ActivateEvent const& event);
    void onCreate(gf::pc::BlackBoardField& bb, ai::CreateEvent const& event);
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // the time since isFollowMainPc stopped passing while m_adjusting (the names are not the original's)
    float m_adjustTimer;
    // set while isFollowMainPc passes; once the timer reaches the AI's adjustTime it clears, and the task runs
    // once more if the PC is at least adjustDist from its target
    bool m_adjusting;
};
}}  // namespace gf::pc

#endif
