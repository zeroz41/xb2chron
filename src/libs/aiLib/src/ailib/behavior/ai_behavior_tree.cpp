#include "ai/BehaviorTree.h"
#include "ai/DecoratorNode.h"
#include "classes/ai/CompositeNode.h"

namespace ai {

BehaviorTree::BehaviorTree() : m_allocator(nullptr), m_settingUp(false) {}

BehaviorTree::~BehaviorTree() {}

void BehaviorTree::beginSetup(unsigned int nodeCount, mm::mtl::IAllocator* allocator) {
    m_allocator = allocator;
    m_nodes.setAllocator(allocator);
    m_nodes.resize(nodeCount, mm::mtl::IntrusivePtr<BehaviorNode>());
    m_settingUp = true;
}

void BehaviorTree::endSetup() {
    m_settingUp = false;
}

void BehaviorTree::cleanup() {
    for (unsigned int i = 0; i < m_nodes.size(); i++) {
        if (m_nodes[i] && (m_nodes[i]->m_flags & 4)) {
            Event event;
            event.m_type = 4;
            m_nodes[i]->onEvent(*m_blackBoard, event);
        }
    }
    m_nodes.clear();
    m_blackBoard.reset();
    m_nodes.setAllocator(nullptr);
    m_allocator = nullptr;
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

void BehaviorTree::execute() {
    BlackBoard* pBB = m_blackBoard.get();
#line 157
    MM_ASSERT(pBB);
    bool result = m_root.execute(*pBB);
    m_root.BehaviorNode::setActiveNotiryChildren(*pBB, result);
}

mm::mtl::RTTI DecoratorNode::m_rtti("DecoratorNode", &BehaviorNode::m_rtti, nullptr);

}  // namespace ai
