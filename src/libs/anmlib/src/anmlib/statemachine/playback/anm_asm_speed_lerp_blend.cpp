#include "anm/Array.h"
#include "algorithm"
#include "anm/AsmBlender.h"
#include "anm/AsmVariable.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/SimplexState.h"
#include "classes/anm/SpeedLerpBlendTree.h"
#include "anm/Util.h"
#include "classes/anm/Control.h"
#include "math.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"
#include <new>

namespace anm {

SpeedLerpBlendTree::SpeedLerpBlendTree(const ResStateData* pRes, const ResSpeedLerpTree* pTree,
                                       mm::mtl::Vector<Variable>& variables, mm::mtl::IAllocator& allocator)
    : AsmState(pRes, allocator), m_pTree(pTree) {
    m_clipCount = pRes->m_clips.size();
    m_pClips = static_cast<AsmClip*>(allocator.allocate(sizeof(AsmClip) * m_clipCount, 8));
    for (unsigned int i = 0; i < m_clipCount; i++) {
        AsmClip* pClip = new (&m_pClips[i]) AsmClip();
        pClip->createControl(pRes->m_clips[i], allocator);
    }
    m_pVariable = &variables[m_pTree->m_variableIndex];
#line 39
    MM_ASSERT(m_pVariable->getVarType() == VAR_FLOAT);
}

SpeedLerpBlendTree::~SpeedLerpBlendTree() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].destroyControl();
        m_pClips[i].~AsmClip();
    }
    m_pAllocator->deallocate(m_pClips);
    m_pClips = nullptr;
    m_clipCount = 0;
}

void SpeedLerpBlendTree::attach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->addClip(m_pClips[i]);
    }
}

void SpeedLerpBlendTree::dettach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->removeClip(m_pClips[i]);
    }
}

void SpeedLerpBlendTree::onEnter(AsmListener* listener) {
    initLoopCount();
    m_speed = 1.0f;
    onSetSpeed();
    notifyEnter(listener);
}

void SpeedLerpBlendTree::onLeave(AsmListener* listener) {
    notifyLeave(listener);
}

void SpeedLerpBlendTree::update(float dt, AsmListener* listener) {
    adjustSpeesAndWeight();
    countLoop(m_pClips[0].update(dt, listener));
    for (unsigned int i = 1; i < m_clipCount; i++) {
        m_pClips[i].update(dt, nullptr);
    }
}

void SpeedLerpBlendTree::adjustSpeesAndWeight() {
#line 199
    MM_ASSERT(m_pVariable);
    float key;  // (declared first: the original's frame keeps it above the value)
    float value;
    m_pVariable->getValue(&value);
    key = value;
    const Array<ResSpeedLerpNode>& nodes = m_pTree->m_nodes;
    ArrayIterartor<const ResSpeedLerpNode> it = std::upper_bound(nodes.begin(), nodes.end(), key, CompLerpNode());
    unsigned int index;
    if (it == nodes.begin()) {
        index = 0;
    } else {
        index = it - nodes.begin();
        unsigned int last = nodes.size() - 1;
        index = (index < last ? index : last) - 1;
    }
    if (m_pClips[index].m_pControl == nullptr || m_pClips[index + 1].m_pControl == nullptr) {
        return;
    }
    float from = m_pTree->m_nodes[index].m_position;
    float to = m_pTree->m_nodes[index + 1].m_position;
    float rate = (value - from) / (to - from);
    rate = rate < 0.0f ? 0.0f : (rate > 1.0f ? 1.0f : rate);
    float fromTime = Util::getPlayBackTime(*m_pClips[index].m_pControl->m_pBinding);
    float toTime = Util::getPlayBackTime(*m_pClips[index + 1].m_pControl->m_pBinding);
    float timeScale = fromTime > 1.1920929e-07f ? toTime / fromTime : 0.0f;
    float speed = from * (1.0f - rate) + rate * (to * timeScale);
    float speedScale = fabsf(speed) > 1.1920929e-07f ? value / speed : 0.0f;
    for (unsigned int i = 0; i < m_clipCount; i++) {
        if (i == index) {
            m_pClips[index].setWeight((1.0f - rate) * m_weight);
            m_pClips[index].setSpeed(speedScale * m_speed);
        } else if (i == index + 1) {
            m_pClips[i].setWeight(rate * m_weight);
            m_pClips[i].setSpeed(timeScale * speedScale * m_speed);
        } else {
            m_pClips[i].setWeight(0.0f);
            if (m_pClips[i].m_pControl != nullptr) {
                float time = Util::getPlayBackTime(*m_pClips[i].m_pControl->m_pBinding);
                float scale = time > 1.1920929e-07f ? speedScale * (fromTime / time) : 0.0f;
                m_pClips[i].setSpeed(scale * m_speed);
            }
        }
    }
}

void SpeedLerpBlendTree::setLocalTime(float time) {
    m_pClips[0].setLocalTime(time);
    if (m_pClips[0].m_pControl == nullptr) {
        return;
    }
    float baseTime = Util::getPlayBackTime(*m_pClips[0].m_pControl->m_pBinding);
    for (unsigned int i = 1; i < m_clipCount; i++) {
        if (m_pClips[i].m_pControl != nullptr) {
            float clipTime = Util::getPlayBackTime(*m_pClips[i].m_pControl->m_pBinding);
            float scale = baseTime > 1.1920929e-07f ? clipTime / baseTime : 0.0f;
            m_pClips[i].setLocalTime(scale * time);
        }
    }
}

float SpeedLerpBlendTree::getLocalTime() const {
    return m_pClips[0].getLocalTime();
}

void SpeedLerpBlendTree::onSetSpeed() {
    adjustSpeesAndWeight();
}

void SpeedLerpBlendTree::onSetWeight() {
    adjustSpeesAndWeight();
}

AsmClip* SpeedLerpBlendTree::getBaseClip() const {
    return m_pClips;
}

}  // namespace anm
