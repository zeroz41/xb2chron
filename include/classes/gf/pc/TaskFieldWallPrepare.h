#ifndef CLASSES_GF_PC_TASKFIELDWALLPREPARE_H
#define CLASSES_GF_PC_TASKFIELDWALLPREPARE_H

#include "mm/MMStdBase.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/UniquePtr.h"
#include "ai/Fsm.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "gf/pc/WallAiContextField.h"

namespace ai { class BlackBoard; }
namespace ai { class CreateEvent; }
namespace ai { class DestroyEvent; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67C48; the field AI's task that prepares the PC for a wall: a state machine of the wall AI's states
// (wait, prepare, adsorption) it steps while the PC holds a wall notice and is not on the wall yet. Its unit's header
// (gf_pc_ai_wall_task_field.h, which its citations name) defines the blackboard-typed checkCondition and execute
class TaskFieldWallPrepare : public ::ai::TaskNode {
public:
    virtual ~TaskFieldWallPrepare() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const& bb) {  // slot 3
        const BlackBoardField* pBB = mm::mtl::rttiCast<const BlackBoardField>(&bb);
#line 25 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
        MM_ASSERT(pBB);
        return testCondition(*pBB);
    }
    virtual bool execute(ai::BlackBoard& bb) {  // slot 4
        BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 25 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/field/ai/gf_pc_ai_wall_task_field.h"
        MM_ASSERT(pBB);
        update(*pBB);
        return true;
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    // 1.0.0's onChangeActivate, testCondition and update are inline in 3.0.1 (it has no copy of them)
    void onChangeActivate(gf::pc::BlackBoardField& bb, ai::ActivateEvent const& event);
    void onCreate(gf::pc::BlackBoardField& bb, ai::CreateEvent const& event);
    void onDestroy(gf::pc::BlackBoardField& bb, ai::DestroyEvent const& event);
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // (the field names are not the original's)
    mm::mtl::UniquePtr<ai::Fsm> m_fsm;  // onCreate's; onDestroy cleans it up and deletes it
    WallAiContextField m_context;  // the states' owner (the machine's)
};
}}  // namespace gf::pc

#endif
