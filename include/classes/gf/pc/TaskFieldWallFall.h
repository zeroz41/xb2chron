#ifndef CLASSES_GF_PC_TASKFIELDWALLFALL_H
#define CLASSES_GF_PC_TASKFIELDWALLFALL_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67C90; the field AI's task that lets go of a wall after a while (the wall AI parameters' fallDelay).
// Its unit's header (gf_pc_ai_wall_task_field.h, which its citations name) defines the blackboard-typed
// checkCondition and execute
class TaskFieldWallFall : public ::ai::TaskNode {
public:
    virtual ~TaskFieldWallFall() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 61 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 61 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    // 1.0.0's testCondition and update are inline in 3.0.1 (it has no copy of them)
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    float m_time;  // how long the PC has held the wall (cleared on creation and when the task turns inactive)
};
}}  // namespace gf::pc

#endif
