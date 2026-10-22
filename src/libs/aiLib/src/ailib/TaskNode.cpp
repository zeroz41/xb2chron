#include "classes/ai/TaskNode.h"

namespace ai {

TaskNode::TaskNode(const char* name, unsigned int flags) : BehaviorNode(name, flags) {}

TaskNode::~TaskNode() {}

mm::mtl::RTTI TaskNode::m_rtti("TaskNode", &BehaviorNode::m_rtti, nullptr);

}  // namespace ai
