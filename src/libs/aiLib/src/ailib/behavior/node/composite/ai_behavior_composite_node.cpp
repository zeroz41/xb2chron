#include "classes/ai/CompositeNode.h"

namespace ai {

CompositeNode::CompositeNode(const char* name, unsigned int childCount, mm::mtl::IAllocator* allocator)
    : BehaviorNode(name, 0), m_childNodes(allocator) {
    m_childNodes.resize(childCount, nullptr);
}

void CompositeNode::setActiveNotiryChildren(BlackBoard& blackBoard, bool active) {
    BehaviorNode::setActiveNotiryChildren(blackBoard, active);
    for (BehaviorNode* child : m_childNodes) {
        if (child != nullptr) {
            child->setActiveNotiryChildren(blackBoard, active);
        }
    }
}

CompositeNode::~CompositeNode() {}

void CompositeNode::attachChild(unsigned int index, BehaviorNode* child) {
#line 68
    MM_ASSERT(m_childNodes[index] == nullptr);
    m_childNodes[index] = child;
}

mm::mtl::RTTI CompositeNode::m_rtti("CompositeNode", &BehaviorNode::m_rtti, nullptr);

}  // namespace ai
