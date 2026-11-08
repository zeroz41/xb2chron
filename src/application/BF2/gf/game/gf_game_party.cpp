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
#include "gf/GfPartySelect.h"
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
#include "classes/gf/GfObjSetupBlade.h"
#include "classes/gf/GfObjSetupDriver.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "classes/gf/GfWeapon.h"
#include "gf/GfAppend.h"
#include "gf/GfObjInfo.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/SCOM_OBJ_ALPHA.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "gf/SDataDriver.h"
#include "algorithm"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfGameObj.h"

namespace gf {

GfGameParty::GfGameParty(const GfSetupParam& param)
    : m_initialized(false),
      m_memberOKCount(0),
      m_memberOKReset(false),
      m_leader(reinterpret_cast<GF_OBJ_HANDLE*>(-1)),
      m_warpObj(reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
    initialize(param);
    GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
}

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

unsigned int GfGameParty::getDriverBdatId(unsigned int index, PTPOS party) {
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

GF_OBJ_HANDLE* GfGameParty::getHandleDriver(unsigned int index, PTPOS party) {
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
        driver = GfDataParty::getPartyMember(index, static_cast<PTPOS>(0))->m_driver;
    }
    return GfDataDriver::getBladeSet(driver);
}

unsigned int GfGameParty::getBladeBdatId(unsigned int index, int slot) {
    unsigned int driver = 0;
    if (index != static_cast<unsigned int>(-1)) {
        driver = GfDataParty::getPartyMember(index, static_cast<PTPOS>(0))->m_driver;
    }
    DataParamAcc acc(3, driver, GimmickType(0));
    return acc.getBlade(slot, false);
}

unsigned int GfGameParty::getHierarchyMax() {
    GfGameParty* self = get();
    unsigned int max = 0;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : self->m_hierarchy) {
            GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(party));
            max = std::max<unsigned int>(max, member->m_hierarchyDriver);
            max = std::max<unsigned int>(max, member->m_hierarchyBlade);
        }
    }
    return max;
}

bool GfGameParty::isExistObj() {
    GfGameParty* self = get();
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : self->m_hierarchy) {
            GF_OBJ_HANDLE* handle = self->m_members[i].m_handles[party];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                GfObjAcc acc(handle);
                if (acc.isDestroy()) {
                    return true;
                }
            }
        }
        int set = getBladeSetId(i, -1);
        if (set >= 0) {
            GF_OBJ_HANDLE* handle = self->m_members[i].m_handles[3 + set];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                GfObjAcc acc(handle);
                if (acc.isDestroy()) {
                    return true;
                }
            }
        }
    }
    return false;
}

GF_OBJ_HANDLE* GfGameParty::getHandleDriverByBdatID(unsigned int driver) {
    GfGameParty* self = get();
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : self->m_hierarchy) {
            if (GfDataParty::getPartyMember(i, static_cast<PTPOS>(party))->m_driver == driver) {
                return getHandleDriver(i, static_cast<PTPOS>(party));
            }
        }
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

int GfGameParty::getPartyMemberNum() {
    GfDataManager::getDataGame();
    GfGameParty* self = get();
    int count = 0;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : self->m_hierarchy) {
            if (GfDataParty::getPartyMember(i, static_cast<PTPOS>(party))->m_driver == 0) {
                continue;
            }
            ++count;
            if (GfGameManager::isGameTypeIra()) {
                continue;
            }
            int set = getBladeSetId(i, -1);
            if (set >= 0) {
                ++count;
            }
            int num = GfDataDriver::getMaxSetBladeNum(getDriverBdatId(i, static_cast<PTPOS>(0)));
            for (int slot = 0; slot < num; ++slot) {
                if (slot != set && getBladeBdatId(i, slot) != 0) {
                    ++count;
                }
            }
        }
    }
    return count;
}

GF_OBJ_HANDLE* GfGameParty::getHandleBladeByBdatID(unsigned int blade) {
    for (unsigned int i = 0; i < 3; ++i) {
        if (getBladeBdatId(i, -1) == blade) {
            return getHandleBlade(i, -1);
        }
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
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
    DataParamAcc acc(getHandleDriver(index, static_cast<PTPOS>(0)));
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
    return GfObjUtil::isBattle(getHandleDriver(getPartyId(getLeader()), static_cast<PTPOS>(0)));
}

GF_OBJ_HANDLE* GfGameParty::getLeaderDriver() {
    return getHandleDriver(getPartyId(getLeader()), static_cast<PTPOS>(0));
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
    return getHandleDriver(getPartyId(getLeader()), static_cast<PTPOS>(0)) == handle;
}

void GfGameParty::switchFormationForIra(unsigned int slot) {
    GfGameMoverSwitcher* switcher = GfGameMoverSwitcher::get();
    if (switcher == nullptr) {
        return;
    }
    GfObj* obj = GfObjUtil::getObj(getHandleDriver(slot, static_cast<PTPOS>(0)));
    if (obj == nullptr) {
        return;
    }
    MsgUnk_1000033 msg(slot, 0, 1);
    // sent through the switcher's fw::MessageObject base
    static_cast<fw::MessageObject*>(switcher)->recieveMessage(obj, msg);
}

void GfGameParty::switchFormationForIraFR(unsigned int slot) {
    GfGameMoverSwitcher* switcher = GfGameMoverSwitcher::get();
    if (switcher == nullptr) {
        return;
    }
    GfObj* obj = GfObjUtil::getObj(getHandleDriver(slot, static_cast<PTPOS>(0)));
    if (obj == nullptr) {
        return;
    }
    MsgUnk_1000033 msg(slot, 0, 2);
    // sent through the switcher's fw::MessageObject base
    static_cast<fw::MessageObject*>(switcher)->recieveMessage(obj, msg);
}

void GfGameParty::switchFormationForIraBR(unsigned int slot) {
    GfGameMoverSwitcher* switcher = GfGameMoverSwitcher::get();
    if (switcher == nullptr) {
        return;
    }
    GfObj* obj = GfObjUtil::getObj(getHandleDriver(slot, static_cast<PTPOS>(0)));
    if (obj == nullptr) {
        return;
    }
    MsgUnk_1000033 msg(slot, 1, 2);
    // sent through the switcher's fw::MessageObject base
    static_cast<fw::MessageObject*>(switcher)->recieveMessage(obj, msg);
}

void GfGameParty::setupChangePartyPos(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.isBattle()) {
        return;
    }
    unsigned int pos = GfObjUtil::getPartyPos(handle);
    bool disp = acc.isDisp(OBJDISP(0x40));
    if (pos == 2) {
        if (disp) {
            setDispIraParty(handle, false);
        }
    } else if (!disp) {
        DataParamAcc param(handle);
        setDispIraParty(handle, true);
        acc.setAlphaNormal(0.0f);
        SCOM_OBJ_ALPHA::create(handle, 1.0f, 1.0f);
        unsigned int driver = param.isValid() && param.getObjType() == 3 ? param.getBdatId() : 0;
        if (GfDataDriver::isIraHideWeaponOnField(driver)) {
            SCOM_OBJ_ALPHA::createWeapon(acc.getHandle(), 0.0f, 0.0f);
        }
    }
}

void GfGameParty::swapMemberForIra(unsigned int index, PTPOS a, PTPOS b) {
    GfDataParty::PartyMember* memberA = GfDataParty::getPartyMember(index, a);
    GfDataParty::PartyMember* memberB = GfDataParty::getPartyMember(index, b);
    unsigned short driver = memberA->m_driver;
    memberA->m_driver = memberB->m_driver;
    memberB->m_driver = driver;
    SDataIra* dataA = GfDataDriver::getSDataIra(memberA->m_driver);
    SDataIra* dataB = GfDataDriver::getSDataIra(memberB->m_driver);
    dataA->m_partyIndex = a;
    dataB->m_partyIndex = b;
    GF_OBJ_HANDLE** handles = m_members[index].m_handles;
    GF_OBJ_HANDLE* handle = handles[a];
    handles[a] = handles[b];
    handles[b] = handle;
    if (index == 0 && a == 0) {
        m_leader = handles[a];
    }
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

void GfSelectBlade::resetDefaultBladeForDebug(GF_OBJ_HANDLE* handle) {
    unsigned int id = GfGameParty::getPartyId(handle);
    if (id == static_cast<unsigned int>(-1)) {
        return;
    }
    GfSelectBlade* self = s_pThis;
    BladeOrder& order = self->m_bladeOrder[id];
    int set = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(id, static_cast<PTPOS>(0))->m_driver);
    if (set < 0) {
        return;
    }
    switch (set) {
    case 0:
        order.m_default[0] = 0;
        order.m_default[1] = 1;
        order.m_default[2] = 2;
        break;
    case 1:
        order.m_default[0] = 1;
        order.m_default[1] = 0;
        order.m_default[2] = 2;
        break;
    case 2:
        order.m_default[0] = 2;
        order.m_default[1] = 0;
        order.m_default[2] = 1;
        break;
    }
    order.m_current[0] = order.m_default[0];
    order.m_current[1] = order.m_default[1];
    order.m_current[2] = order.m_default[2];
}

void GfPartySelect::fn_71002BD018(mm::mtl::FixedVector<unsigned short, 32>& list) {
    for (unsigned int i = 0; i < 3; ++i) {
        unsigned int driver = GfDataParty::getDriver(i, static_cast<PTPOS>(0));
        if (driver != 0 && !GfDataDriver::isDummyDriver(driver)) {
            list.push_back(driver);
        }
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
        if (GfGameManager::isGameTypeIra() && GfObjUtil::getPartyPos(handle) == 2) {
            setDispIraParty(handle, false);
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

void GfGameParty::entryHandle(GF_OBJ_HANDLE* handle, unsigned int type) {
    switch (type) {
    case 3: {
        GfObjSetupDriver* setup =
            mm::mtl::rttiCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->m_setup);
        unsigned int index = setup->m_partyId;
        if (index == static_cast<unsigned int>(-1)) {
            return;
        }
        m_members[index].m_handles[GfObjUtil::getPartyPos(handle)] = handle;
        break;
    }
    case 10: {
        GfObjSetupWeapon* setup = mm::mtl::rttiCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->m_setup);
        if (setup->m_partyId == static_cast<unsigned int>(-1)) {
            return;
        }
        int set = getBladeSetId(setup->m_partyId, setup->pad_6c);
        GF_OBJ_HANDLE* owner;
        if (GfGameManager::isGameTypeIra()) {
            owner = GfObjUtil::getMaster(handle);
        } else {
            owner = getHandleBlade(setup->m_partyId, set);
        }
        GfWeapon* weapon = GfMountManager::getGfWeapon(owner, GFATTACH(0));
        GfAppend* append = GfObjUtil::getAppend(handle, GFATTACH(0));
        if (append != nullptr && setup->m_partyId != static_cast<unsigned int>(-1)) {
            unsigned short index = append->getMountIndex();
            (weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[index] = handle;
        }
        break;
    }
    case 4: {
        GfObjSetupBlade* setup = mm::mtl::rttiCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->m_setup);
        if (setup->m_partyId == static_cast<unsigned int>(-1)) {
            return;
        }
        int set = getBladeSetId(setup->m_partyId, setup->pad_6c);
        GfMemberInfo& member = m_members[setup->m_partyId];
        if (GfObjUtil::isTrinityBlade(handle)) {
            member.m_handles[8] = handle;
        } else {
            member.m_handles[3 + set] = handle;
        }
        break;
    }
    default:
        if (GfObjUtil::isDummyMover(handle)) {
            m_warpObj = handle;
        }
        break;
    }
}

// the slot lookups' results go unused (3.0.1 keeps only their calls)
void GfGameParty::destroyedObject(GF_OBJ_HANDLE* handle) {
    switch (GfObjUtil::getObjType(handle)) {
    case 3: {
        GfObjSetupDriver* setup =
            mm::mtl::rttiCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->m_setup);
        if (setup->m_partyId != static_cast<unsigned int>(-1)) {
            GfObjUtil::getPartyPos(handle);
        }
        break;
    }
    case 4: {
        GfObjSetupBlade* setup = mm::mtl::rttiCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->m_setup);
        if (setup->m_partyId != static_cast<unsigned int>(-1)) {
            getBladeSetId(setup->m_partyId, setup->pad_6c);
            GfObjUtil::isTrinityBlade(handle);
        }
        break;
    }
    }
    if (m_leader == handle) {
        m_leader = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfObjAcc acc(handle);
    unsigned int id = acc.getPartyID();
    if (id != static_cast<unsigned int>(-1)) {
        int ok = m_partyIdMemberOK[id];
        if (ok != 0) {
            m_partyIdMemberOK[id] = 0;
            if (ok == 2) {
                GfEvent::callPartyIDMemberOK(false, id);
            }
        }
    }
}

void GfGameParty::removeHandle(GF_OBJ_HANDLE* handle) {
    switch (GfObjUtil::getObjType(handle)) {
    case 3: {
        GfObjSetupDriver* setup =
            mm::mtl::rttiCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->m_setup);
        unsigned int index = setup->m_partyId;
        if (index == static_cast<unsigned int>(-1)) {
            return;
        }
        m_members[index].m_handles[GfObjUtil::getPartyPos(handle)] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        break;
    }
    case 10: {
        GfObjSetupWeapon* setup = mm::mtl::rttiCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->m_setup);
        unsigned int index = setup->m_partyId;
        if (index == static_cast<unsigned int>(-1)) {
            return;
        }
        int set = getBladeSetId(index, setup->pad_6c);
        GfWeapon* weapon = GfMountManager::getGfWeapon(getHandleBlade(setup->m_partyId, set), GFATTACH(0));
        if (weapon == nullptr) {
            return;
        }
        GfAppend* append = GfObjUtil::getAppend(handle, GFATTACH(0));
        if (append != nullptr) {
            unsigned short slot = append->getMountIndex();
            (weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[slot] =
                reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
        break;
    }
    case 4: {
        GfObjSetupBlade* setup = mm::mtl::rttiCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->m_setup);
        unsigned int index = setup->m_partyId;
        if (index == static_cast<unsigned int>(-1)) {
            return;
        }
        if (GfObjUtil::isTrinityBlade(handle)) {
            m_members[index].m_handles[8] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        } else {
            m_members[index].m_handles[3 + getBladeSetId(setup->m_partyId, setup->pad_6c)] =
                reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
        break;
    }
    default:
        if (m_warpObj == handle) {
            m_warpObj = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
        break;
    }
}

void GfGameParty::createdObject(GF_OBJ_HANDLE* handle) {
    switch (GfObjUtil::getObjType(handle)) {
    case 3: {
        GfObjSetupDriver* setup =
            mm::mtl::rttiCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->m_setup);
        unsigned int index = setup->m_partyId;
        if (index != static_cast<unsigned int>(-1)) {
            GF_OBJ_HANDLE*& slot = m_members[index].m_handles[GfObjUtil::getPartyPos(handle)];
            if (slot == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                slot = handle;
            }
        }
        break;
    }
    case 4:
        buildObjBlade(handle);
        break;
    case 10:
        buildObjWeapon(handle);
        break;
    }
}

void GfGameParty::gevBattleStart() {
    if (!m_selectIra.m_currentPartyValid) {
        getCurrentPartyInfo(m_selectIra.m_currentParty);
        m_selectIra.m_currentPartyValid = true;
    }
}

void GfGameParty::gevBattleEnd() {}

void GfGameParty::gevPlayEvent(GEV gev, unsigned int) {
    if (gev == GEV(10)) {
        m_selectIra.restorePartyMember();
    }
}

void GfGameParty::buildObjBlade(GF_OBJ_HANDLE* handle) {
    GfObjSetupBlade* setup = mm::mtl::rttiCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->m_setup);
    if (setup->m_partyId == static_cast<unsigned int>(-1)) {
        return;
    }
    int set = getBladeSetId(setup->m_partyId, setup->pad_6c);
    GfMemberInfo& member = m_members[setup->m_partyId];
    if (GfObjUtil::isTrinityBlade(handle)) {
        if (member.m_handles[8] == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            member.m_handles[8] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
    } else if (member.m_handles[3 + set] == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        member.m_handles[3 + set] = handle;
    }
}

void GfGameParty::buildObjWeapon(GF_OBJ_HANDLE* handle) {
    GfObjSetupWeapon* setup = mm::mtl::rttiCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->m_setup);
    if (setup->m_partyId == static_cast<unsigned int>(-1)) {
        return;
    }
    GfWeapon* weapon = GfMountManager::getGfWeapon(handle, GFATTACH(0));
    GfAppend* append = GfObjUtil::getAppend(handle, GFATTACH(0));
    if (weapon == nullptr || append == nullptr) {
        return;
    }
    bool second = setup->pad_78;
    unsigned short index = append->getMountIndex();
    if (weapon->getObjHandle(index, second) == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        index = append->getMountIndex();
        (weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[index] = handle;
    }
}

void GfGameParty::getCurrentPartyInfo(RQ_SETUP_PARTY& info) {
    GfGameParty* self = get();
    if (self == nullptr) {
        return;
    }
    if (GfGameManager::isGameTypeIra()) {
        for (unsigned int i = 0; i < 10; ++i) {
            for (unsigned int& party : self->m_hierarchy) {
                info.m_iraDrivers[i][party] = GfDataParty::getPartyMember(i, static_cast<PTPOS>(party))->m_driver;
            }
        }
    } else {
        for (unsigned int i = 0; i < 10; ++i) {
            RQ_SETUP_PARTY::Driver& driver = info.m_drivers[i];
            driver.m_driver = getDriverBdatId(i, static_cast<PTPOS>(0));
            driver.m_activeIndex = getBladeSetId(i, -1);
            int num = GfDataDriver::getMaxSetBladeNum(driver.m_driver);
            for (int slot = 0; slot < num; ++slot) {
                driver.m_blades[slot] = getBladeBdatId(i, slot);
            }
        }
    }
    SDataParty* data = GfDataParty::getSDataParty();
    info.m_extras[0].m_type = data->m_leaderType;
    info.m_extras[1].m_type = data->pad_44;
    info.m_extras[0].m_id = data->m_leader;
    info.m_extras[1].m_id = data->pad_48;
}

void GfGameParty::getCurrentPartyInfo(RQ_SETUP_PARTY_DRIVER& info) {
    for (unsigned int i = 0; i < 10; ++i) {
        info.m_drivers[i] = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver;
    }
    info.m_leader = GfDataParty::getSDataParty()->m_leader;
}

void GfGameParty::gevChangeBlade(GF_OBJ_HANDLE* handle, int, int) {
    unsigned int index = getPartyId(handle);
    GF_OBJ_HANDLE* driver = getHandleDriver(index, static_cast<PTPOS>(0));
    if (driver == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    OPTMNT type = GfMountManager::getMountType(driver, GFATTACH(0));
    GfMountManager::removeMountHandle(driver, GFATTACH(0));
    GfMountManager::addMountHandle(GfObjUtil::getMountHandle(getHandleBlade(index, -1), GFATTACH(0)), driver);
    GfMountManager::setMountType(driver, GFATTACH(0), type);
}

void GfGameParty::recalcHierarchy() {
    if (GfGameManager::isGameTypeIra()) {
        recalcHierarchyIra();
        return;
    }
    SDataParty* data = GfDataParty::getSDataParty();
    for (unsigned int i = 0; i < 3; ++i) {
        GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0));
        member->m_hierarchyDriver = 0;
        member->m_hierarchyBlade = 0;
    }
    unsigned int leader = 0;
    switch (data->m_leaderType) {
    case 3:
        for (unsigned int i = 0; i < 3; ++i) {
            GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0));
            if (GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver == data->m_leader) {
                member->m_hierarchyDriver = 1;
                leader = i;
                break;
            }
        }
        break;
    case 4:
        for (unsigned int i = 0; i < 3; ++i) {
            GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0));
            if (getBladeSetId(i, -1) >= 0 && getBladeBdatId(i, -1) == data->m_leader) {
                member->m_hierarchyBlade = 1;
                leader = i;
                break;
            }
        }
        break;
    default:
        for (unsigned int i = 0; i < 3; ++i) {
            if (GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver != 0) {
                data->m_leaderType = 3;
                data->m_leader = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver;
                for (unsigned int j = 0; j < 3; ++j) {
                    GfDataParty::PartyMember* member = GfDataParty::getPartyMember(j, static_cast<PTPOS>(0));
                    if (member->m_hierarchyDriver == 0) {
                        member->m_hierarchyDriver = 1;
                        leader = j;
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
    unsigned short hierarchy = 1;
    // numbers a member's driver and blade that have no hierarchy yet
    auto number = [&](GfDataParty::PartyMember* member) {
        if (member->m_driver == 0) {
            return;
        }
        if (member->m_hierarchyDriver == 0) {
            if (member->m_hierarchyBlade == 0) {
                DataParamAcc acc(3, member->m_driver, GimmickType(0));
                if (acc.isScenarioMask()) {
                    member->m_hierarchyBlade = ++hierarchy;
                    member->m_hierarchyDriver = ++hierarchy;
                } else {
                    member->m_hierarchyDriver = ++hierarchy;
                    member->m_hierarchyBlade = ++hierarchy;
                }
            } else {
                member->m_hierarchyDriver = ++hierarchy;
            }
        } else if (member->m_hierarchyBlade == 0) {
            member->m_hierarchyBlade = ++hierarchy;
        }
    };
    number(GfDataParty::getPartyMember(leader, static_cast<PTPOS>(0)));
    for (unsigned int i = 0; i < 3; ++i) {
        number(GfDataParty::getPartyMember(i, static_cast<PTPOS>(0)));
    }
}

void GfGameParty::recalcHierarchyIra() {
    SDataParty* data = GfDataParty::getSDataParty();
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : get()->m_hierarchy) {
            GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(party));
            member->m_hierarchyDriver = 0;
            member->m_hierarchyBlade = 0;
        }
    }
    unsigned int leader = 0;
    if (data->m_leaderType == 3) {
        data->m_leader = GfDataParty::getPartyMember(0, static_cast<PTPOS>(0))->m_driver;
        for (unsigned int i = 0; i < 3; ++i) {
            GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0));
            if (GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver == data->m_leader) {
                member->m_hierarchyDriver = 1;
                leader = i;
                break;
            }
        }
    } else {
        for (unsigned int i = 0; i < 3; ++i) {
            if (GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver != 0) {
                data->m_leaderType = 3;
                data->m_leader = GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver;
                for (unsigned int j = 0; j < 3; ++j) {
                    GfDataParty::PartyMember* member = GfDataParty::getPartyMember(j, static_cast<PTPOS>(0));
                    if (member->m_hierarchyDriver == 0) {
                        member->m_hierarchyDriver = 1;
                        leader = j;
                        break;
                    }
                }
                break;
            }
        }
    }
    unsigned short hierarchy = 1;
    for (unsigned int& party : get()->m_hierarchy) {
        if (party != 2) {
            GfDataParty::PartyMember* member = GfDataParty::getPartyMember(leader, static_cast<PTPOS>(party));
            if (member->m_driver != 0 && member->m_hierarchyDriver == 0) {
                member->m_hierarchyDriver = ++hierarchy;
            }
        }
    }
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : get()->m_hierarchy) {
            if (party != 2) {
                GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(party));
                if (member->m_driver != 0 && member->m_hierarchyDriver == 0) {
                    member->m_hierarchyDriver = ++hierarchy;
                }
            }
        }
    }
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int& party : get()->m_hierarchy) {
            if (party == 2) {
                GfDataParty::PartyMember* member = GfDataParty::getPartyMember(i, static_cast<PTPOS>(party));
                if (member->m_driver != 0 && member->m_hierarchyDriver == 0) {
                    member->m_hierarchyDriver = ++hierarchy;
                }
            }
        }
    }
}

bool GfGameParty::isExistMismatchScenarioMask(unsigned int index) {
    for (unsigned int i = 0; i < 3; ++i) {
        if (index == static_cast<unsigned int>(-1) || index == i) {
            GF_OBJ_HANDLE* handle = getHandleDriver(i, static_cast<PTPOS>(0));
            if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                continue;
            }
            if (GfGameObj::isValidGameObj(handle, true, nullptr) ==
                GfDataDriver::isScenarioMask(GfDataParty::getPartyMember(i, static_cast<PTPOS>(0))->m_driver)) {
                return true;
            }
        }
    }
    return false;
}

unsigned int GfGameParty::getLeaderLevel() {
    SDataParty* data = GfDataParty::getSDataParty();
    unsigned int driver = 0;
    if (data->m_leaderType == 3) {
        driver = data->m_leader;
    } else if (data->m_leaderType == 4) {
        unsigned int id = getPartyId(4, data->m_leader);
        driver = id != static_cast<unsigned int>(-1)
                     ? GfDataParty::getPartyMember(id, static_cast<PTPOS>(0))->m_driver
                     : 0;
    }
    DataParamAcc acc(3, driver, GimmickType(0));
    return acc.getLevel(false);
}

void GfGameParty::getPartyPosition(GfPartyPosInfo& info) {
    info = GfPartyPosInfo();
    for (unsigned int hierarchy = 1; hierarchy <= (GfGameManager::isGameTypeIra() ? 9u : 6u); ++hierarchy) {
        GfObjAcc acc(getHandleByHierarchy(hierarchy));
        GfPartyPosInfo::Pos& pos = info.m_pos[hierarchy - 1];
        pos.m_isValid = acc.getObjPosRot(pos.m_pos, pos.m_rotY);
    }
}

GfWeapon* GfGameParty::getHandleWeapon(unsigned int index, int set) {
    GF_OBJ_HANDLE* handle;
    if (GfDataDriver::isIra(getDriverBdatId(index, static_cast<PTPOS>(0)))) {
        handle = getHandleDriver(index, static_cast<PTPOS>(0));
    } else {
        handle = getHandleBlade(index, getBladeSetId(index, set));
    }
    return GfMountManager::getGfWeapon(handle, GFATTACH(0));
}

GfWeapon* GfGameParty::getHandleWeaponDriver(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() == 3) {
        if (GfDataDriver::isIra(acc.getDriverId())) {
            return GfMountManager::getGfWeapon(handle, GFATTACH(0));
        }
        if (acc.getPartyID() != static_cast<unsigned int>(-1)) {
            return getHandleWeapon(acc.getPartyID(), -1);
        }
    }
    return nullptr;
}

void GfGameParty::destroyHandleWeapon(unsigned int index, int set) {
    GfWeapon* weapon = getHandleWeapon(index, set);
    if (weapon == nullptr) {
        return;
    }
    weapon->m_useSecond = true;
    for (int i = 0; i < 10; ++i) {
        GfObjUtil::destroy((weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[i]);
        (weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    weapon->m_useSecond = false;
    for (int i = 0; i < 10; ++i) {
        GfObjUtil::destroy((weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[i]);
        (weapon->m_useSecond ? weapon->m_secondHandles : weapon->m_handles)[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
}

void GfGameParty::setupGame() {
    m_hierarchy.clear();
    m_hierarchy.push_back(0);
    if (GfGameManager::isGameTypeIra()) {
        m_hierarchy.push_back(1);
        m_hierarchy.push_back(2);
    }
}

unsigned int GfGameParty::getDriverNum() {
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; ++i) {
        count += GfObjUtil::isValid(getHandleDriver(i, static_cast<PTPOS>(0)));
    }
    return count;
}

bool GfGameParty::isNeedResetBladeForIra() {
    GfGameParty* party = get();
    return party != nullptr ? party->m_selectIra.m_currentPartyValid : false;
}

GF_OBJ_HANDLE* GfGameParty::getDummpMover() {
    GfGameParty* party = get();
    return party != nullptr ? party->m_warpObj : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

}  // namespace gf
