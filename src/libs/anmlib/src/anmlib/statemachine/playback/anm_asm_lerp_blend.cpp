#include "anm/Array.h"
#include "algorithm"
#include "anm/AsmBlender.h"
#include "anm/AsmVariable.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/LerpBlendTree.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"
#include <new>

namespace anm {

LerpBlendTree::LerpBlendTree(const ResStateData* pRes, const ResLerpTree* pTree, mm::mtl::Vector<Variable>& variables,
                             mm::mtl::IAllocator& allocator)
    : AsmState(pRes, allocator), m_pTree(pTree) {
    m_clipCount = pRes->m_clips.size();
    m_pClips = static_cast<AsmClip*>(allocator.allocate(sizeof(AsmClip) * m_clipCount, 8));
    for (unsigned int i = 0; i < m_clipCount; i++) {
        AsmClip* pClip = new (&m_pClips[i]) AsmClip();
        pClip->createControl(pRes->m_clips[i], allocator);
    }
    m_pVariable = &variables[m_pTree->m_variableIndex];
#line 38
    MM_ASSERT(m_pVariable->getVarType() == VAR_FLOAT);
}

LerpBlendTree::~LerpBlendTree() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].destroyControl();
        m_pClips[i].~AsmClip();
    }
    m_pAllocator->deallocate(m_pClips);
    m_pClips = nullptr;
    m_clipCount = 0;
}

void LerpBlendTree::attach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->addClip(m_pClips[i]);
    }
}

void LerpBlendTree::dettach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->removeClip(m_pClips[i]);
    }
}

void LerpBlendTree::onEnter(AsmListener* listener) {
    initLoopCount();
    m_speed = 1.0f;
    onSetSpeed();
    notifyEnter(listener);
}

void LerpBlendTree::onLeave(AsmListener* listener) {
    notifyLeave(listener);
}

void LerpBlendTree::update(float dt, AsmListener* listener) {
    adjustWeight();
    countLoop(m_pClips[0].update(dt, listener));
    for (unsigned int i = 1; i < m_clipCount; i++) {
        m_pClips[i].update(dt, nullptr);
    }
}

void LerpBlendTree::adjustWeight() {
    float key;  // (declared first: the original's frame keeps it above the value)
    float value;
    m_pVariable->getValue(&value);
    key = value;
    const Array<ResLerpNode>& nodes = m_pTree->m_nodes;
    ArrayIterartor<const ResLerpNode> it = std::upper_bound(nodes.begin(), nodes.end(), key, CompLerpNode());
    unsigned int index;
    if (it == nodes.begin()) {
        index = 0;
    } else {
        index = it - nodes.begin();
        unsigned int last = nodes.size() - 1;
        index = (index < last ? index : last) - 1;
    }
    float from = m_pTree->m_nodes[index].m_position;
    float to = m_pTree->m_nodes[index + 1].m_position;
    float rate = (value - to) / (from - to);
    for (unsigned int i = 0; i < m_clipCount; i++) {
        if (i == index) {
            m_pClips[index].setWeight(rate * m_weight);
        } else if (i == index + 1) {
            m_pClips[i].setWeight((1.0f - rate) * m_weight);
        } else {
            m_pClips[i].setWeight(0.0f);
        }
    }
}

void LerpBlendTree::setLocalTime(float time) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].setLocalTime(time);
    }
}

float LerpBlendTree::getLocalTime() const {
    return m_pClips[0].getLocalTime();
}

void LerpBlendTree::onSetSpeed() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].setSpeed(m_speed);
    }
}

void LerpBlendTree::onSetWeight() {
    adjustWeight();
}

AsmClip* LerpBlendTree::getBaseClip() const {
    return m_pClips;
}

}  // namespace anm
