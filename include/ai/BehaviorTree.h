#ifndef AI_BEHAVIORTREE_H
#define AI_BEHAVIORTREE_H

#include "classes/ai/BlackBoard.h"
#include "classes/ai/RootNode.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/UniquePtr.h"
#include "mm/mtl/Vector.h"

// ai_behavior_tree.h as the game's own files name it (AIAgentField::setup's template instances); the libraries'
// own spelling is not known
#define AI_BEHAVIOR_TREE_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/ailib/src\\ailib/behavior/ai_behavior_tree.h"

namespace ai {

// a tree of behavior nodes: its setup fills a table of nodes and links them by index under its root. The member
// names are the original's (its header's assertions spell them)
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

    // the blackboard, a T made with the setup's allocator
    template <typename T>
    void createBlackBoard() {
#line 47 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_setup==true);
#line 48 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_pAllocator);
        m_blackBoard.reset(new (m_pAllocator->allocate(sizeof(T), alignof(T))) T());
    }
    // the task node nodeID, a T named name; one that asks for it (flag bit 1) hears event 2 (created)
    template <typename T>
    void createTask(unsigned int nodeID, const char* name) {
#line 60 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_setup==true);
#line 61 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_pAllocator);
#line 62 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_pNodes[nodeID] == nullptr);
        void* memory = m_pAllocator->allocate(sizeof(T), alignof(T));
        m_pNodes[nodeID] = new (memory) T(name);
        if (m_pNodes[nodeID]->m_flags & 2) {
            CreateEvent event;
            event.m_type = 2;
            m_pNodes[nodeID]->onEvent(*m_blackBoard, event);
        }
    }
    // the composite node nodeID, a T named name with room for childCount children
    template <typename T>
    void createComposite(unsigned int nodeID, const char* name, unsigned int childCount) {
#line 79 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_setup==true);
#line 80 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_pAllocator);
#line 81 AI_BEHAVIOR_TREE_PATH
        MM_ASSERT(m_pNodes[nodeID] == nullptr);
        void* memory = m_pAllocator->allocate(sizeof(T), alignof(T));
        m_pNodes[nodeID] = new (memory) T(name, childCount, m_pAllocator);
    }

    BehaviorNode* getNode(unsigned int index) const { return m_pNodes[index].get(); }

    RootNode m_root;
    mm::mtl::UniquePtr<BlackBoard> m_blackBoard;
    mm::mtl::Vector<mm::mtl::IntrusivePtr<BehaviorNode> > m_pNodes;
    mm::mtl::IAllocator* m_pAllocator;  // beginSetup's
    bool m_setup;                       // set by beginSetup, cleared by endSetup
};

}  // namespace ai

#endif
