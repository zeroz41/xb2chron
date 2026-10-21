#ifndef CLASSES_AI_COMPOSITENODE_H
#define CLASSES_AI_COMPOSITENODE_H

#include "classes/ai/BehaviorNode.h"
#include "mm/mtl/Vector.h"

namespace ai { class BlackBoard; }
namespace mm { namespace mtl { class IAllocator; }}

namespace ai {
// table 0x7100B80EB0
class CompositeNode : public ::ai::BehaviorNode {
public:
    CompositeNode(const char* name, unsigned int childCount, mm::mtl::IAllocator* allocator);
    virtual ~CompositeNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void setActiveNotiryChildren(ai::BlackBoard& blackBoard, bool active);  // slot 5
    void attachChild(unsigned int index, BehaviorNode* child);

    static mm::mtl::RTTI m_rtti;
    mm::mtl::Vector<BehaviorNode*> m_childNodes;
};
}  // namespace ai

#endif
