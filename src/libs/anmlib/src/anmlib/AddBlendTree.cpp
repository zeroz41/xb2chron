#include "classes/anm/AddBlendTree.h"

#include "classes/anm/ResASM.h"
#include "algorithm"
#include "anm/AsmBlender.h"
#include "anm/AsmListener.h"
#include "anm/AsmVariable.h"
#include "anm/Util.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"
#include <new>

namespace anm {

AddBlendTree::AddBlendTree(const ResStateData* pRes, const ResAddTree* pTree, mm::mtl::Vector<Variable>& variables,
                           mm::mtl::IAllocator& allocator)
    : AsmState(pRes, allocator), m_pTree(pTree) {
    m_clipCount = pRes->m_clips.size();
    m_pClips = static_cast<AsmClip*>(allocator.allocate(sizeof(AsmClip) * m_clipCount, 8));
    for (unsigned int i = 0; i < m_clipCount; i++) {
        AsmClip* pClip = new (&m_pClips[i]) AsmClip();
        pClip->createControl(pRes->m_clips[i], allocator);
    }
    m_pVariables = &variables;
}

AddBlendTree::~AddBlendTree() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].destroyControl();
        m_pClips[i].~AsmClip();
    }
    m_pAllocator->deallocate(m_pClips);
    m_pClips = nullptr;
    m_clipCount = 0;
}

void AddBlendTree::attach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->addClip(m_pClips[i]);
    }
}

void AddBlendTree::dettach(AsmBlender* blender) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        blender->removeClip(m_pClips[i]);
    }
}

void AddBlendTree::onEnter(AsmListener* listener) {
    initLoopCount();
    m_speed = 1.0f;
    onSetSpeed();
    notifyEnter(listener);
}

void AsmState::initLoopCount() {
    const ResState* pInfo = m_pRes->m_pInfo;
    const Binding* pBinding = m_pRes->m_clips[0].m_pBinding;
    m_loop = 0;
    const ResLoopCount* pLoopCount = pInfo->m_pLoopCount;
    if (pLoopCount != nullptr) {
        m_loopCount = pLoopCount->m_min + static_cast<unsigned int>(pLoopCount->m_range * rand());
    } else if (pBinding != nullptr && Util::getPlayMode(*pBinding) == PLAY_MODE_ONCE) {
        m_loopCount = 1;
    } else {
        m_loopCount = 0;
    }
}

void AsmState::notifyEnter(AsmListener* listener) {
    for (int kind = 0; kind < 5; kind++) {
        if (listener != nullptr && m_pRes->m_enterAnnotations[kind].size() != 0) {
            CallBackDetector::execute(*listener, AsmListener::CALLBACK_ENTER, m_pRes->m_enterAnnotations[kind]);
        }
        const mm::mtl::Vector<ResClipData>& clips = m_pRes->m_clips;
        for (unsigned int i = 0; i < clips.size(); i++) {
            const ResClipData& clip = clips[i];
            if (listener != nullptr && clip.m_frameAnnotations[kind].size() != 0) {
                CallBackDetector::executeStartFrame(*listener, clip.m_start, clip.m_frameAnnotations[kind]);
            }
        }
    }
}

void AddBlendTree::onLeave(AsmListener* listener) {
    notifyLeave(listener);
}

void AsmState::notifyLeave(AsmListener* listener) {
    if (listener == nullptr) {
        return;
    }
    for (int kind = 0; kind < 5; kind++) {
        if (m_pRes->m_leaveAnnotations[kind].size() != 0) {
            CallBackDetector::execute(*listener, AsmListener::CALLBACK_LEAVE, m_pRes->m_leaveAnnotations[kind]);
        }
    }
}

void AddBlendTree::update(float dt, AsmListener* listener) {
    adjustWeight();
    countLoop(m_pClips[0].update(dt, listener));
    for (unsigned int i = 1; i < m_clipCount; i++) {
        m_pClips[i].update(dt, nullptr);
    }
}

void AddBlendTree::adjustWeight() {
    unsigned int baseCount = m_pTree->m_baseCount;
    for (unsigned int i = 0; i < baseCount; i++) {
        m_pClips[i].setWeight(m_weight);
    }
    for (unsigned int i = 0; i < m_pTree->m_nodes.size(); i++) {
        const ResAddNode& node = m_pTree->m_nodes[i];
        float value;
        (*m_pVariables)[node.m_variableIndex].getValue(&value);
        m_pClips[baseCount + i].setWeight(value * m_weight);
    }
}

void AddBlendTree::setLocalTime(float time) {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].setLocalTime(time);
    }
}

float AddBlendTree::getLocalTime() const {
    return m_pClips[0].getLocalTime();
}

void AddBlendTree::onSetSpeed() {
    for (unsigned int i = 0; i < m_clipCount; i++) {
        m_pClips[i].setSpeed(m_speed);
    }
}

void AddBlendTree::onSetWeight() {
    adjustWeight();
}

AsmClip* AddBlendTree::getBaseClip() const {
    return m_pClips;
}

}  // namespace anm
