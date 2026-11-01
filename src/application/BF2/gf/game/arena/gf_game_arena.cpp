// the arena (challenge battle) game mode: its singleton TUnk_B535D0, its state machine and the simple states

#include "classes/gf/GfGameManager.h"
#include "classes/gf/TUnk_B535D0.h"
#include "gf/SDataGame.h"
#include "classes/gf/TUnk_B52C38.h"
#include "classes/gf/TUnk_28D7B8.h"
#include "classes/gf/TUnk_28E618.h"
#include "classes/gf/TUnk_28D5BC.h"
#include "classes/gf/TUnk_B52C68.h"
#include "classes/gf/TUnk_B53648.h"
#include "classes/gf/TUnk_B53690.h"
#include "classes/gf/TUnk_B52EC0.h"
#include "classes/gf/TUnk_B536D8.h"
#include "classes/gf/TUnk_B53720.h"
#include "classes/gf/TUnk_B53768.h"
#include "classes/gf/TUnk_B537B0.h"
#include "classes/gf/TUnk_B53118.h"
#include "classes/gf/TUnk_B53370.h"
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

TUnk_B535D0::MapjumpParam::MapjumpParam() : m_mapjumpId(0xE1) {}

bool TUnk_B535D0::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x1000034) {
        fn_7100290D40(sender, static_cast<MsgUnk_1000034&>(msg));
        return true;
    }
    return false;
}

void TUnk_B535D0::fn_7100291100(const GfSetupParam& param) {
#line 109
    m_partySetup = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) TUnk_28D7B8(this);
    m_msgObj = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) TUnk_B52C38(this);
    m_helper = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) TUnk_28E618(this);
    m_sound = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) TUnk_28D5BC();
    m_fsm.beginSetup(this, 10);
    m_fsm.registerState<TUnk_B52C68>(0);
    m_fsm.registerState<TUnk_B53648>(1);
    m_fsm.registerState<TUnk_B53690>(2);
    m_fsm.registerState<TUnk_B52EC0>(3);
    m_fsm.registerState<TUnk_B536D8>(9);
    m_fsm.registerState<TUnk_B53720>(4);
    m_fsm.registerState<TUnk_B53768>(5);
    m_fsm.registerState<TUnk_B537B0>(6);
    m_fsm.registerState<TUnk_B53118>(7);
    m_fsm.registerState<TUnk_B53370>(8);
    m_fsm.endSetup();
    m_fsm.setState(0);
#line 130
    m_updater = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MicroUpdater<TUnk_B535D0>();
    m_updater->start(this, &fn_7100291C6C);
    fn_71002906D0(m_ids);
    m_sound->fn_710028D5F0();
    GfGameFlag::setLocal(1, 0xDC0D, 0);
    m_isSetUp = true;
}

TUnk_B535D0::~TUnk_B535D0() {}

void TUnk_B535D0::fn_7100291AD8(const GfSetupParam& param) {
#line 89
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) TUnk_B535D0(param);
}

void TUnk_B535D0::fn_7100291B1C() {
    TUnk_B535D0* self = sys();
    self->fn_7100291B64();
    delete self;
}

void TUnk_B535D0::fn_7100291B64() {
    while (!fn_7100291CAC()) {
        GfSleep(1);
    }
    if (m_updater != nullptr) {
        delete m_updater;
        m_updater = nullptr;
    }
    m_fsm.cleanup();
    m_sound->fn_710028D624();
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

void TUnk_B535D0::fn_7100291C6C(TUnk_B535D0* self) {
    for (;;) {
        self->m_fsm.update(&self->m_updateInfo);
        ml::MicroThread::sys()->sleep(0, true);
    }
}

bool TUnk_B535D0::fn_7100291CAC() {
    return m_fsm.m_pState->m_stateID == 9;
}

bool TUnk_B535D0::fn_7100291D54() {
    return m_fsm.m_pState->m_stateID == 5;
}

bool TUnk_B535D0::fn_7100291D68() {
    if (GfManager::isDestroyNow()) {
        return true;
    }
    return m_isEnd;
}

bool TUnk_B535D0::fn_7100291DA0() {
    return m_fsm.m_pState->m_stateID == 3;
}

bool TUnk_B535D0::fn_7100291DB4() {
    return GfGameFlag::getLocal(1, 0xDC0D) != 0;
}

bool TUnk_B535D0::fn_7100291DD8() {
    if (m_msgObj->m_isDone) {
        return true;
    }
    return m_fsm.m_pState->m_stateID == 7;
}

bool TUnk_B535D0::fn_7100291E00() {
    return m_fsm.m_pState->m_stateID == 8;
}

void TUnk_B535D0::fn_7100291E2C(unsigned int frames) {
    ml::MicroThread::sys()->sleep(frames, true);
}

unsigned int TUnk_B535D0::fn_7100291E14(GF_OBJ_HANDLE* handle) {
    return m_partySetup->fn_710028E5BC(m_msgObj->m_key, handle);
}

void TUnk_B535D0::fn_7100291F2C() {
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
// fn_7100291B64 waits for). Only the strings survive in the original (.rodata lbl_710098A308..0x710098A38D, after
// "dlc_se_btl_chbtl", no reference left): what pointed at them was unreferenced and dropped by the linker.
const char* g_arenaStateNames[] = {
    "ARENA_WAIT", "ARENA_SETUP", "ARENA_LEAVE", "ARENA_FIELD", "ARENA_BTL_START",
    "ARENA_BTL", "ARENA_BTL_RESULT", "ARENA_BTL_RETURN", "ARENA_EVENT", "ARENA_DESTROY",
};

void TUnk_B535D0::fn_7100291FF0() {
    fw::SoundResource* resource = m_soundResource;
    m_soundPack = nullptr;
    if (resource != nullptr) {
        resource->release();
        m_soundResource = nullptr;
    }
}

void TUnk_B535D0::fn_7100291CC0() {
    GfDataManager::getDataGame()->m_ruleTable.fn_7100290510(m_ids);
}

TUnk_B535D0::RuleTable* TUnk_B535D0::fn_7100291CF4() {
    return &GfDataManager::getDataGame()->m_ruleTable;
}

GfGameManager::BattleChallengeRecord::Rule* TUnk_B535D0::fn_7100291D14(unsigned int id, unsigned int mode) {
    RuleRow* rows = GfDataManager::getDataGame()->m_ruleTable.m_rows;
    return &rows[id].m_rules[mode];
}

unsigned int TUnk_B535D0::fn_7100292060(const fw::UpdateInfo& info) {
    m_updateInfo = info;
    m_updater->update();
    if (m_sound != nullptr) {
        m_sound->fn_710028D644(info);
    }
    return GfGameFlag::getLocal(1, 0xDC0D);
}

bool fn_71002920F0() {
    return ::mm::mtl::PtrSingleton<GfPlayComStartChallengeBattle>::sys() != nullptr;
}

}  // namespace gf
