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
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_ADD_DEVELOP.h"
#include "classes/fw/ColiObject.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/GfDataDevelop.h"
#include "gf/GfDataMap.h"
#include "gf/GfExecSchedule.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfSetupPfTalk.h"
#include "fw/Transform.h"
#include "fw/UpdateInfo.h"
#include "mm/Mat44.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/RTTI.h"
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

void StateApproachPc::seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateApproachPc::seqApproachPc;
    }
}

void StateApproachPc::seqApproachPc(GfComBehaviorNpc& owner, const fw::UpdateInfo& info) {
    if (!m_execCmd.m_done) {
        return;
    }
    if (m_execCmd.m_executed) {
        owner.init(true);
    }
    if (!gmk::isPlayerExist()) {
        return;
    }
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr) {
        return;
    }
    owner.setGoalPos(gmk::getPlayerPos());
    if (!isCondMatch(owner)) {
        requestState(1);
        return;
    }
    bool far;
    {
        GfObjAcc acc(static_cast<GfObj*>(owner.m_owner));
        const mm::Vec3& pos = acc.getWorldTransform().position;
        const mm::Vec3& playerPos = gmk::getPlayerPos();
        mm::Vec3 toPlayer = playerPos - pos;
        toPlayer.y = 0.0f;
        far = !(playerPos.y - pos.y < 1.0f && toPlayer.dot(toPlayer) < 1.0f);
    }
    if (far) {
        GfObjAcc acc(static_cast<GfObj*>(owner.m_owner));
        const mm::Vec3& npcPos = acc.getWorldTransform().position;
        mm::Vec3 gmkPos = *gmk->m_pos;
        mm::Vec3 toGmk = npcPos - gmkPos;
        float dy = toGmk.y;
        toGmk.y = 0.0f;
        float distSq = toGmk.dot(toGmk);
        if (!(GfComBehaviorNpc::BdatInfo::getDistYThreshold() < dy) &&
            !(owner.m_bdatInfo.m_approachDistSq < distSq)) {
            owner.moveToGoal(info.m_deltaTime);
            return;
        }
    }
    TFieldExecCmd<GfComAsm>::CreateInfo idle;
    idle.handle = static_cast<GfObj*>(owner.m_owner)->m_handle;
    idle.cmdName = "C_idle";
    idle.timeout = 5.0f;
    m_execCmd.create(idle);
    m_seq = &StateApproachPc::seqApproachPcIdle;
}

bool StateApproachPc::isCondMatch(const GfComBehaviorNpc& owner) {
    if (!gmk::isPlayerExist() || !(owner.m_bdatInfo.m_approachDistSq > 0.0f) ||
        GfComBehaviorNpc::BdatInfo::getDistYThreshold() * GfComBehaviorNpc::BdatInfo::getDistYThreshold() <
            owner.m_playerDistYSq ||
        owner.m_bdatInfo.m_approachDistSq < owner.m_playerDistSq) {
        return false;
    }
    return true;
}

void StateApproachPc::seqApproachPcIdle(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_executed) {
        owner.init(false);
    }
    if (!isCondMatch(owner)) {
        requestState(1);
    }
}

void StateIdle::applyInitStateName(GfComBehaviorNpc& owner) {
    GfComAsm* com = owner.getComAsm();
    const char* stateName = com != nullptr ? com->getStateName(static_cast<AnimLayer>(0)) : nullptr;
    GfObjSetupNpc* setup = nullptr;
    if (GFOBJ_INFO* info = GfObjManager::getObjInfo(static_cast<GfObj*>(owner.m_owner)->m_handle)) {
        setup = static_cast<GfObjSetupNpc*>(info->m_setup);
        if (setup != nullptr) {
            if (setup->m_type == info->m_obj->m_type && info->m_obj->m_type == 6) {
                setup = mm::mtl::rttiCast<GfObjSetupNpc>(info->m_setup);
            } else {
                setup = nullptr;
            }
        }
    }
    if (stateName != nullptr) {
        if (strstr(stateName, "S_schedule_") != nullptr) {
            mm::mtl::FixStr<32> schedule(stateName);
            if (schedule.m_str[schedule.m_nLen - 1] != '2') {
                schedule.m_str[schedule.m_nLen - 1] = setup->m_stateName.m_str[setup->m_stateName.m_nLen - 1];
                if (strcmp(schedule.m_str, setup->m_stateName.m_str) == 0) {
                    return;
                }
            }
        } else if (strcmp(stateName, setup->m_stateName.m_str) == 0) {
            return;
        }
    }
    if (m_endSchedule) {
        execEndSchedule(owner);
    }
    if (stateName == nullptr || strcmp(setup->m_stateName.m_str, stateName) != 0) {
        mm::mtl::FixStr<32> cmd(setup->m_stateName);
        cmd[0] = 'C';
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, cmd.m_str));
    }
}

inline bool StateIdle::isExecEndScheduleCondMatched(GfComBehaviorNpc& owner, ai::State* state) const {
    if (state == nullptr) {
        return false;
    }
    if (state->m_stateID == 6) {
        gmk::AGmkBase* gmk = owner.getBindedGmkInst();
        if (gmk != nullptr &&
            Bdat::getValCheckU8(gmk->getBindedBdatFp(), "NpcTurn", gmk->m_createInfo.m_bdatId) == 3) {
            return false;
        }
    }
    return true;
}

void StateIdle::enter(GfComBehaviorNpc* owner, ai::State* prev) {
    m_endSchedule = isExecEndScheduleCondMatched(*owner, prev);
    if (owner->m_turnCmd.pad_6c) {
        applyInitStateName(*owner);
        m_seq = &StateIdle::seqCheckNextState;
    } else {
        m_seq = &StateIdle::seqWaitTurnEnd;
    }
}

void StateIdle::seqCheckNextState(GfComBehaviorNpc& owner, const fw::UpdateInfo& info) {
    if (m_execCmd.m_info.handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_execCmd.m_info.cmdName.m_nLen != 0) {
        m_execCmd.update(info.m_deltaTime);
        if (!m_execCmd.m_done) {
            return;
        }
        if (m_execCmd.m_executed) {
            owner.init(false);
        }
    }
    int next = owner.getNexStateId();
    if (next != -1) {
        requestState(next);
    }
}

void StateIdle::seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        applyInitStateName(owner);
        m_seq = &StateIdle::seqCheckNextState;
    }
}

void StateIdle::leave(GfComBehaviorNpc* owner, ai::State* next) {
    if (next == nullptr || m_stateID == next->m_stateID) {
        return;
    }
    if (isExecEndScheduleCondMatched(*owner, next)) {
        execEndSchedule(*owner);
    }
}

void StateIdle::update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

StateTalk::StateTalk() : m_seq(nullptr), m_fromIdle(false) {}

void StateTalk::enter(GfComBehaviorNpc* owner, ai::State* prev) {
    if (prev != nullptr) {
        m_fromIdle = prev->m_stateID == 0;
    }
    if (GfComAsm* com = owner->getComAsm()) {
        com->execCmd("C_walkend", static_cast<AnimLayer>(0));
    }
    if (gmk::AGmkBase* gmk = owner->getBindedGmkInst()) {
        int eventId = owner->m_bdatInfo.m_talkEventId;
        GF_OBJ_HANDLE* handle = static_cast<GfObj*>(owner->m_owner)->m_handle;
        GfSetupPfTalk talk;
        talk.m_eventId = eventId;
        talk.m_handle = handle;
        talk.pad_10 = 0;
        talk.m_npcTurn = static_cast<unsigned char>(
            Bdat::getValCheck(gmk->getBindedBdatFp(), "NpcTurn", gmk->m_createInfo.m_bdatId, 1));
        if (talk.m_npcTurn == 0) {
            execEndSchedule(*owner);
        }
        GfPlayFactory::createTalk(talk);
    }
    setCollideNpcMob(false);
    owner->init(false);
    m_seq = &StateTalk::seqWaitTalkEnd;
}

void StateTalk::setCollideNpcMob(bool collide) {
    setCollideNpcMob(GfGameParty::getHandleDriver(0, PTPOS(0)), collide);
    setCollideNpcMob(GfGameParty::getHandleBlade(0, -1), collide);
    setCollideNpcMob(GfGameParty::getHandleDriver(1, PTPOS(0)), collide);
    setCollideNpcMob(GfGameParty::getHandleBlade(1, -1), collide);
    setCollideNpcMob(GfGameParty::getHandleDriver(2, PTPOS(0)), collide);
    setCollideNpcMob(GfGameParty::getHandleBlade(2, -1), collide);
}

void StateTalk::seqWaitTalkEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (owner.pad_100) {
        return;
    }
    if (owner.m_turnCmd.m_info.handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && owner.m_turnCmd.m_info.pad_c >= 0.0f &&
        owner.m_turnCmd.m_info.pad_c <= 3.14159274f && owner.m_turnCmd.m_info.pad_10 >= 0.0f &&
        owner.m_turnCmd.m_info.pad_10 <= 3.14159274f && owner.m_turnCmd.m_info.pad_14 > 0.0f &&
        !owner.m_turnCmd.pad_6c) {
        return;
    }
    if (owner.m_bdatInfo.isIconTalkBonus()) {
        owner.m_bdatInfo.setTalkBonusFlag();
        unsigned int zone = GfGameManager::getMapZoneID();
        // the talk bonus's BDAT row (sheet 0x7b) by the zone's development level (the name is not the original's)
        const unsigned int bonusRows[] = {0x46, 0x2E, 0x2F, 0x30, 0x31, 0x32};
        unsigned int level = GfDataDevelop::getLevel(zone);
        unsigned int row = bonusRows[level];
        unsigned short point = Bdat::getValCheck(GfDataBdat::getFP(0x7b), 1, row, 2);
        if (point != 0) {
            if (Bdat::getValCheckU8(GfDataBdat::getFP(0x5d), "zone", GfGameManager::getMapID()) != 0) {
                SCOM_ADD_DEVELOP::create(zone, point);
            } else {
                for (unsigned int i = 1; i <= 8; ++i) {
                    if (GfDataMap::isArcadiaDestroy() && i == 6) {
                        continue;
                    }
                    SCOM_ADD_DEVELOP::create(i, point);
                }
            }
        }
        SCOM_ACHIEV_INC::addTotalCount(0x17, 1);
        SCOM_ACHIEV_INC::create(0x17, 1, 0);
    }
    if (m_fromIdle) {
        if (gmk::AGmkBase* gmk = owner.getBindedGmkInst()) {
            mm::Mat44 mtx;
            gmk->getMatrix(mtx, true);
            owner.execTurnCmd(atan2f(mtx.m[2][0], mtx.m[2][2]), 1.0f, 0.000001f, 0.0f);
        }
        m_seq = &StateTalk::seqWaitTurnEnd;
    } else {
        requestState(0);
    }
}

inline void StateTalk::leave(GfComBehaviorNpc* owner, ai::State*) {
    setCollideNpcMob(true);
    if (m_fromIdle && &StateTalk::seqWaitTalkEnd == m_seq) {
        if (gmk::AGmkBase* gmk = owner->getBindedGmkInst()) {
            mm::Mat44 mtx;
            gmk->getMatrix(mtx, true);
            owner->execTurnCmd(atan2f(mtx.m[2][0], mtx.m[2][2]), 1.0f, 0.000001f, 0.0f);
        }
    }
}

inline void StateTalk::update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateTalk::seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        requestState(0);
    }
}

void StateTalk::setCollideNpcMob(GF_OBJ_HANDLE* handle, bool collide) {
    GfObj* obj = GfObjAcc(handle).getObj();
    if (obj == nullptr) {
        return;
    }
    const GfComCollider* collider = obj->getComponent<GfComCollider>(4);
    if (collider == nullptr) {
        return;
    }
    for (fw::ColiObject* const& coli : collider->m_coliObjects) {
        if (coli != nullptr) {
            if (collide) {
                unsigned int flag = coli->getHitMaterialFlag() | 0x40000;
                coli->setHitMaterialFlag(flag);
            } else {
                unsigned int flag = coli->getHitMaterialFlag() & ~0x40000;
                coli->setHitMaterialFlag(flag);
            }
        }
    }
}

StateTalk::~StateTalk() {}

const char* StateTalk::getName() const { return "StateTalk"; }

void StateTalk::onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorNpc*>(owner), prev); }

void StateTalk::onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorNpc*>(owner), next); }

void StateTalk::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorNpc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace npc
}  // namespace gf
