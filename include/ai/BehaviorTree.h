#ifndef AI_BEHAVIORTREE_H
#define AI_BEHAVIORTREE_H

#include "classes/ai/BlackBoard.h"
#include "classes/ai/RootNode.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/UniquePtr.h"
#include "mm/mtl/Vector.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace ai {

// a tree of behavior nodes: its setup fills a table of nodes and links them by index under its root
class BehaviorTree {
public:
    BehaviorTree();
    ~BehaviorTree();
    void beginSetup(unsigned int nodeCount, mm::mtl::IAllocator* allocator);
    void endSetup();
    void cleanup();
    void attachRoot(unsigned int index);
    void attachComposite(unsigned int compositeIndex, unsigned int childIndex, unsigned int slot);
    void attachDecorator(unsigned int decoratorIndex, unsigned int childIndex);
    void execute();

    BehaviorNode* getNode(unsigned int index) const { return m_nodes[index].get(); }

    RootNode m_root;
    mm::mtl::UniquePtr<BlackBoard> m_blackBoard;
    mm::mtl::Vector<mm::mtl::IntrusivePtr<BehaviorNode> > m_nodes;
    mm::mtl::IAllocator* m_allocator;  // beginSetup's
    bool m_settingUp;                  // set by beginSetup, cleared by endSetup
};

}  // namespace ai

#endif
