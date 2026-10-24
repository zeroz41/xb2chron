#ifndef CLASSES_GF_PC_TASKFIELDJUMP_H
#define CLASSES_GF_PC_TASKFIELDJUMP_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B67930
class TaskFieldJump : public ::ai::TaskNode {
public:
    // what BehaviorTree::createTask makes (flags from its instance)
    explicit TaskFieldJump(const char* name) : TaskNode(name, 0) {}
    // its field AI parameter entry (AgentUtilField::getAIParamAdapter's 4); the name is not the original's
    struct Param {
        float m_minSpeed;  // update launches the PC at least this fast
    };

    virtual ~TaskFieldJump() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 23 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_jump_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 23 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_jump_task_field.h"
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
