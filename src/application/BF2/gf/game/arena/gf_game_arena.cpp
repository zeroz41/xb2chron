// the arena (challenge battle) game mode: its singleton GfGameArena, its state machine and the simple states

#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameArena.h"
#include "gf/SDataGame.h"
#include "classes/gf/GfArenaBattle.h"
#include "classes/gf/GfArenaParty.h"
#include "classes/gf/GfArenaReward.h"
#include "classes/gf/GfArenaJingle.h"
#include "classes/gf/StateArenaWait.h"
#include "classes/gf/StateArenaSetup.h"
#include "classes/gf/StateArenaLeave.h"
#include "classes/gf/StateArenaField.h"
#include "classes/gf/StateArenaDestroy.h"
#include "classes/gf/StateArenaStartBattle.h"
#include "classes/gf/StateArenaExecBattle.h"
#include "classes/gf/StateArenaResultBattle.h"
#include "classes/gf/StateArenaReturnBattle.h"
#include "classes/gf/StateArenaEvent.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfManager.h"
#include "classes/ml/MicroThread.h"
#include "classes/gf/GfPlayComStartChallengeBattle.h"
#include "classes/gf/GfInfo.h"
#include "classes/fw/SoundResource.h"
#include "classes/fw/SoundManager.h"
#include "gf/GfDataSound.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/SDataGame.h"

namespace gf {

MapJumpForReturnBattle::MapJumpForReturnBattle() : m_mapjumpId(0xE1) {}

bool GfGameArena::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x1000034) {
        procMsgGameBtlArena(sender, static_cast<MsgGameBtlArena&>(msg));
        return true;
    }
    return false;
}

void GfGameArena::initialize(const GfSetupParam& param) {
#line 109
    m_partySetup = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfArenaParty(this);
    m_msgObj = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfArenaBattle(this);
    m_helper = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfArenaReward(this);
    m_sound = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfArenaJingle();
    m_fsm.beginSetup(this, 10);
    m_fsm.registerState<StateArenaWait>(0);
    m_fsm.registerState<StateArenaSetup>(1);
    m_fsm.registerState<StateArenaLeave>(2);
    m_fsm.registerState<StateArenaField>(3);
    m_fsm.registerState<StateArenaDestroy>(9);
    m_fsm.registerState<StateArenaStartBattle>(4);
    m_fsm.registerState<StateArenaExecBattle>(5);
    m_fsm.registerState<StateArenaResultBattle>(6);
    m_fsm.registerState<StateArenaReturnBattle>(7);
    m_fsm.registerState<StateArenaEvent>(8);
    m_fsm.endSetup();
    m_fsm.setState(0);
#line 130
    m_updater = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MicroUpdater<GfGameArena>();
    m_updater->start(this, &fnUpdate);
    GfArenaUtil::setupChBtlList(m_ids);
    m_sound->initialize();
    GfGameFlag::setLocal(1, 0xDC0D, 0);
    m_isSetUp = true;
}

GfGameArena::~GfGameArena() {}

void GfGameArena::build(const GfSetupParam& param) {
#line 89
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameArena(param);
}

void GfGameArena::destroy() {
    GfGameArena* self = sys();
    self->finalize();
    delete self;
}

void GfGameArena::finalize() {
    while (!isStateDestroy()) {
        GfSleep(1);
    }
    if (m_updater != nullptr) {
        delete m_updater;
        m_updater = nullptr;
    }
    m_fsm.cleanup();
    m_sound->finalize();
    if (m_sound != nullptr) {
        delete m_sound;
        m_sound = nullptr;
    }
    if (m_helper != nullptr) {
        delete m_helper;
        m_helper = nullptr;
    }
    if (m_msgObj != nullptr) {
        delete m_msgObj;
        m_msgObj = nullptr;
    }
    if (m_partySetup != nullptr) {
        delete m_partySetup;
        m_partySetup = nullptr;
    }
    m_isSetUp = false;
}

void GfGameArena::fnUpdate(GfGameArena* self) {
    for (;;) {
        self->m_fsm.update(&self->m_updateInfo);
        ml::MicroThread::sys()->sleep(0, true);
    }
}

bool GfGameArena::isStateDestroy() const {
    return m_fsm.m_pState->m_stateID == 9;
}

bool GfGameArena::isBattleNow() const {
    return m_fsm.m_pState->m_stateID == 5;
}

bool GfGameArena::isDestroyNow() const {
    if (GfManager::isDestroyNow()) {
        return true;
    }
    return m_isEnd;
}

bool GfGameArena::isEnableStartBattle() const {
    return m_fsm.m_pState->m_stateID == 3;
}

bool GfGameArena::isActiveArena() const {
    return GfGameFlag::getLocal(1, 0xDC0D) != 0;
}

bool GfGameArena::isInvalidTutorial() const {
    if (m_msgObj->m_isDone) {
        return true;
    }
    return m_fsm.m_pState->m_stateID == 7;
}

bool GfGameArena::isPlayEvent() const {
    return m_fsm.m_pState->m_stateID == 8;
}

void GfGameArena::sleep(unsigned int frames) {
    ml::MicroThread::sys()->sleep(frames, true);
}

unsigned int GfGameArena::getWeaponDamage(GF_OBJ_HANDLE* handle) const {
    return m_partySetup->getWeaponDamage(m_msgObj->m_key, handle);
}

void GfGameArena::createMapSound() {
    fw::SoundResource::SetupInfo info;
    info.pad_8 = 0x80;
    info.pad_0 = 5;
    info.pad_4 = 0;
    mm::mtl::FixStr<128> path;
    GfDataSound::getFullPath(path, "dlc_se_btl_chbtl");
    m_soundResource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), path.m_str, info,
                                                 static_cast<fw::LOAD_PRIO>(10));
    while (!m_soundResource->valid()) {
        ml::MicroThread::sys()->sleep(0, true);
    }
    m_soundPack = fw::SoundManager::sys()->findPack("dlc_se_btl_chbtl", nullptr);
}

// Proposed name, not the original's: the names of the arena states (IDs 0..9: 3 is the field state, 9 the one
// finalize waits for). Only the strings survive in the original (.rodata lbl_710098A308..0x710098A38D, after
// "dlc_se_btl_chbtl", no reference left): what pointed at them was unreferenced and dropped by the linker.
const char* g_arenaStateNames[] = {
    "ARENA_WAIT", "ARENA_SETUP", "ARENA_LEAVE", "ARENA_FIELD", "ARENA_BTL_START",
    "ARENA_BTL", "ARENA_BTL_RESULT", "ARENA_BTL_RETURN", "ARENA_EVENT", "ARENA_DESTROY",
};

void GfGameArena::destroyMapSound() {
    fw::SoundResource* resource = m_soundResource;
    m_soundPack = nullptr;
    if (resource != nullptr) {
        resource->release();
        m_soundResource = nullptr;
    }
}

void GfGameArena::setupGame() {
    GfArenaUtil::setupSaveData(GfDataManager::getDataGame()->m_ruleTable, m_ids);
}

SaveChBtl* GfGameArena::getSaveInfo() const {
    return &GfDataManager::getDataGame()->m_ruleTable;
}

// the difficulty indexes as an unsigned value (umaddl): GFDIFF's own underlying type is unsigned, while the tree
// declares it `enum GFDIFF : int`
ChBtlInfo::ChBtlDiff* GfGameArena::getSaveInfo(unsigned int id, GFDIFF diff) const {
    mm::mtl::FixedArray<ChBtlInfo, 48>& rows = GfDataManager::getDataGame()->m_ruleTable.m_rows;
    return &rows[id].m_rules[static_cast<unsigned int>(diff)];
}

unsigned int GfGameArena::update(const fw::UpdateInfo& info) {
    m_updateInfo = info;
    m_updater->update();
    if (m_sound != nullptr) {
        m_sound->update(info);
    }
    return GfGameFlag::getLocal(1, 0xDC0D);
}

bool GfGameArena::isBusy() const {
    return ::mm::mtl::PtrSingleton<GfPlayComStartChallengeBattle>::sys() != nullptr;
}

}  // namespace gf
