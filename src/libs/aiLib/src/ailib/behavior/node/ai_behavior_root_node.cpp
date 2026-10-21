#include "classes/ai/RootNode.h"

namespace ai {

RootNode::RootNode() : BehaviorNode("RootNode", 0), m_pChildNode(nullptr) {}

RootNode::~RootNode() {}

void RootNode::attachChild(BehaviorNode* child) {
#line 42
    MM_ASSERT(m_pChildNode == nullptr);
    m_pChildNode = child;
}

bool RootNode::execute(BlackBoard& blackBoard) {
    bool result;
    if (m_pChildNode->checkCondition(blackBoard)) {
        result = m_pChildNode->execute(blackBoard);
        m_pChildNode->BehaviorNode::setActiveNotiryChildren(blackBoard, result);
    } else {
        m_pChildNode->setActiveNotiryChildren(blackBoard, false);
        result = false;
    }
    return result;
}

mm::mtl::RTTI RootNode::m_rtti("RootNode", &BehaviorNode::m_rtti, nullptr);

}  // namespace ai
