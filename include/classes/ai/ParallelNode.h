#ifndef CLASSES_AI_PARALLELNODE_H
#define CLASSES_AI_PARALLELNODE_H

#include "classes/ai/CompositeNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80EF8
class ParallelNode : public ::ai::CompositeNode {
public:
    virtual ~ParallelNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void checkCondition(ai::BlackBoard const&);  // slot 3
    virtual void execute(ai::BlackBoard&);  // slot 4
};
}  // namespace ai

#endif
