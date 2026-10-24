#include "mm/mtl/FixStr.h"
#include "ml/PathUtil.h"
#include "classes/gf/GfGameRide.h"
#include "gf/MsgGameRideEvent.h"
#include "gf/MsgPcBattleStart.h"
#include "classes/gf/GfGameTarget.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfEvent.h"
#include "fw/Message.h"
#include "gf/GfDataSave.h"
#include "classes/gf/GfGameLoad.h"
#include "ml/EventFileTh.h"

namespace gf {

void GfGameRide::build(const GfSetupParam& param) {
#line 40
    GfGameRide* ride = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameRide();
    ride->setup();
}

void GfGameRide::destroy() {
    GfGameRide* ride = get();
    ride->cleanup();
    delete ride;
}

bool GfGameRide::testRideOn() {
    return get()->m_vehicle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) &&
           get()->m_rider != reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfGameRide::setRideOn(bool on) {
    GfGameRide* ride = get();
    if (on) {
        ride->rideOn();
    } else {
        ride->getDown(GfGameManager::getPartyLeader());
    }
}

bool GfGameRide::isVehicle(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return get()->m_vehicle == handle;
}

GfGameRide::~GfGameRide() {}

bool GfGameRide::isRideOnPair() {
    if (GfObjSetup* setup = GfObjUtil::getObjSetup(GfGameManager::getPartyLeaderDriver())) {
        if (GfGameScene* scene = GfGameScene::get()) {
            return scene->isRideParty(setup->m_partyId);
        }
    }
    return false;
}

void GfGameRide::gevPartyReturnFieldState(unsigned int state) {
    if (state == 0 && isRideOnPair() &&
        (m_vehicle == reinterpret_cast<GF_OBJ_HANDLE*>(-1) || m_rider == reinterpret_cast<GF_OBJ_HANDLE*>(-1))) {
        rideOn();
    }
}

bool GfGameRide::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == MsgGameRideEvent::ID) {
        procMsgGameRideEvent(sender, static_cast<MsgGameRideEvent&>(msg));
        return true;
    }
    return false;
}

void GfGameRide::procMsgGameRideEvent(fw::MessageObject* sender, MsgGameRideEvent& msg) {
    if (!isRideOnPair()) {
        return;
    }
    switch (msg.m_type) {
    case 0:
        rideOn();
        break;
    case 1: {
        GF_OBJ_HANDLE* leader = GfGameManager::getPartyLeaderDriver();
        getDown(leader);
        if (!testRideOn()) {
            GfGameTarget::disableTargetWithoutEnemy();
            if (GfObj* obj = GfObjUtil::getObj(leader)) {
                MsgPcBattleStart message(0);
                static_cast<fw::MessageObject*>(obj)->recieveMessage(this, message);
            }
        }
        break;
    }
    case 2:
        getDown(GfGameManager::getPartyLeaderDriver());
        break;
    }
}

}  // namespace gf
