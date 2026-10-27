#include "classes/gf/TUnk_B535D0.h"
#include "classes/gf/TUnk_B52C38.h"
#include "classes/gf/TUnk_28D7B8.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/TUnk_B52C68.h"
#include "classes/gf/TUnk_B52EC0.h"
#include "classes/gf/TUnk_B53118.h"
#include "classes/gf/TUnk_B53370.h"
#include "classes/gf/TUnk_B53648.h"
#include "classes/gf/TUnk_B53690.h"
#include "classes/gf/TUnk_B53720.h"
#include "classes/gf/TUnk_B53768.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfDataMap.h"
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

void TUnk_B53370::gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) {}

void TUnk_B53370::gevPlayEvent(gf::GEV gev, unsigned int) {
    switch (static_cast<int>(gev)) {
    case 0xC: m_playState = 1; break;
    case 0xD: m_playState = 3; break;
    case 0xE: m_playState = 2; break;
    default: break;
    }
}

}  // namespace gf
