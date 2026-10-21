#ifndef CLASSES_AI_SEQUENCENODE_H
#define CLASSES_AI_SEQUENCENODE_H

#include "classes/ai/CompositeNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80F88
class SequenceNode : public ::ai::CompositeNode {
public:
    virtual ~SequenceNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&) { return true; }  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
};
}  // namespace ai

#endif
