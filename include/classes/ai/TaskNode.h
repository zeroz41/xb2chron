#ifndef CLASSES_AI_TASKNODE_H
#define CLASSES_AI_TASKNODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai {
// table 0x7100B80FD0
class TaskNode : public ::ai::BehaviorNode {
public:
    virtual ~TaskNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
};
}  // namespace ai

#endif
