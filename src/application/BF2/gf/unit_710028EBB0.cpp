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
            if (!arena->fn_7100291DB4() && GfDataMap::getMapID(info.m_mapJumpId) == 0x3A) {
                MsgUnk_1000034 msg(0xB);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
        break;
    case 6:
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (arena->fn_7100291DB4()) {
                m_arenaFlagSeen = true;
            }
        }
        break;
    }
}

void StateArenaSetup::fn_710028F3F0(void* owner, ai::State*) {
    static_cast<GfGameArena*>(owner)->createMapSound();
}

void StateArenaSetup::fn_710028F3F8(void*, ai::State*) {}

void StateArenaSetup::fn_710028F3FC(void*, void const*) {
    requestState(3);
}

void StateArenaLeave::fn_710028F444(void* owner, ai::State*) {
    GfGameArena* arena = static_cast<GfGameArena*>(owner);
    arena->m_partySetup->removeFieldBlade();
    arena->destroyMapSound();
}

void StateArenaLeave::fn_710028F46C(void*, ai::State*) {}

void StateArenaLeave::fn_710028F470(void*, void const*) {
    requestState(9);
}

void StateArenaField::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    if (gev == 1) {
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (arena->fn_7100291DB4() && GfDataMap::getMapID(info.m_mapJumpId) != 0x3A) {
                MsgUnk_1000034 msg(0xA);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
    }
}

void StateArenaStartBattle::fn_710028F5F8(void*, ai::State*) {}

void StateArenaStartBattle::fn_710028F5FC(void*, ai::State*) {}

void StateArenaStartBattle::fn_710028F600(void* owner, void const*) {
    GfGameArena* arena = static_cast<GfGameArena*>(owner);
    if (arena->m_partySetup->fn_710028E4E8(arena->m_msgObj->m_key)) {
        GfMenuManager::loadBchUI();
        arena->m_msgObj->mapjumpForBattleStart();
        requestState(5);
    } else {
        requestState(3);
    }
}

void StateArenaExecBattle::fn_710028F694(void*, ai::State*) {
    btl::Utility::StartChallengeBattleCallback();
}

void StateArenaExecBattle::fn_710028F698(void*, ai::State*) {}

void StateArenaExecBattle::fn_710028F69C(void* owner, void const* arg) {
    static_cast<GfGameArena*>(owner)->m_msgObj->fn_710028CFF8(arg);
    requestState(7);
}

void StateArenaReturnBattle::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&) {
    if (gev == 4) {
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            arena->m_msgObj->mapjumpForReturnFieldForObjCleanup();
        }
    }
}

void StateArenaResultBattle::fn_710028F738(void* owner, ai::State*) {
    static_cast<GfGameArena*>(owner)->m_helper->listUpTBox();
    m_step = &StateArenaResultBattle::fn_710028F770;
    m_context = GfMenuCallContext::create();
}

void StateArenaResultBattle::fn_710028F770(void* owner, void const*) {
    GfGameArena* arena = static_cast<GfGameArena*>(owner);
    if (arena->m_msgObj->m_result == 2 || arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score)) {
        m_step = &StateArenaResultBattle::fn_710028F858;
    } else {
        m_step = &StateArenaResultBattle::fn_710028F8D8;
    }
}

void StateArenaResultBattle::fn_710028F7C4(void*, ai::State*) {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void StateArenaResultBattle::fn_710028F830(void* owner, void const* arg) {
    if (m_step) {
        (this->*m_step)(owner, arg);
    }
}

void StateArenaResultBattle::fn_710028F858(void* owner, void const*) {
    GfGameArena* arena = static_cast<GfGameArena*>(owner);
    mm::Mat44 mtx;
    if (arena->m_helper->getActionOrigin(mtx)) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
        arena->m_helper->createCameraCut01(pos, rotY);
    }
    arena->m_helper->playCameraCut01();
    m_timer = 0.5f;
    m_step = &StateArenaResultBattle::fn_710028FA80;
}

void StateArenaResultBattle::fn_710028F8D8(void* owner, void const*) {
    if (!GfGameManager::isFading(static_cast<unsigned int>(-1))) {
        GfGameArena* arena = static_cast<GfGameArena*>(owner);
        bool clear = arena->m_msgObj->m_result == 2 || arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score);
        if (clear) {
            arena->m_helper->playReturnVoice(arena->m_msgObj->m_result == 2);
            m_step = &StateArenaResultBattle::fn_710028F964;
        } else {
            arena->m_helper->playReturnVoice(false);
            m_step = &StateArenaResultBattle::fn_710028F99C;
        }
    }
}

void StateArenaResultBattle::fn_710028F964(void*, void const*) {
    m_context->reset();
    GfMenuObjSalvage::openBtlchRecord(m_context);
    m_step = &StateArenaResultBattle::fn_710028F9F0;
}

void StateArenaResultBattle::fn_710028F99C(void* owner, void const*) {
    static_cast<GfGameArena*>(owner)->m_helper->destroyCameraCut01();
    requestState(3);
    m_step = nullptr;
}

void StateArenaResultBattle::fn_710028F9F0(void*, void const*) {
    if (m_context->isTerm()) {
        m_step = &StateArenaResultBattle::fn_710028FA24;
    }
}

void StateArenaResultBattle::fn_710028FA24(void* owner, void const*) {
    GfGameArena* arena = static_cast<GfGameArena*>(owner);
    if (arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score)) {
        arena->m_helper->fn_710028E69C(arena->m_msgObj->m_score);
    } else {
        arena->m_helper->fn_710028E878(arena->m_msgObj->m_score);
    }
    m_timer = 0.5f;
    m_step = &StateArenaResultBattle::fn_710028FAA8;
}

void StateArenaResultBattle::fn_710028FA80(void*, void const* arg) {
    m_timer -= static_cast<const float*>(arg)[0];
    if (m_timer < 0.0f) {
        m_step = &StateArenaResultBattle::fn_710028F8D8;
    }
}

void StateArenaResultBattle::fn_710028FAA8(void*, void const* arg) {
    m_timer -= static_cast<const float*>(arg)[1];
    if (m_timer < 0.0f) {
        m_step = &StateArenaResultBattle::fn_710028FAD0;
    }
}

void StateArenaResultBattle::fn_710028FAD0(void* owner, void const*) {
    m_context->reset();
    GfMenuObjSalvage::ResultParam param;
    param.m_unk2 = 1;
    GfMenuObjSalvage::openResult(m_context, param);
    GfGameArena* arena = static_cast<GfGameArena*>(owner);
    arena->m_helper->fn_710028EF70(arena->m_msgObj->m_score);
    m_step = &StateArenaResultBattle::fn_710028FB2C;
}

void StateArenaResultBattle::fn_710028FB2C(void* owner, void const*) {
    if (m_context->isTerm()) {
        static_cast<GfGameArena*>(owner)->m_helper->destroyCameraCut01();
        m_timer = 0.0f;
        m_step = &StateArenaResultBattle::fn_710028FB70;
    }
}

void StateArenaResultBattle::fn_710028FB70(void* owner, void const* arg) {
    m_timer += static_cast<const float*>(arg)[1];
    if (m_timer > 1.0f) {
        GfGameArena* arena = static_cast<GfGameArena*>(owner);
        arena->m_helper->fn_710028F0A4(arena->m_msgObj->m_score);
        m_step = &StateArenaResultBattle::fn_710028F99C;
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
