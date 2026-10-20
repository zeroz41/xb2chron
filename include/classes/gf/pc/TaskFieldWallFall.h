#ifndef CLASSES_GF_PC_TASKFIELDWALLFALL_H
#define CLASSES_GF_PC_TASKFIELDWALLFALL_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67C90
class TaskFieldWallFall : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldWallFall();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void checkCondition(ai::BlackBoard const&);  // slot 3
    virtual void execute(ai::BlackBoard&);  // slot 4
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
};
}}  // namespace gf::pc

#endif
