#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfArenaBattle.h"
#include "classes/gf/GfArenaParty.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/StateArenaWait.h"
#include "classes/gf/StateArenaField.h"
#include "classes/gf/StateArenaReturnBattle.h"
#include "classes/gf/StateArenaEvent.h"
#include "classes/gf/StateArenaResultBattle.h"
#include "classes/gf/GfArenaReward.h"
#include "classes/gf/GfMenuObjSalvage.h"
#include "math.h"
#include "classes/gf/StateArenaSetup.h"
#include "classes/gf/StateArenaLeave.h"
#include "classes/gf/StateArenaStartBattle.h"
#include "classes/gf/StateArenaExecBattle.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataBlade.h"
#include "gf/MapjumpCallbackInfo.h"
#include "btl/Utility.h"

namespace gf {

void StateArenaWait::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    switch (static_cast<int>(gev)) {
    case 1:
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (!arena->isActiveArena() && GfDataMap::getMapID(info.m_mapJumpId) == 0x3A) {
                MsgUnk_1000034 msg(0xB);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
        break;
    case 6:
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (arena->isActiveArena()) {
                m_arenaFlagSeen = true;
            }
        }
        break;
    }
}

void StateArenaSetup::enter(GfGameArena* arena, ai::State*) {
    arena->createMapSound();
}

void StateArenaSetup::leave(GfGameArena*, ai::State*) {}

void StateArenaSetup::update(GfGameArena*, fw::UpdateInfo const&) {
    requestState(3);
}

void StateArenaLeave::enter(GfGameArena* arena, ai::State*) {
    arena->m_partySetup->removeFieldBlade();
    arena->destroyMapSound();
}

void StateArenaLeave::leave(GfGameArena*, ai::State*) {}

void StateArenaLeave::update(GfGameArena*, fw::UpdateInfo const&) {
    requestState(9);
}

void StateArenaField::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    if (gev == 1) {
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (arena->isActiveArena() && GfDataMap::getMapID(info.m_mapJumpId) != 0x3A) {
                MsgUnk_1000034 msg(0xA);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
    }
}

void StateArenaStartBattle::enter(GfGameArena*, ai::State*) {}

void StateArenaStartBattle::leave(GfGameArena*, ai::State*) {}

void StateArenaStartBattle::update(GfGameArena* arena, fw::UpdateInfo const&) {
    if (arena->m_partySetup->fn_710028E4E8(arena->m_msgObj->m_key)) {
        GfMenuManager::loadBchUI();
        arena->m_msgObj->mapjumpForBattleStart();
        requestState(5);
    } else {
        requestState(3);
    }
}

void StateArenaExecBattle::enter(GfGameArena*, ai::State*) {
    btl::Utility::StartChallengeBattleCallback();
}

void StateArenaExecBattle::leave(GfGameArena*, ai::State*) {}

void StateArenaExecBattle::update(GfGameArena* arena, fw::UpdateInfo const& info) {
    arena->m_msgObj->execBattleSequence(info);
    requestState(7);
}

void StateArenaReturnBattle::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&) {
    if (gev == 4) {
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            arena->m_msgObj->mapjumpForReturnFieldForObjCleanup();
        }
    }
}

void StateArenaResultBattle::enter(GfGameArena* arena, ai::State*) {
    arena->m_helper->listUpTBox();
    m_step = &StateArenaResultBattle::updateStart;
    m_context = GfMenuCallContext::create();
}

void StateArenaResultBattle::updateStart(GfGameArena* arena, fw::UpdateInfo const&) {
    if (arena->m_msgObj->m_result == 2 || arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score)) {
        m_step = &StateArenaResultBattle::updateCamera;
    } else {
        m_step = &StateArenaResultBattle::updateFadeWait;
    }
}

void StateArenaResultBattle::leave(GfGameArena*, ai::State*) {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void StateArenaResultBattle::update(GfGameArena* arena, fw::UpdateInfo const& info) {
    if (m_step) {
        (this->*m_step)(arena, info);
    }
}

void StateArenaResultBattle::updateCamera(GfGameArena* arena, fw::UpdateInfo const&) {
    mm::Mat44 mtx;
    if (arena->m_helper->getActionOrigin(mtx)) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
        arena->m_helper->createCameraCut01(pos, rotY);
    }
    arena->m_helper->playCameraCut01();
    m_timer = 0.5f;
    m_step = &StateArenaResultBattle::updateCameraWait;
}

void StateArenaResultBattle::updateFadeWait(GfGameArena* arena, fw::UpdateInfo const&) {
    if (!GfGameManager::isFading(static_cast<unsigned int>(-1))) {
            bool clear = arena->m_msgObj->m_result == 2 || arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score);
        if (clear) {
            arena->m_helper->playReturnVoice(arena->m_msgObj->m_result == 2);
            m_step = &StateArenaResultBattle::updateResult;
        } else {
            arena->m_helper->playReturnVoice(false);
            m_step = &StateArenaResultBattle::updateFinish;
        }
    }
}

void StateArenaResultBattle::updateResult(GfGameArena*, fw::UpdateInfo const&) {
    m_context->reset();
    GfMenuObjSalvage::openBtlchRecord(m_context);
    m_step = &StateArenaResultBattle::updateResultWait;
}

void StateArenaResultBattle::updateFinish(GfGameArena* arena, fw::UpdateInfo const&) {
    arena->m_helper->destroyCameraCut01();
    requestState(3);
    m_step = nullptr;
}

void StateArenaResultBattle::updateResultWait(GfGameArena*, fw::UpdateInfo const&) {
    if (m_context->isTerm()) {
        m_step = &StateArenaResultBattle::updateTBox;
    }
}

void StateArenaResultBattle::updateTBox(GfGameArena* arena, fw::UpdateInfo const&) {
    if (arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score)) {
        arena->m_helper->fn_710028E69C(arena->m_msgObj->m_score);
    } else {
        arena->m_helper->fn_710028E878(arena->m_msgObj->m_score);
    }
    m_timer = 0.5f;
    m_step = &StateArenaResultBattle::updateTBoxWait;
}

void StateArenaResultBattle::updateCameraWait(GfGameArena*, fw::UpdateInfo const& info) {
    m_timer -= info.m_frameTime;
    if (m_timer < 0.0f) {
        m_step = &StateArenaResultBattle::updateFadeWait;
    }
}

void StateArenaResultBattle::updateTBoxWait(GfGameArena*, fw::UpdateInfo const& info) {
    m_timer -= info.m_deltaTime;
    if (m_timer < 0.0f) {
        m_step = &StateArenaResultBattle::updateUI;
    }
}

void StateArenaResultBattle::updateUI(GfGameArena* arena, fw::UpdateInfo const&) {
    m_context->reset();
    GfMenuObjSalvage::ResultParam param;
    param.m_unk2 = 1;
    GfMenuObjSalvage::openResult(m_context, param);
    arena->m_helper->fn_710028EF70(arena->m_msgObj->m_score);
    m_step = &StateArenaResultBattle::updateUIWait;
}

void StateArenaResultBattle::updateUIWait(GfGameArena* arena, fw::UpdateInfo const&) {
    if (m_context->isTerm()) {
        arena->m_helper->destroyCameraCut01();
        m_timer = 0.0f;
        m_step = &StateArenaResultBattle::updateReturnCamera;
    }
}

void StateArenaResultBattle::updateReturnCamera(GfGameArena* arena, fw::UpdateInfo const& info) {
    m_timer += info.m_deltaTime;
    if (m_timer > 1.0f) {
            arena->m_helper->fn_710028F0A4(arena->m_msgObj->m_score);
        m_step = &StateArenaResultBattle::updateFinish;
    }
}

void StateArenaEvent::gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) {}

void StateArenaEvent::gevPlayEvent(gf::GEV gev, unsigned int) {
    switch (static_cast<int>(gev)) {
    case 0xC: m_playState = 1; break;
    case 0xD: m_playState = 3; break;
    case 0xE: m_playState = 2; break;
    default: break;
    }
}

void GfGameManager::BattleChallengeRecord::Rule::fn_71002904DC(BattleChallengeRecord* record, unsigned int value) {
    if (m_value4 < value) {
        m_value4 = value;
    }
    record->m_value28 = value;
}

void GfGameManager::BattleChallengeRecord::Rule::fn_71002904F4(BattleChallengeRecord* record, unsigned int value) {
    if (m_value0 == 0 || value < m_value0) {
        m_value0 = value;
    }
    record->m_value30 = value;
}

}  // namespace gf
