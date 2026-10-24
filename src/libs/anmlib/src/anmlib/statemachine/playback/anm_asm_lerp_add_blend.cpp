#include "classes/anm/ResASM.h"
#include "classes/anm/FrozenState.h"
#include "classes/anm/LerpAddBlendTree.h"
#include "anm/Array.h"
#include "algorithm"
#include "anm/AsmBlender.h"
#include "anm/AsmVariable.h"
#include "math.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"
#include <new>

namespace anm {

LerpAddBlendTree::LerpAddBlendTree(const ResStateData* pRes, const ResLerpAddTree* pTree,
                                   mm::mtl::Vector<Variable>& variables, mm::mtl::IAllocator& allocator)
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

LerpAddBlendTree::~LerpAddBlendTree() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].destroyControl();
        m_pClips[i].~AsmClip();
    }
    m_pAllocator->deallocate(m_pClips);
    m_pClips = nullptr;
    m_clipCount = 0;
}

void LerpAddBlendTree::attach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->addClip(m_pClips[i]);
    }
}

void LerpAddBlendTree::dettach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->removeClip(m_pClips[i]);
    }
}

void LerpAddBlendTree::onEnter(AsmListener* listener) {
    initLoopCount();
    m_speed = 1.0f;
    onSetSpeed();
    notifyEnter(listener);
}

void LerpAddBlendTree::onLeave(AsmListener* listener) {
    notifyLeave(listener);
}

void LerpAddBlendTree::update(float dt, AsmListener* listener) {
    adjustWeight();
    countLoop(m_pClips[0].update(dt, listener));
    for (unsigned int i = 1; i < m_clipCount; i++) {
        m_pClips[i].update(dt, nullptr);
    }
}

void LerpAddBlendTree::adjustWeight() {
    unsigned int baseCount = m_pTree->m_baseCount;
    for (unsigned int i = 0; i < baseCount; i++) {
        m_pClips[i].setWeight(m_weight);
    }
    float key;  // (declared first: the original's frame keeps it above the value)
    float value;
    m_pVariable->getValue(&value);
    key = value;
    const Array<ResLerpAddNode>& nodes = m_pTree->m_nodes;
    ArrayIterartor<const ResLerpAddNode> it = std::lower_bound(nodes.begin(), nodes.end(), key, CompLerpAddNode());
    int index = it - nodes.begin();
    int last = nodes.size() - 1;
    index = index < last ? index : last;
    int prev = index - 1 < 0 ? 0 : index - 1;
    bool positive = !(key < 0.0f);  // (kept as a value: the original selects on `key >= 0`, unordered included)
    index = positive ? index : prev;
    float position = m_pTree->m_nodes[index].m_position;
    float rate;
    if (fabsf(position) > 1.1920929e-07f) {
        rate = value / position;
    } else {
        rate = 0.0f;
    }
    unsigned int count = m_pTree->m_nodes.size();
    for (unsigned int i = 0; i < count; i++) {
        if (i == index) {
            m_pClips[baseCount + i].setWeight(rate * m_weight);
        } else {
            m_pClips[baseCount + i].setWeight(0.0f);
        }
    }
}

void LerpAddBlendTree::setLocalTime(float time) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].setLocalTime(time);
    }
}

float LerpAddBlendTree::getLocalTime() const {
    return m_pClips[0].getLocalTime();
}

void LerpAddBlendTree::onSetSpeed() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].setSpeed(m_speed);
    }
}

void LerpAddBlendTree::onSetWeight() {
    adjustWeight();
}

AsmClip* LerpAddBlendTree::getBaseClip() const {
    return m_pClips;
}

}  // namespace anm
