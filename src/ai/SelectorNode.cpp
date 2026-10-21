#include "classes/ai/SelectorNode.h"

namespace ai {

SelectorNode::~SelectorNode() {}

// runs the children in order until one succeeds; the rest are made inactive
bool SelectorNode::execute(BlackBoard& blackBoard) {
    bool result = false;
    for (BehaviorNode* child : m_childNodes) {
        if (child == nullptr) {
            continue;
        }
        bool childResult;
        if (!result && child->checkCondition(blackBoard)) {
            childResult = child->execute(blackBoard);
            child->BehaviorNode::setActiveNotiryChildren(blackBoard, childResult);
        } else {
            child->setActiveNotiryChildren(blackBoard, false);
            childResult = false;
        }
        result |= childResult;
    }
    return result;
}

mm::mtl::RTTI SelectorNode::m_rtti("SelectorNode", &CompositeNode::m_rtti, nullptr);

}  // namespace ai
