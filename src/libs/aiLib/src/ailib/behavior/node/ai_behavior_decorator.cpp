#include "classes/ai/DecoratorNode.h"

namespace ai {

mm::mtl::RTTI DecoratorNode::m_rtti("DecoratorNode", &BehaviorNode::m_rtti, nullptr);

DecoratorNode::DecoratorNode(const char* name) : BehaviorNode(name, 0), m_pChildNode(nullptr) {}

DecoratorNode::~DecoratorNode() {}

void DecoratorNode::attachChild(BehaviorNode* child) {
#line 43
    MM_ASSERT(m_pChildNode == nullptr);
    m_pChildNode = child;
}

void DecoratorNode::detachChild() {
    m_pChildNode = nullptr;
}

bool DecoratorNode::execute(BlackBoard& blackBoard) {
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

}  // namespace ai
