#ifndef AI_EVENT_H
#define AI_EVENT_H

namespace ai {

// what a behavior node's onEvent receives
class Event {
public:
    // 1: the node's active state changed (BehaviorNode::setActiveNotiryChildren); 4: its tree is cleaned up
    // (BehaviorTree::cleanup, to the nodes whose flags ask for it)
    int m_type;
    bool m_active;  // with type 1: the new state
};

}  // namespace ai

#endif
