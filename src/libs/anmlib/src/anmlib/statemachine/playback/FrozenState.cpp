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

FrozenState::FrozenState(const ResStateData* pRes, mm::mtl::IAllocator& allocator) : AsmState(pRes, allocator) {
    m_clip.createControl(pRes->m_clips[0], allocator);
}

FrozenState::~FrozenState() {
    m_clip.destroyControl();
}

void FrozenState::attach(AsmBlender* blender) {
    blender->addClip(m_clip);
}

void FrozenState::dettach(AsmBlender* blender) {
    blender->removeClip(m_clip);
}

void FrozenState::onEnter(AsmListener* listener) {
    m_clip.setLocalTime(m_pRes->m_clips[0].m_start);
    m_clip.setSpeed(0.0f);
    notifyEnter(listener);
}

void FrozenState::onLeave(AsmListener* listener) {
    notifyLeave(listener);
}

void FrozenState::update(float, AsmListener*) {}

float FrozenState::getLocalTime() const {
    return m_clip.getLocalTime();
}

void FrozenState::onSetWeight() {
    m_clip.setWeight(m_weight);
}

void FrozenState::setLocalTime(float) {}

void FrozenState::onSetSpeed() {}

AsmClip* FrozenState::getBaseClip() const {
    return const_cast<AsmClip*>(&m_clip);
}

}  // namespace anm
