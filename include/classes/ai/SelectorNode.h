#ifndef CLASSES_AI_SELECTORNODE_H
#define CLASSES_AI_SELECTORNODE_H

#include "classes/ai/CompositeNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80F40
class SelectorNode : public ::ai::CompositeNode {
public:
    virtual ~SelectorNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&) { return true; }  // slot 3
    virtual bool execute(ai::BlackBoard& blackBoard);  // slot 4

    static mm::mtl::RTTI m_rtti;
};
}  // namespace ai

#endif
