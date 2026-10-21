#include "classes/ai/SequenceNode.h"

namespace ai {

SequenceNode::~SequenceNode() {}

// runs the children in order while they succeed; the rest are made inactive
bool SequenceNode::execute(BlackBoard& blackBoard) {
    bool result = true;
    for (BehaviorNode* child : m_childNodes) {
        if (child == nullptr) {
            continue;
        }
        bool childResult;
        if (result && child->checkCondition(blackBoard)) {
            childResult = child->execute(blackBoard);
            child->BehaviorNode::setActiveNotiryChildren(blackBoard, childResult);
        } else {
            child->setActiveNotiryChildren(blackBoard, false);
            childResult = false;
        }
        result &= childResult;
    }
    return result;
}

mm::mtl::RTTI SequenceNode::m_rtti("SequenceNode", &CompositeNode::m_rtti, nullptr);

}  // namespace ai
