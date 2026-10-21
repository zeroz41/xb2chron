#ifndef CLASSES_GF_PC_TASKFIELDWALLJUMPWAIT_H
#define CLASSES_GF_PC_TASKFIELDWALLJUMPWAIT_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B679C0
class TaskFieldWallJumpWait : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldWallJumpWait();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&);  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
