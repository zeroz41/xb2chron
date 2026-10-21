#ifndef CLASSES_GF_PC_TASKFIELDCHECKWARP_H
#define CLASSES_GF_PC_TASKFIELDCHECKWARP_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67DC8
class TaskFieldCheckWarp : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldCheckWarp();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&);  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
};
}}  // namespace gf::pc

#endif
