#ifndef CLASSES_GF_PC_TASKFIELDSENSOR_H
#define CLASSES_GF_PC_TASKFIELDSENSOR_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class ActivateEvent; }
namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67C00; the field AI's sensing task: reads the PC's surroundings into the blackboard's flags.
// Its unit's header defines the blackboard-typed checkCondition and execute (its citations name it)
class TaskFieldSensor : public ::ai::TaskNode {
public:
    // what BehaviorTree::createTask makes (flags from its instance)
    explicit TaskFieldSensor(const char* name) : TaskNode(name, 1) {}
    virtual ~TaskFieldSensor() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 23 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_sensor_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 23 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_sensor_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    // 1.0.0's own functions, inline in 3.0.1 (it has no copy of either)
    void onChangeActivate(gf::pc::BlackBoardField& bb, ai::ActivateEvent const& event);
    bool testCondition(gf::pc::BlackBoardField const&) { return true; }
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // createTask<TaskFieldSensor> allocates 0x50 bytes aligned to 16: a 16-aligned member (a vector) at 0x40,
    // which the constructor leaves alone
    alignas(16) unsigned char pad_40[0x10];
};
}}  // namespace gf::pc

#endif
