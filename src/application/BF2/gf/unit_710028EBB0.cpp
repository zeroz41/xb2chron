#include "classes/gf/TUnk_B535D0.h"
#include "classes/gf/TUnk_B52C38.h"
#include "classes/gf/TUnk_28D7B8.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/TUnk_B52C68.h"
#include "classes/gf/TUnk_B52EC0.h"
#include "classes/gf/TUnk_B53118.h"
#include "classes/gf/TUnk_B53370.h"
#include "classes/gf/TUnk_B537B0.h"
#include "classes/gf/TUnk_28E618.h"
#include "classes/gf/GfMenuObjSalvage.h"
#include "math.h"
#include "classes/gf/TUnk_B53648.h"
#include "classes/gf/TUnk_B53690.h"
#include "classes/gf/TUnk_B53720.h"
#include "classes/gf/TUnk_B53768.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataBlade.h"
#include "gf/MapjumpCallbackInfo.h"
#include "btl/Utility.h"

namespace gf {

void TUnk_B52C68::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    switch (static_cast<int>(gev)) {
    case 1:
        if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
            if (!arena->fn_7100291DB4() && GfDataMap::getMapID(info.m_mapJumpId) == 0x3A) {
                MsgUnk_1000034 msg(0xB);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
        break;
    case 6:
        if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
            if (arena->fn_7100291DB4()) {
                m_arenaFlagSeen = true;
            }
        }
        break;
    }
}

void TUnk_B53648::fn_710028F3F0(void* owner, ai::State*) {
    static_cast<TUnk_B535D0*>(owner)->fn_7100291F2C();
}

void TUnk_B53648::fn_710028F3F8(void*, ai::State*) {}

void TUnk_B53648::fn_710028F3FC(void*, void const*) {
    requestState(3);
}

void TUnk_B53690::fn_710028F444(void* owner, ai::State*) {
    TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
    arena->m_partySetup->fn_710028DAB4();
    arena->fn_7100291FF0();
}

void TUnk_B53690::fn_710028F46C(void*, ai::State*) {}

void TUnk_B53690::fn_710028F470(void*, void const*) {
    requestState(9);
}

void TUnk_B52EC0::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    if (gev == 1) {
        if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
            if (arena->fn_7100291DB4() && GfDataMap::getMapID(info.m_mapJumpId) != 0x3A) {
                MsgUnk_1000034 msg(0xA);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
    }
}

void TUnk_B53720::fn_710028F5F8(void*, ai::State*) {}

void TUnk_B53720::fn_710028F5FC(void*, ai::State*) {}

void TUnk_B53720::fn_710028F600(void* owner, void const*) {
    TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
    if (arena->m_partySetup->fn_710028E4E8(arena->m_msgObj->m_key)) {
        GfMenuManager::fn_710035A460();
        arena->m_msgObj->fn_710028CF40();
        requestState(5);
    } else {
        requestState(3);
    }
}

void TUnk_B53768::fn_710028F694(void*, ai::State*) {
    btl::Utility::fn_710000FB3C();
}

void TUnk_B53768::fn_710028F698(void*, ai::State*) {}

void TUnk_B53768::fn_710028F69C(void* owner, void const* arg) {
    static_cast<TUnk_B535D0*>(owner)->m_msgObj->fn_710028CFF8(arg);
    requestState(7);
}

void TUnk_B53118::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&) {
    if (gev == 4) {
        if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
            arena->m_msgObj->fn_710028D584();
        }
    }
}

void TUnk_B537B0::fn_710028F738(void* owner, ai::State*) {
    static_cast<TUnk_B535D0*>(owner)->m_helper->fn_710028EDAC();
    m_step = &TUnk_B537B0::fn_710028F770;
    m_context = GfMenuCallContext::create();
}

void TUnk_B537B0::fn_710028F770(void* owner, void const*) {
    TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
    if (arena->m_msgObj->m_result == 2 || arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score)) {
        m_step = &TUnk_B537B0::fn_710028F858;
    } else {
        m_step = &TUnk_B537B0::fn_710028F8D8;
    }
}

void TUnk_B537B0::fn_710028F7C4(void*, ai::State*) {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void TUnk_B537B0::fn_710028F830(void* owner, void const* arg) {
    if (m_step) {
        (this->*m_step)(owner, arg);
    }
}

void TUnk_B537B0::fn_710028F858(void* owner, void const*) {
    TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
    mm::Mat44 mtx;
    if (arena->m_helper->fn_710028EB74(mtx)) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
        arena->m_helper->fn_710028EBB0(pos, rotY);
    }
    arena->m_helper->fn_710028ED50();
    m_timer = 0.5f;
    m_step = &TUnk_B537B0::fn_710028FA80;
}

void TUnk_B537B0::fn_710028F8D8(void* owner, void const*) {
    if (!GfGameManager::isFading(static_cast<unsigned int>(-1))) {
        TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
        bool clear = arena->m_msgObj->m_result == 2 || arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score);
        if (clear) {
            arena->m_helper->fn_710028F00C(arena->m_msgObj->m_result == 2);
            m_step = &TUnk_B537B0::fn_710028F964;
        } else {
            arena->m_helper->fn_710028F00C(false);
            m_step = &TUnk_B537B0::fn_710028F99C;
        }
    }
}

void TUnk_B537B0::fn_710028F964(void*, void const*) {
    m_context->reset();
    GfMenuObjSalvage::fn_710046F628(m_context);
    m_step = &TUnk_B537B0::fn_710028F9F0;
}

void TUnk_B537B0::fn_710028F99C(void* owner, void const*) {
    static_cast<TUnk_B535D0*>(owner)->m_helper->fn_710028ECA0();
    requestState(3);
    m_step = nullptr;
}

void TUnk_B537B0::fn_710028F9F0(void*, void const*) {
    if (m_context->isTerm()) {
        m_step = &TUnk_B537B0::fn_710028FA24;
    }
}

void TUnk_B537B0::fn_710028FA24(void* owner, void const*) {
    TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
    if (arena->m_helper->fn_710028E7DC(arena->m_msgObj->m_score)) {
        arena->m_helper->fn_710028E69C(arena->m_msgObj->m_score);
    } else {
        arena->m_helper->fn_710028E878(arena->m_msgObj->m_score);
    }
    m_timer = 0.5f;
    m_step = &TUnk_B537B0::fn_710028FAA8;
}

void TUnk_B537B0::fn_710028FA80(void*, void const* arg) {
    m_timer -= static_cast<const float*>(arg)[0];
    if (m_timer < 0.0f) {
        m_step = &TUnk_B537B0::fn_710028F8D8;
    }
}

void TUnk_B537B0::fn_710028FAA8(void*, void const* arg) {
    m_timer -= static_cast<const float*>(arg)[1];
    if (m_timer < 0.0f) {
        m_step = &TUnk_B537B0::fn_710028FAD0;
    }
}

void TUnk_B537B0::fn_710028FAD0(void* owner, void const*) {
    m_context->reset();
    GfMenuObjSalvage::ResultParam param;
    param.m_unk2 = 1;
    GfMenuObjSalvage::openResult(m_context, param);
    TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
    arena->m_helper->fn_710028EF70(arena->m_msgObj->m_score);
    m_step = &TUnk_B537B0::fn_710028FB2C;
}

void TUnk_B537B0::fn_710028FB2C(void* owner, void const*) {
    if (m_context->isTerm()) {
        static_cast<TUnk_B535D0*>(owner)->m_helper->fn_710028ECA0();
        m_timer = 0.0f;
        m_step = &TUnk_B537B0::fn_710028FB70;
    }
}

void TUnk_B537B0::fn_710028FB70(void* owner, void const* arg) {
    m_timer += static_cast<const float*>(arg)[1];
    if (m_timer > 1.0f) {
        TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
        arena->m_helper->fn_710028F0A4(arena->m_msgObj->m_score);
        m_step = &TUnk_B537B0::fn_710028F99C;
    }
}

void TUnk_B53370::gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) {}

void TUnk_B53370::gevPlayEvent(gf::GEV gev, unsigned int) {
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

void fn_710029064C(unsigned int id) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    if (unsigned int map = btl->fn_71001E979C(id)) {
        unsigned int mapId = GfDataMap::getMapID(map);
        unsigned int weather = btl->fn_71001E9824(id);
        MapEnvData* env = GfDataBlade::fn_710024E1C8(mapId);
        if (env->m_mapId == mapId) {
            env->m_id = static_cast<WEATHERID>(weather < 4 ? weather + 1 : 5);
            env->m_time = 0.0f;
            env->m_timeMax = 100.0f;
        }
    }
}

}  // namespace gf
