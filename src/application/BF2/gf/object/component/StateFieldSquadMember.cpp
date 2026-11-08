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
#include "classes/gf/GfComPropertyEnemy.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/enemy/StateFieldIdle.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "gf/GfObjAcc.h"
#include "classes/fw/Camera.h"
#include "btl/siren_battle_manager.h"
#include "ml/MtRand.h"
#include "math.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "gf/GfObjInfo.h"
#include <string.h>

namespace gf {
namespace enemy {

// the command enter starts by the state's ID, unless the previous state was 4 or 5 (lbl_7100B65C88; the name is not
// the original's)
static StateFieldIdle::StateName s_idleCmdNames[5] = {
    {1, "C_idle"}, {2, "C_uniqueA"}, {3, "C_uniqueB"}, {4, "C_specialA_00"}, {5, "C_specialB_00"}};
// the actMove column (BDAT 0x6e) enter reads the idle time from by the state's ID (lbl_7100B65CD8; the name is not
// the original's)
static StateFieldIdle::StateName s_idleTimeColumns[5] = {
    {1, "IDL_Time"}, {2, nullptr}, {3, nullptr}, {4, "ExIDL1_Time"}, {5, "ExIDL2_Time"}};

void StateFieldIdle::enter(GfComBehaviorEnemy* owner, ai::State* prev) {
    owner->m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(1), *owner);
    GfComAsm* asmCom = owner->m_owner->getComponent<GfComAsm>(2);
    if (asmCom != nullptr) {
        asmCom->execCmd("C_walkend", AnimLayer(0));
    }
    unsigned int id = m_stateID;
    mm::mtl::FixStr<32> cmdName;
    if (prev != nullptr) {
        bool special = prev->m_stateID == 4 || prev->m_stateID == 5;
        cmdName.clear();
        if (!special) {
            for (int i = 0; i < 5; i++) {
                if (s_idleCmdNames[i].m_stateId == id) {
                    cmdName = s_idleCmdNames[i].m_name;
                    break;
                }
            }
        }
    } else if (asmCom != nullptr && asmCom->getStateName(AnimLayer(0)) != nullptr) {
        // the state's command: its name with S_ turned into C_
        cmdName = asmCom->getStateName(AnimLayer(0));
        cmdName.m_str[0] = 'C';
    } else {
        cmdName = "C_idle";
    }
    GfObjSetupEnemy* setup = nullptr;
    GFOBJ_INFO* info = GfObjManager::getObjInfo(static_cast<GfObj*>(owner->m_owner)->m_handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        setup = mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    if (static_cast<int>(setup->m_actMoveId) > 0) {
        pad_5c = -1.0f;
        unsigned char* fp = GfDataBdat::getFP(0x6e);
        int actMoveId = setup->m_actMoveId;
        for (int i = 0; i < 5; i++) {
            if (s_idleTimeColumns[i].m_stateId == id) {
                if (s_idleTimeColumns[i].m_name != nullptr) {
                    pad_5c = Bdat::getValCheckU8(fp, s_idleTimeColumns[i].m_name, actMoveId);
                }
                break;
            }
        }
    } else {
        pad_5c = 0.0f;
    }
    if (cmdName.length() != 0) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, cmdName.m_str));
    }
    owner->m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(0), *owner);
    pad_58 = 0.0f;
    bool isFlyInsect = owner->isFlyInsect();
    pad_18 = isFlyInsect ? 2 : 1;
    m_seq = (id == 1 && isFlyInsect) ? &StateFieldIdle::seqFlyInsectIdle : &StateFieldIdle::seqOthersIdle;
}

void StateFieldIdle::seqFlyInsectIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    if (m_execCmd.m_executed) {
        mm::Vec3 goal = owner.getTransform().position;
        GfObjSetupEnemy* setup =
            mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(owner.m_owner)->m_handle)->m_setup);
        goal.y = setup->m_initialPos.y + ml::mtRandf1(-1.0f, 1.0f) * 3.0f;
        owner.m_field.m_goalPos = goal;
    }
    if (m_execCmd.m_done) {
        float dt = info.m_deltaTime;
        owner.m_field.moveToGoal(dt);
    }
    if (owner.m_field.isArrivedToGoal()) {
        pad_58 = pad_5c;
    }
}

void StateFieldIdle::seqOthersIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_executed) {
        owner.m_field.m_goalPos = owner.getTransform().position;
    }
}

void StateFieldIdle::leave(GfComBehaviorEnemy* owner, ai::State* next) {
    GfComAsm* asmCom = owner->m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    switch (m_stateID) {
    case 4:
        asmCom->execCmd("C_specialA_02", AnimLayer(0));
        break;
    case 5:
        asmCom->execCmd("C_specialB_02", AnimLayer(0));
        break;
    }
}

void StateFieldIdle::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_info.handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_execCmd.m_info.cmdName.length() != 0 &&
        !m_execCmd.m_done) {
        return;
    }
    if (m_execCmd.m_executed && pad_5c < 0.0f) {
        if (GfComAsm* asmCom = owner->m_owner->getComponent<GfComAsm>(2)) {
            if (const char* name = asmCom->getStateName(AnimLayer(0))) {
                asmCom->getPlaybackTime(name, &pad_5c);
            }
        }
    }
    pad_58 += info.m_deltaTime;
    if ((pad_5c != 0.0f && pad_5c <= pad_58) || (owner->pad_54e2 && m_stateID != 1)) {
        if (owner->isStateCondMatch(static_cast<STATE_ID>(14))) {
            requestState(14);
        } else {
            GfObjSetupEnemy* setup = mm::mtl::rttiCast<GfObjSetupEnemy>(
                GfObjManager::getObjInfo(static_cast<GfObj*>(owner->m_owner)->m_handle)->m_setup);
            if (!setup->pad_b2) {
                STATE_ID next = owner->getNextFieldStateId();
                if (owner->isStateCondMatch(next)) {
                    requestState(next);
                }
            }
        }
    }
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateFieldSpawn::enter(GfComBehaviorEnemy* owner, ai::State*) { owner->disposeMenuObj(); }

void StateFieldSpawn::leave(GfComBehaviorEnemy* owner, ai::State*) { owner->createMenuObj(); }

void StateFieldSpawn::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo&) {
    bool isIdle = true;
    if (GfComAsm* asmCom = owner->m_owner->getComponent<GfComAsm>(2)) {
        if (const char* name = asmCom->getStateName(AnimLayer(0))) {
            isIdle = strcmp(name, "S_idle") == 0;
        }
    }
    if (btl::SirenBattleManager::sys()->pad_1cb &&
        mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(owner->m_owner)->m_handle)->m_setup)
            ->pad_b1) {
        const char* name;
        float time;
        if (!isIdle) {
            GfComAsm* asmCom = owner->m_owner->getComponent<GfComAsm>(2);
            if (asmCom == nullptr) {
                return;
            }
            name = asmCom->getStateName(AnimLayer(0));
            time = asmCom->getLocalTime(AnimLayer(0));
            if (!(time >= 0.0f)) {
                return;
            }
        } else {
            if (pad_18) {
                return;
            }
            pad_18 = true;
            time = 3.40282347e+38f;
            name = nullptr;
        }
        GfObjAcc acc(static_cast<GfObj*>(owner->m_owner)->m_handle);
        unsigned int bdatId = acc.getBdatId();
        btl::SirenBattleManager::sys()->NotifySpawnAnimation(bdatId, time, name);
        return;
    }
    if (!isIdle) {
        return;
    }
    if (owner->pad_550d) {
        requestState(owner->getNextFieldStateId());
    } else {
        requestState(1);
    }
}

StateFieldSquadMember::StateFieldSquadMember() : m_seq(nullptr), pad_60(false), pad_64(0) {}

void StateFieldSquadMember::seqUpdateIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        mm::Vec3 pos;
        float rotY;
        if (owner.m_field.m_squadNavi.getPosRotY(pos, rotY)) {
            owner.execTurnCmd(rotY);
            m_seq = &StateFieldSquadMember::seqWaitTurnEnd;
        }
    }
}

void StateFieldSquadMember::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    pad_60 = pad_64 < 0.1f;
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
    gmk::GmkSquadNavi& navi = owner->m_field.m_squadNavi;
    if (!navi.isInSquad()) {
        return;
    }
    if (navi.m_index == 0) {
        requestState(1);
        return;
    }
    gmk::GmkSquadNavi::UpdateInfo naviInfo;
    naviInfo.m_pos = owner->getTransform().position;
    navi.update(naviInfo);
    mm::Vec3 pos;
    float rotY;
    if (!navi.getPosRotY(pos, rotY)) {
        return;
    }
    owner->m_field.m_goalPos = pos;
    const mm::Vec3& cur = owner->getTransform().position;
    float dx = pos.x - cur.x;
    float dz = pos.z - cur.z;
    pad_64 = sqrtf(dx * dx + dz * dz);
    if (!pad_60) {
        owner->m_field.applyFieldMoveSpeed(
            static_cast<GfBehaviorEnemyField::MoveSpeed>(pad_64 < 0.5f ? 0 : (pad_64 < 1.0f ? 1 : 2)), *owner);
    }
}

void StateFieldSquadMember::seqWaitTurnEnd(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        if (pad_60) {
            owner.m_field.applyFieldMoveSpeed(static_cast<GfBehaviorEnemyField::MoveSpeed>(0), owner);
        }
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle,
                                                             pad_60 ? "C_idle" : "C_move"));
        m_seq = pad_60 ? &StateFieldSquadMember::seqUpdateIdle : &StateFieldSquadMember::seqUpdateMove;
    }
}

void StateFieldSquadMember::seqUpdateMove(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (!m_execCmd.m_done) {
        return;
    }
    if (pad_60) {
        mm::Vec3 pos;
        float rotY;
        if (owner.m_field.m_squadNavi.getPosRotY(pos, rotY)) {
            owner.execTurnCmd(rotY);
            m_seq = &StateFieldSquadMember::seqWaitTurnEnd;
            return;
        }
    }
    owner.execTurnCmdToGoal();
    if (owner.m_turnCmd.pad_6c) {
        owner.m_field.moveToGoal(info.m_deltaTime);
    } else {
        m_seq = &StateFieldSquadMember::seqWaitTurnEnd;
    }
}

StateFieldSquadMember::~StateFieldSquadMember() {}

const char* StateFieldSquadMember::getName() const { return "StateFieldSquadMember"; }

void StateFieldSquadMember::onEnter(void* owner, ai::State*) {
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(
        static_cast<GfObj*>(static_cast<GfComBehaviorEnemy*>(owner)->m_owner)->m_handle, "C_idle"));
    m_seq = &StateFieldSquadMember::seqUpdateIdle;
}

void StateFieldSquadMember::onLeave(void*, ai::State*) {}

void StateFieldSquadMember::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace enemy
}  // namespace gf
