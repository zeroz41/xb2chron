#include "classes/ai/BehaviorNode.h"

namespace ai {

BehaviorNode::BehaviorNode(const char* name, unsigned int flags) : m_active(false), m_flags(flags) {
    m_name = name;
}

BehaviorNode::~BehaviorNode() {}

mm::mtl::RTTI BehaviorNode::m_rtti("BehaviorNode", nullptr, nullptr);

}  // namespace ai
