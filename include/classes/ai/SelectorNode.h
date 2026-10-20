#ifndef CLASSES_AI_SELECTORNODE_H
#define CLASSES_AI_SELECTORNODE_H

#include "classes/ai/CompositeNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80F40
class SelectorNode : public ::ai::CompositeNode {
public:
    virtual ~SelectorNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void checkCondition(ai::BlackBoard const&);  // slot 3
    virtual void execute(ai::BlackBoard&);  // slot 4
};
}  // namespace ai

#endif
