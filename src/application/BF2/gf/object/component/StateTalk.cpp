#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/npc/StateApproachPc.h"
#include "classes/gf/npc/StateIdle.h"
#include "classes/gf/npc/StateTalk.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/GfSetupPfTalk.h"
#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/npc/StateApproachPc.h"
#include "classes/gf/npc/StateIdle.h"
#include "classes/gf/npc/StateTalk.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComCollider.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/ColiObject.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/GfExecSchedule.h"
#include "gf/GfObjAcc.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfSetupPfTalk.h"
#include "fw/Transform.h"
#include "fw/UpdateInfo.h"
#include "mm/Mat44.h"
#include "plugin/Bdat.h"
#include <math.h>
#include <string.h>

namespace gf {
namespace npc {

void StateApproachPc::enter(GfComBehaviorNpc* owner, ai::State*) {
    owner->validateLocalSteer(static_cast<STATE_ID>(m_stateID));
    m_seq = &StateApproachPc::seqTurnPc;
}

void StateApproachPc::seqTurnPc(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        owner.execTurnCmdToPos(gmk::getPlayerPos());
        m_seq = &StateApproachPc::seqWaitTurnEnd;
    }
}

void StateApproachPc::leave(GfComBehaviorNpc* owner, ai::State* next) {
    if (next != nullptr) {
        owner->validateLocalSteer(static_cast<STATE_ID>(next->m_stateID));
    }
    m_seq = nullptr;
}

void StateApproachPc::update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateIdle::update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

StateTalk::StateTalk() : m_seq(nullptr), m_fromIdle(false) {}

inline void StateTalk::update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateTalk::seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (owner.m_turnEnded) {
        requestState(0);
    }
}

StateTalk::~StateTalk() {}

const char* StateTalk::getName() const { return "StateTalk"; }

void StateTalk::onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorNpc*>(owner), prev); }

void StateTalk::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorNpc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace npc
}  // namespace gf
