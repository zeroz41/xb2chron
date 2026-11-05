#include "classes/gf/GfStateBase.h"
#include "classes/gf/enemy/StateBattleBase.h"
#include "classes/gf/enemy/StateBattleActionBase.h"
#include "classes/gf/enemy/StateBattle.h"
#include "classes/gf/enemy/StateFieldHome.h"
#include "classes/gf/enemy/StateFieldSquadMember.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/enemy/StateFieldWalk.h"
#include "classes/gf/enemy/StateFieldAreaWalk.h"
#include "classes/gf/enemy/StateFieldBlade.h"
#include "classes/gf/enemy/StateFieldSpawn.h"
#include "classes/gf/GfObj.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gmk/GmkRouteNavi.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "fw/Transform.h"
#include "gf/GfObjAcc.h"
#include "gf/GfFieldPitchRollController.h"
#include <string.h>

namespace gf {
namespace enemy {

// the command each route point action (StateFieldWalk::pad_90) plays there, none for 0, 1 and 6 (lbl_7100B65D78;
// the name is not the original's)
__attribute__((used)) static const char* s_routePointCmdNames[7] = {nullptr, nullptr, "C_uniqueA", "C_uniqueB", "C_specialA_00", "C_specialB_00", nullptr};

void StateFieldWalk::seqIdleInfinit(GfComBehaviorEnemy&, const fw::UpdateInfo& info) { m_execCmd.update(info.m_deltaTime); }

void StateFieldWalk::seqInitGoalPos(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (gmk::GmkRouteNavi* navi = owner.m_field.getGmkRouteNavi()) {
        const mm::Vec3& pos = owner.getTransform().position;
        validateGmkRouteNaviConsideringGfLocalSteer(*navi, owner.m_field.m_localSteer, pos);
        gmk::GmkRouteNavi::UpdateInfo naviInfo;
        naviInfo.m_pos.x = pos.x;
        naviInfo.m_pos.y = pos.y;
        naviInfo.m_pos.z = pos.z;
        navi->update(naviInfo);
        owner.m_field.m_goalPos = navi->pad_90;
    }
    if (owner.m_field.isArrivedToGoal()) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateFieldWalk::seqUpdateMove;
    } else {
        owner.execTurnCmdToGoal();
        m_seq = &StateFieldWalk::seqWaitTurnEnd;
    }
}

void StateFieldWalk::leave(GfComBehaviorEnemy* owner, ai::State*) { owner->pad_54e1 = false; }

void StateFieldWalk::pollToShiftLandingSeq(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.m_owner->getComponent<GfComAsm>(2) == nullptr || !owner.isFly()) {
        return;
    }
    gmk::GmkRouteNavi* navi = owner.m_field.getGmkRouteNavi();
    if (navi == nullptr || pad_90 != 6 || navi->m_acc.m_gmk == nullptr) {
        return;
    }
    mm::Vec3 pointPos;
    if (!static_cast<gmk::GmkRoute*>(navi->m_acc.m_gmk)->getRoutePointPos(pointPos, pad_84)) {
        return;
    }
    owner.m_field.m_goalPos = pointPos;
    if (navi->isArrived(pointPos, owner.getTransform().position)) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_idle"));
        m_seq = &StateFieldWalk::seqWaitToIdle;
        owner.pad_54e1 = true;
    }
}

void StateFieldWalk::seqWaitToIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_specialA_00"));
        m_seq = &StateFieldWalk::seqMoveToBeginLanding;
        owner.m_field.m_pitchRoll.pad_30 = true;
        owner.m_field.m_moveSpeed.setSpeedKmph(owner.m_field.m_moveSpeed.m_speedMin, 0.0f);
    }
}

void StateFieldWalk::seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateFieldWalk::seqUpdateMove;
        owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(0),
                                          static_cast<GfBehaviorEnemyField::MoveSpeed>((m_stateID & ~1u) == 10 ? 2 : 1),
                                          owner);
    }
}

void StateFieldWalk::seqWaitToIdleAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        if (m_hasPointRotY) {
            owner.execTurnCmdAccurately(m_pointRotY);
        }
        m_seq = &StateFieldWalk::seqWaitTurnEndAtRoutePoint;
    }
}

void StateFieldWalk::seqWaitTurnEndAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        if (pad_90 != 1 && s_routePointCmdNames[pad_90] != nullptr) {
            m_execCmd.create(
                TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, s_routePointCmdNames[pad_90]));
        }
        pad_68 = 0.0f;
        m_seq = &StateFieldWalk::seqPlayMotAtRoutePoint;
    }
}

void StateFieldWalk::seqWaitSpecialEndAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    // actions 4 and 5 (C_specialA_00, C_specialB_00) move the enemy by the motion
    auto isSpecial = [this]() { return pad_90 == 4 || pad_90 == 5; };
    if (isSpecial()) {
        owner.extractLoco();
    }
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        if (isSpecial()) {
            m_seq = &StateFieldWalk::seqWaitSyncLoco;
        } else {
            owner.execTurnCmdToGoal();
            m_seq = &StateFieldWalk::seqWaitTurnEnd;
        }
    }
}

void StateFieldWalk::seqWaitSyncLoco(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    owner.extractLoco();
    GfObjAcc acc(static_cast<GfObj*>(owner.m_owner)->m_handle);
    if (GfObj* obj = acc.getObj()) {
        if (GfComAsm* com = obj->getComponent<GfComAsm>(2)) {
            const char* name = com->getStateName(static_cast<AnimLayer>(0));
            if (name == nullptr || strcmp(name, "S_idle") != 0) {
                return;
            }
            if (gmk::GmkRouteNavi* navi = owner.m_field.getGmkRouteNavi()) {
                navi->updateNextPos();
            }
        }
    }
    owner.execTurnCmdToGoal();
    m_seq = &StateFieldWalk::seqWaitTurnEnd;
}

void StateFieldWalk::seqLandingIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    pad_68 += info.m_deltaTime;
    if (!owner.pad_54e2 && pad_68 < pad_94) {
        return;
    }
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_specialA_02"));
    m_seq = &StateFieldWalk::seqWaitTakeOffEnd;
}

bool StateFieldWalk::isCondMatch(const GfComBehaviorEnemy& owner) {
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr) {
        return false;
    }
    return static_cast<unsigned int>(gmk->getGmkType()) < 2;
}

}  // namespace enemy
}  // namespace gf
