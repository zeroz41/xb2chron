#ifndef CLASSES_AI_SEQUENCENODE_H
#define CLASSES_AI_SEQUENCENODE_H

#include "classes/ai/CompositeNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80F88
class SequenceNode : public ::ai::CompositeNode {
public:
    // what BehaviorTree::createComposite makes
    SequenceNode(const char* name, unsigned int childCount, mm::mtl::IAllocator* allocator)
        : CompositeNode(name, childCount, allocator) {}
    virtual ~SequenceNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&) { return true; }  // slot 3
    virtual bool execute(ai::BlackBoard& blackBoard);  // slot 4

    static mm::mtl::RTTI m_rtti;
};
}  // namespace ai

#endif
