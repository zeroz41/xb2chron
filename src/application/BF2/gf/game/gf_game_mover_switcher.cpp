#include "classes/fw/MessageObject.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameMoverSwitcher.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameRide.h"
#include "gf/MsgPcFieldChangeControlMode.h"
#include "gf/MsgPcFieldWarp.h"
#include "gf/MsgPcBattleStart.h"
#include "gf/MsgUnk_1000032.h"
#include "gf/MsgUnk_1000033.h"
#include "classes/gf/GfGameTarget.h"
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

bool GfGameMoverSwitcher::recieveMessage(fw::MessageObject*, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000032:
        if (m_enable) {
            switchMover();
            if (static_cast<MsgUnk_1000032&>(msg).m_value == 1) {
                GfGameTarget::disableTargetWithoutEnemy();
                if (GfObj* obj = GfObjUtil::getObj(GfGameManager::getPartyLeaderDriver())) {
                    MsgPcBattleStart message(0);
                    static_cast<fw::MessageObject*>(obj)->recieveMessage(this, message);
                }
            }
        }
        return true;
    case 0x1000033: {
        MsgUnk_1000033& ira = static_cast<MsgUnk_1000033&>(msg);
        switchMoverForIra(ira.m_slot, static_cast<PTPOS>(ira.m_value0), static_cast<PTPOS>(ira.m_value1));
        return true;
    }
    }
    return false;
}

}  // namespace gf
