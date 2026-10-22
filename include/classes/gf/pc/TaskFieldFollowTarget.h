#ifndef CLASSES_GF_PC_TASKFIELDFOLLOWTARGET_H
#define CLASSES_GF_PC_TASKFIELDFOLLOWTARGET_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B67978; the field AI's task that routes the PC toward the formation's target position. Its unit's
// header (gf_pc_ai_follow_task_field.h, which its citations name) defines the blackboard-typed checkCondition and
// execute
class TaskFieldFollowTarget : public ::ai::TaskNode {
public:
    virtual ~TaskFieldFollowTarget() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 23 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_follow_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 23 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_follow_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
