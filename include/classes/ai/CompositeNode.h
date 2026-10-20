#ifndef CLASSES_AI_COMPOSITENODE_H
#define CLASSES_AI_COMPOSITENODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80EB0
class CompositeNode : public ::ai::BehaviorNode {
public:
    virtual ~CompositeNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void setActiveNotiryChildren(ai::BlackBoard&, bool);  // slot 5
};
}  // namespace ai

#endif
