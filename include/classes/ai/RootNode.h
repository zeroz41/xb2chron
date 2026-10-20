#ifndef CLASSES_AI_ROOTNODE_H
#define CLASSES_AI_ROOTNODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80E68
class RootNode : public ::ai::BehaviorNode {
public:
    virtual ~RootNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ai::BlackBoard&);  // slot 4
    virtual void setActiveNotiryChildren(ai::BlackBoard&, bool);  // slot 5
};
}  // namespace ai

#endif
