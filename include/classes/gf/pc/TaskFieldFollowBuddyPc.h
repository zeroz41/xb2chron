#ifndef CLASSES_GF_PC_TASKFIELDFOLLOWBUDDYPC_H
#define CLASSES_GF_PC_TASKFIELDFOLLOWBUDDYPC_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B67A98
class TaskFieldFollowBuddyPc : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldFollowBuddyPc();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void checkCondition(ai::BlackBoard const&);  // slot 3
    virtual void execute(ai::BlackBoard&);  // slot 4
};
}}  // namespace gf::pc

#endif
