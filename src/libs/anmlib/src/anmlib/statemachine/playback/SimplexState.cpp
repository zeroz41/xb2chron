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

SimplexState::SimplexState(const ResStateData* pRes, mm::mtl::IAllocator& allocator) : AsmState(pRes, allocator) {
    m_clip.createControl(pRes->m_clips[0], allocator);
}

SimplexState::~SimplexState() {
    m_clip.destroyControl();
}

void SimplexState::attach(AsmBlender* blender) {
    blender->addClip(m_clip);
}

void SimplexState::dettach(AsmBlender* blender) {
    blender->removeClip(m_clip);
}

void SimplexState::onEnter(AsmListener* listener) {
    initLoopCount();
    m_speed = 1.0f;
    onSetSpeed();
    notifyEnter(listener);
}

void SimplexState::onLeave(AsmListener* listener) {
    notifyLeave(listener);
}

void SimplexState::update(float dt, AsmListener* listener) {
    countLoop(m_clip.update(dt, listener));
}

void SimplexState::onSetSpeed() {
    m_clip.setSpeed(m_speed);
}

void SimplexState::onSetWeight() {
    m_clip.setWeight(m_weight);
}

void SimplexState::setLocalTime(float time) {
    m_clip.setLocalTime(time);
}

float SimplexState::getLocalTime() const {
    return m_clip.getLocalTime();
}

AsmClip* SimplexState::getBaseClip() const {
    return const_cast<AsmClip*>(&m_clip);
}

}  // namespace anm
