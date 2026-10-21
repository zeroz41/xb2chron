#include "classes/ai/ParallelNode.h"

namespace ai {

ParallelNode::~ParallelNode() {}

// runs every child whose condition holds; succeeds when any of them does
bool ParallelNode::execute(BlackBoard& blackBoard) {
    bool result = false;
    for (BehaviorNode* child : m_childNodes) {
        if (child == nullptr) {
            continue;
        }
        bool childResult = false;
        if (child->checkCondition(blackBoard)) {
            childResult = child->execute(blackBoard);
        }
        child->BehaviorNode::setActiveNotiryChildren(blackBoard, childResult);
        result |= childResult;
    }
    return result;
}

mm::mtl::RTTI ParallelNode::m_rtti("ParallelNode", &CompositeNode::m_rtti, nullptr);

}  // namespace ai
