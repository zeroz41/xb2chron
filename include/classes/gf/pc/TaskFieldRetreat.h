#ifndef CLASSES_GF_PC_TASKFIELDRETREAT_H
#define CLASSES_GF_PC_TASKFIELDRETREAT_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B67AE0
class TaskFieldRetreat : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldRetreat();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void checkCondition(ai::BlackBoard const&);  // slot 3
    virtual void execute(ai::BlackBoard&);  // slot 4
};
}}  // namespace gf::pc

#endif
