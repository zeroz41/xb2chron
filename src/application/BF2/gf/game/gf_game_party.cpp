#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjUtil.h"
#include "gf/GfDataParty.h"
#include "classes/gf/GfPause.h"
#include "gf/GfDataParty.h"
#include "gf/GfReqParam.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfSelectBlade.h"
#include "gf/MsgUnk_1000033.h"
#include "classes/gf/GfGameMoverSwitcher.h"
#include "gf/GfDataParty.h"
#include "classes/gf/GfStatusProperty.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfStatusProperty.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataParty.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfSelectBlade.h"

namespace gf {

GfGameParty::~GfGameParty() {
    GfObjManager::removeListener(this);
}

void GfGameParty::build(const GfSetupParam& param) {
#line 90
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameParty(param);
}

void GfGameParty::destroy() {
    GfGameParty* party = get();
    party->finalize();
    if (party != nullptr) {
        delete party;
    }
}

GF_OBJ_HANDLE* GfGameParty::getLeader() {
    return getHandleByHierarchy(1);
}

unsigned int GfGameParty::getDriverBdatId(unsigned int index, unsigned int party) {
    if (index == static_cast<unsigned int>(-1)) {
        return 0;
    }
    return GfDataParty::getPartyMember(index, party)->m_driver;
}

GF_OBJ_HANDLE* GfGameParty::getHandleMover(unsigned int id) {
    if (id == 0) {
        return GfGameManager::getControlMover();
    }
    GfGameParty* party = get();
    return id != static_cast<unsigned int>(-1) && party != nullptr ? party->m_members[id].m_handles[0]
                                                                   : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfGameParty::getHandleDriver(unsigned int index, unsigned int party) {
    GfGameParty* self = get();
    return index != static_cast<unsigned int>(-1) && self != nullptr ? self->m_members[index].m_handles[party]
                                                                     : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfGameParty::getHandleBlade(unsigned int index, int slot) {
    GfGameParty* party = get();
    if (index != static_cast<unsigned int>(-1) && party != nullptr) {
        int set = getBladeSetId(index, slot);
        return set >= 0 ? party->m_members[index].m_handles[3 + set] : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

int GfGameParty::getBladeSetId(unsigned int index, int set) {
    if (set >= 0) {
        return set;
    }
    unsigned int driver = 0;
    if (index != static_cast<unsigned int>(-1)) {
        driver = GfDataParty::getPartyMember(index, 0)->m_driver;
    }
    return GfDataDriver::getBladeSet(driver);
}

unsigned int GfGameParty::getBladeBdatId(unsigned int index, int slot) {
    unsigned int driver = 0;
    if (index != static_cast<unsigned int>(-1)) {
        driver = GfDataParty::getPartyMember(index, 0)->m_driver;
    }
    DataParamAcc acc(3, driver, GimmickType(0));
    return acc.getBlade(slot, false);
}

void GfGameParty::gevGameObjEnter(GF_OBJ_HANDLE* handle) {
    get()->createdObject(handle);
    if (GfObjUtil::getObjType(handle) == 3 && GfObjUtil::getObjSetup(handle)->m_createType == 1) {
        GfEvent::callPartyDriver(handle, GfObjUtil::getObjSetup(handle)->m_partyId, true);
    }
}

void GfGameParty::gevGameObjLeave(GF_OBJ_HANDLE* handle) {
    if (GfObjUtil::getObjType(handle) == 3 && GfObjUtil::getObjSetup(handle)->m_createType == 1) {
        GfEvent::callPartyDriver(handle, GfObjUtil::getObjSetup(handle)->m_partyId, false);
    }
}

void GfGameParty::gevPartyIDMemberOK(bool ok, unsigned int id) {
    if (ok) {
        if (GfGameScene* scene = GfGameScene::get()) {
            scene->setRideOn(id);
        }
    }
}

void GfGameParty::setupBattleStart(unsigned int index) {
    DataParamAcc acc(getHandleDriver(index, 0));
    GfSelectBlade::s_pThis->m_startBattleSetId[index] = acc.getBladeSet(false);
}

unsigned short GfGameParty::getPartyGauge() {
    return GfDataParty::getSDataParty()->m_partyGauge;
}

void GfGameParty::setPartyGauge(unsigned short gauge) {
    GfDataParty::getSDataParty()->m_partyGauge = gauge;
}

GfStatusProperty* GfGameParty::getPartyStatusProperty(unsigned int index) {
    GfGameParty* party = get();
    if (party == nullptr) {
        return nullptr;
    }
    return party->m_members[index].m_statusProperty.get();
}

bool GfGameParty::isBtlLeaderDirver() {
    return GfObjUtil::isBattle(getHandleDriver(getPartyId(getLeader()), 0));
}

GF_OBJ_HANDLE* GfGameParty::getLeaderDriver() {
    return getHandleDriver(getPartyId(getLeader()), 0);
}

bool GfGameParty::isLeaderBlade() {
    GfObjAcc acc(getLeader());
    return acc.getType() == 4;
}

GfComTransform* GfGameParty::getLeaderTransform() {
    GfObj* obj = GfObjUtil::getObj(GfGameManager::getControlMover());
    if (obj == nullptr) {
        return nullptr;
    }
    return obj->getComponent<GfComTransform>(0);
}

GfObj* GfGameParty::getLeaderTransformObj() {
    return GfObjUtil::getObj(GfGameManager::getControlMover());
}

bool GfGameParty::isLeaderDriver(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return getHandleDriver(getPartyId(getLeader()), 0) == handle;
}

void GfGameParty::fn_71002BC718(unsigned int slot) {
    GfGameMoverSwitcher* switcher = GfGameMoverSwitcher::get();
    if (switcher == nullptr) {
        return;
    }
    GfObj* obj = GfObjUtil::getObj(getHandleDriver(slot, 0));
    if (obj == nullptr) {
        return;
    }
    MsgUnk_1000033 msg(slot, 0, 1);
    // sent through the switcher's fw::MessageObject base
    static_cast<fw::MessageObject*>(switcher)->recieveMessage(obj, msg);
}

void GfGameParty::fn_71002BC7AC(unsigned int slot) {
    GfGameMoverSwitcher* switcher = GfGameMoverSwitcher::get();
    if (switcher == nullptr) {
        return;
    }
    GfObj* obj = GfObjUtil::getObj(getHandleDriver(slot, 0));
    if (obj == nullptr) {
        return;
    }
    MsgUnk_1000033 msg(slot, 0, 2);
    // sent through the switcher's fw::MessageObject base
    static_cast<fw::MessageObject*>(switcher)->recieveMessage(obj, msg);
}

void GfGameParty::fn_71002BC840(unsigned int slot) {
    GfGameMoverSwitcher* switcher = GfGameMoverSwitcher::get();
    if (switcher == nullptr) {
        return;
    }
    GfObj* obj = GfObjUtil::getObj(getHandleDriver(slot, 0));
    if (obj == nullptr) {
        return;
    }
    MsgUnk_1000033 msg(slot, 1, 2);
    // sent through the switcher's fw::MessageObject base
    static_cast<fw::MessageObject*>(switcher)->recieveMessage(obj, msg);
}

int GfSelectBlade::getStartBattleSetId(unsigned int slot) {
    if (slot > 2 || s_pThis == nullptr) {
        return -1;
    }
    return s_pThis->m_startBattleSetId[slot];
}

void GfSelectBlade::resetStartBattleSetId(unsigned int slot) {
    if (slot <= 2 && s_pThis != nullptr) {
        s_pThis->m_startBattleSetId[slot] = -1;
    }
}


void GfGameParty::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int type) {
    if (type != 3 && type != 4 && type != 10 && type != 11) {
        return;
    }
    switch (static_cast<int>(evt)) {
    case 1:
        entryHandle(handle, type);
        break;
    case 2:
        if (GfPause::isPause(1) && getHandleByHierarchy(1) == handle) {
            GfGameScene* scene = GfGameScene::get();
            if (scene != nullptr) {
                scene->setCameraAvtivateOneTime();
            }
        }
        if (GfGameManager::fn_71002A9E68() && GfObjUtil::fn_710054FCDC(handle) == 2) {
            fn_71002BC46C(handle, false);
        }
        break;
    case 3:
        destroyedObject(handle);
        break;
    case 4:
        removeHandle(handle);
        break;
    }
}

void GfGameParty::fn_71002B8D3C() {
    if (!m_currentPartyValid) {
        getCurrentPartyInfo(m_currentParty);
        m_currentPartyValid = true;
    }
}

void GfGameParty::fn_71002B8D70() {}

void GfGameParty::fn_71002B8D74(GEV gev, unsigned int) {
    if (gev == GEV(10)) {
        fn_71002B8D88(m_currentParty);
    }
}

unsigned int GfGameParty::getLeaderLevel() {
    SDataParty* data = GfDataParty::getSDataParty();
    unsigned int driver = 0;
    if (data->m_leaderType == 3) {
        driver = data->m_leader;
    } else if (data->m_leaderType == 4) {
        unsigned int id = getPartyId(4, data->m_leader);
        driver = id != static_cast<unsigned int>(-1) ? GfDataParty::getPartyMember(id, 0)->m_driver : 0;
    }
    DataParamAcc acc(3, driver, GimmickType(0));
    return acc.getLevel(false);
}

GfWeapon* GfGameParty::getHandleWeapon(unsigned int index, int set) {
    GF_OBJ_HANDLE* handle;
    if (GfDataDriver::fn_710023F9A8(getDriverBdatId(index, 0))) {
        handle = getHandleDriver(index, 0);
    } else {
        handle = getHandleBlade(index, getBladeSetId(index, set));
    }
    return GfMountManager::getGfWeapon(handle, GFATTACH(0));
}

GfWeapon* GfGameParty::fn_71002B7C34(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() == 3) {
        if (GfDataDriver::fn_710023F9A8(acc.getDriverId())) {
            return GfMountManager::getGfWeapon(handle, GFATTACH(0));
        }
        if (acc.getPartyID() != static_cast<unsigned int>(-1)) {
            return getHandleWeapon(acc.getPartyID(), -1);
        }
    }
    return nullptr;
}

void GfGameParty::fn_71002BC3B4() {
    m_hierarchy.clear();
    m_hierarchy.push_back(0);
    if (GfGameManager::fn_71002A9E68()) {
        m_hierarchy.push_back(1);
        m_hierarchy.push_back(2);
    }
}

unsigned int GfGameParty::fn_71002BC338() {
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; ++i) {
        count += GfObjUtil::isValid(getHandleDriver(i, 0));
    }
    return count;
}

bool GfGameParty::fn_71002BC6D0() {
    GfGameParty* party = get();
    return party != nullptr ? party->m_currentPartyValid : false;
}

GF_OBJ_HANDLE* GfGameParty::fn_71002BC6F8() {
    GfGameParty* party = get();
    return party != nullptr ? party->m_warpObj : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

}  // namespace gf
