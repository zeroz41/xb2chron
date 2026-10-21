#ifndef CLASSES_AI_TASKNODE_H
#define CLASSES_AI_TASKNODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai {
// table 0x7100B80FD0
class TaskNode : public ::ai::BehaviorNode {
public:
    TaskNode(const char* name, unsigned int flags);
    virtual ~TaskNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2

    static mm::mtl::RTTI m_rtti;
};
}  // namespace ai

#endif
