#include "mm/mtl/IntrusivePtr.h"
#include "ai/BehaviorTree.h"
#include "classes/ai/DecoratorNode.h"
#include "classes/ai/CompositeNode.h"

namespace ai {

BehaviorTree::BehaviorTree() : m_pAllocator(nullptr), m_setup(false) {}

BehaviorTree::~BehaviorTree() {}

void BehaviorTree::beginSetup(unsigned int nodeCount, mm::mtl::IAllocator* allocator) {
    m_pAllocator = allocator;
    m_pNodes.setAllocator(allocator);
    m_pNodes.resize(nodeCount, mm::mtl::IntrusivePtr<BehaviorNode>());
    m_setup = true;
}

void BehaviorTree::endSetup() {
    m_setup = false;
}

void BehaviorTree::cleanup() {
    for (unsigned int i = 0; i < m_pNodes.size(); i++) {
        if (m_pNodes[i] && (m_pNodes[i]->m_flags & 4)) {
            Event event;
            event.m_type = 4;
            m_pNodes[i]->onEvent(*m_blackBoard, event);
        }
    }
    m_pNodes.clear();
    m_blackBoard.reset();
    m_pNodes.setAllocator(nullptr);
    m_pAllocator = nullptr;
}

void BehaviorTree::attachRoot(unsigned int index) {
    BehaviorNode* pNode = getNode(index);
#line 88
    MM_ASSERT(pNode);
    m_root.attachChild(pNode);
}

void BehaviorTree::attachComposite(unsigned int compositeIndex, unsigned int childIndex, unsigned int slot) {
    BehaviorNode* node = getNode(compositeIndex);
    CompositeNode* pComposite = node != nullptr && node->getRTTI()->isKindOf(&CompositeNode::m_rtti)
                                    ? static_cast<CompositeNode*>(node)
                                    : nullptr;
#line 104
    MM_ASSERT(pComposite);
    BehaviorNode* pChildNode = getNode(childIndex);
#line 107
    MM_ASSERT(pChildNode);
    pComposite->attachChild(slot, pChildNode);
}

void BehaviorTree::attachDecorator(unsigned int decoratorIndex, unsigned int childIndex) {
    BehaviorNode* node = getNode(decoratorIndex);
    DecoratorNode* pDecorator = node != nullptr && node->getRTTI()->isKindOf(&DecoratorNode::m_rtti)
                                    ? static_cast<DecoratorNode*>(node)
                                    : nullptr;
#line 121
    MM_ASSERT(pDecorator);
    BehaviorNode* pChildNode = getNode(childIndex);
#line 124
    MM_ASSERT(pChildNode);
    pDecorator->attachChild(pChildNode);
}

void BehaviorTree::execute() {
    BlackBoard* pBB = m_blackBoard.get();
#line 157
    MM_ASSERT(pBB);
    bool result = m_root.execute(*pBB);
    m_root.BehaviorNode::setActiveNotiryChildren(*pBB, result);
}

}  // namespace ai
