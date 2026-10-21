#ifndef CLASSES_AI_ROOTNODE_H
#define CLASSES_AI_ROOTNODE_H

#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80E68
class RootNode : public ::ai::BehaviorNode {
public:
    RootNode();
    virtual ~RootNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool execute(ai::BlackBoard& blackBoard);  // slot 4
    virtual void setActiveNotiryChildren(ai::BlackBoard& blackBoard, bool active) {  // slot 5
        BehaviorNode::setActiveNotiryChildren(blackBoard, active);
        // aiLib's ai_behavior_root_node.h, as its own files' include path named it
#line 39 "../../src\\ailib/behavior/node/ai_behavior_root_node.h"
        MM_ASSERT(m_pChildNode);
        m_pChildNode->setActiveNotiryChildren(blackBoard, active);
    }
    void attachChild(BehaviorNode* child);

    static mm::mtl::RTTI m_rtti;
    BehaviorNode* m_pChildNode;
};
}  // namespace ai

#endif
