#include "classes/fw/MessageObject.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameMoverSwitcher.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameRide.h"
#include "gf/MsgPcFieldChangeControlMode.h"
#include "gf/MsgPcFieldWarp.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjUtil.h"

namespace gf {

void GfGameMoverSwitcher::build(const GfSetupParam& param) {
#line 38
    GfGameMoverSwitcher* switcher = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameMoverSwitcher();
    switcher->setup();
}

void GfGameMoverSwitcher::destroy() {
    GfGameMoverSwitcher* switcher = get();
    if (switcher != nullptr) {
        switcher->cleanup();
        delete switcher;
    }
}

GfGameMoverSwitcher::~GfGameMoverSwitcher() {}

void GfGameMoverSwitcher::gevPartyMemberOK(bool ok) {
    if (!ok) {
        return;
    }
    if (GfObjUtil::getObjType(GfGameManager::getPartyLeader()) == 4 && !GfGameRide::isRideOnPair()) {
        m_enable = true;
    } else {
        m_enable = false;
    }
}

void GfGameMoverSwitcher::gevPartyReturnFieldState(unsigned int state) {
    if (state == 0 && m_enable && GfGameParty::getLeaderDriver() == GfGameManager::getControlMover()) {
        switchMover();
    }
}

void GfGameMoverSwitcher::switchMover() {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    if (formation == nullptr) {
        return;
    }
    formation->swapFormation(0, 1);
    // the new leader takes the control, the old one follows
    for (int i = 0; i < 2; i++) {
        if (GfObj* obj = GfObjUtil::getObj(formation->m_players[i].m_handle)) {
            MsgPcFieldChangeControlMode mode(i);
            sendMessage(obj, mode);
            MsgPcFieldWarp warp;
            warp.m_transform.rotation = formation->m_followTransforms[0].rotation;
            warp.m_transform.position = formation->m_targetPos[i];
            warp.m_immediate = true;
            sendMessage(obj, warp);
        }
    }
}

}  // namespace gf
