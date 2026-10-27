// the arena (challenge battle) game mode: its singleton TUnk_B535D0, its state machine and the simple states

#include "classes/gf/TUnk_B535D0.h"
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

namespace gf {

bool TUnk_B535D0::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x1000034) {
        fn_7100290D40(sender, static_cast<MsgUnk_1000034&>(msg));
        return true;
    }
    return false;
}

void TUnk_B535D0::fn_7100291100() {
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

void TUnk_B535D0::fn_7100291C6C(TUnk_B535D0* self) {
    for (;;) {
        self->m_fsm.update(self->m_stepInfo);
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

bool fn_71002920F0() {
    return ::mm::mtl::PtrSingleton<GfPlayComStartChallengeBattle>::sys() != nullptr;
}

}  // namespace gf
