#ifndef CLASSES_AI_DECORATORNODE_H
#define CLASSES_AI_DECORATORNODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// a behavior node with one child. Its table (1.0.0's 0x71011B9170) and code are gone from 3.0.1; what is left of
// ai_behavior_decorator.cpp there is its m_rtti, the initializer that builds it, and BehaviorNode::checkCondition,
// the copy its table emitted
class DecoratorNode : public ::ai::BehaviorNode {
public:
    DecoratorNode(const char* name);
    virtual ~DecoratorNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool execute(ai::BlackBoard& blackBoard);  // slot 4
    virtual void setActiveNotiryChildren(ai::BlackBoard& blackBoard, bool active) {  // slot 5
        BehaviorNode::setActiveNotiryChildren(blackBoard, active);
        // aiLib's ai_behavior_decorator.h, as its own files' include path named it
#line 41 "../../src\\ailib/behavior/node/ai_behavior_decorator.h"
        MM_ASSERT(m_pChildNode);
        m_pChildNode->setActiveNotiryChildren(blackBoard, active);
    }
    void attachChild(BehaviorNode* child);
    void detachChild();

    static mm::mtl::RTTI m_rtti;
    BehaviorNode* m_pChildNode;
};
}  // namespace ai

#endif
