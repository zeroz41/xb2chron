#ifndef AI_DECORATORNODE_H
#define AI_DECORATORNODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai {

// a behavior node by its type information alone: ai_behavior_tree.cpp defines its m_rtti ("DecoratorNode", based
// on BehaviorNode's), and nothing else of it is left in the module
class DecoratorNode : public ::ai::BehaviorNode {
public:
    static mm::mtl::RTTI m_rtti;
};

}  // namespace ai

#endif
