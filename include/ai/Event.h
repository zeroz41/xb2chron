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

// the events by type, as the nodes' handlers take them (1.0.0's TaskFieldSensor::onChangeActivate and
// TaskFieldFollowMainPc::onCreate name them): type 1 a change of the node's active state, type 2 its creation
class ActivateEvent : public Event {};
class CreateEvent : public Event {};

}  // namespace ai

#endif
