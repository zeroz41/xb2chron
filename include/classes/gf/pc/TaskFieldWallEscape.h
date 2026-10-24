#ifndef CLASSES_GF_PC_TASKFIELDWALLESCAPE_H
#define CLASSES_GF_PC_TASKFIELDWALLESCAPE_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B67A08
class TaskFieldWallEscape : public ::ai::TaskNode {
public:
    // what BehaviorTree::createTask makes (flags from its instance)
    explicit TaskFieldWallEscape(const char* name) : TaskNode(name, 0) {}
    virtual ~TaskFieldWallEscape() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 81 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 81 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    // (its checkCondition and execute, which call these, are emitted where its table is)
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // testCondition's: how far the other players push the PC (AgentUtilField::calcParentPlayerPush's; the name is
    // not the original's)
    mm::Vec3 m_push;
};
}}  // namespace gf::pc

#endif
