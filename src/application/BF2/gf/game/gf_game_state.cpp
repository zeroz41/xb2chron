// the game's state machine and its states (the states' slots are inline: their tables have no key function, so
// GfGameState::build, whose registrations make them, emits their tables and slots here)

#include "classes/gf/GfGameState.h"
#include "classes/gf/StateGfInitialize.h"
#include "classes/gf/StateGfDestroy.h"
#include "classes/gf/StateControl.h"
#include "classes/gf/StateMapjump.h"
#include "classes/gf/StatePlayerDead.h"
#include "classes/gf/StateMenu.h"
#include "classes/gf/StateWaitEvent.h"
#include "classes/gf/StateSalvage.h"
#include "classes/gf/StateCollect.h"
#include "classes/gf/StateFieldTbox.h"
#include "classes/gf/StateMapGimmick.h"
#include "classes/gf/StateGrave.h"
#include "classes/gf/StateJump.h"
#include "classes/gf/StateWarp.h"
#include "classes/gf/StateGmkTutorial.h"
#include "classes/gf/StateGmkCamera.h"
#include "classes/gf/StateEvent.h"
#include "classes/gf/StateTalk.h"
#include "classes/gf/StateGimmickTask.h"
#include "classes/gf/StateChainAttack.h"
#include "classes/gf/StateArtsMovie.h"
#include "classes/gf/StateResetBlade.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameEnv.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfInfo.h"
#include "fw/UpdateInfo.h"
#include "mm/Vec3.h"

namespace gf {

GfGameState::~GfGameState() {}

void GfGameState::build(const GfSetupParam& param) {
#line 434
    GfGameState* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameState();
    self->m_fsm.beginSetup(self, 25);
    self->m_fsm.registerState<StateGfInitialize>(1);
    self->m_fsm.registerState<StateGfDestroy>(2);
    self->m_fsm.registerState<StateControl>(3);
    self->m_fsm.registerState<StateMapjump>(8);
    self->m_fsm.registerState<StateMapjump>(9);
    self->m_fsm.registerState<StatePlayerDead>(10);
    self->m_fsm.registerState<StateMenu>(6);
    self->m_fsm.registerState<StateWaitEvent>(7);
    self->m_fsm.registerState<StateSalvage>(11);
    self->m_fsm.registerState<StateCollect>(12);
    self->m_fsm.registerState<StateFieldTbox>(13);
    self->m_fsm.registerState<StateMapGimmick>(14);
    self->m_fsm.registerState<StateGrave>(15);
    self->m_fsm.registerState<StateJump>(16);
    self->m_fsm.registerState<StateWarp>(17);
    self->m_fsm.registerState<StateGmkTutorial>(18);
    self->m_fsm.registerState<StateGmkCamera>(19);
    self->m_fsm.registerState<StateEvent>(20);
    self->m_fsm.registerState<StateTalk>(4);
    self->m_fsm.registerState<StateGimmickTask>(21);
    self->m_fsm.registerState<StateChainAttack>(22);
    self->m_fsm.registerState<StateArtsMovie>(23);
    self->m_fsm.registerState<StateResetBlade>(24);
    self->m_fsm.endSetup();
    self->m_fsm.setState(1);
}

void GfGameState::destroy() {
    GfGameState* self = get();
    self->m_fsm.cleanup();
    delete self;
}

void GfGameState::update(const fw::UpdateInfo& info) {
    GfGameState* self = get();
    if (self != nullptr) {
        self->m_stateTime += info.m_deltaTime;
        self->m_fsm.update(&info);
    }
}

void GfGameState::clear() {
    if (get() != nullptr) {
        get()->m_stateTime = 0.0f;
    }
}

bool GfGameState::test(unsigned int flags) {
    return (get()->m_stateFlags & flags) != 0;
}

GF_STATE GfGameState::getState() {
    return static_cast<GF_STATE>(get()->m_fsm.m_pState->m_stateID);
}

GF_STATE GfGameState::getStateReserve() {
    return get()->m_stateReserve;
}

void GfGameState::setStateReserve(GF_STATE state) {
    if (state != 0) {
        GfGameState* self = get();
        self->m_stateReserve = state;
        self->m_reserveFrame = GfInfo::getFrameCount32();
    }
}

void GfGameState::setState(GF_STATE state, bool keepReserve) {
    GfGameState* self = get();
    if (!keepReserve) {
        self->m_stateReserve = static_cast<GF_STATE>(3);
        self->m_reserveFrame = GfInfo::getFrameCount32();
    }
    self->m_fsm.setState(state);
    self->m_stateTime = 0.0f;
}

inline const char* StateGfInitialize::getName() const {
    return "StateGfInitialize";
}
inline void StateGfInitialize::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0;
}
inline void StateGfInitialize::onLeave(void* owner, ai::State* next) {}
inline void StateGfInitialize::onStep(void* owner, const void* arg) {}

inline const char* StateGfDestroy::getName() const {
    return "StateGfDestroy";
}
inline void StateGfDestroy::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0;
    GfEvent::callGameState(static_cast<GF_STATE>(prev->m_stateID), static_cast<GF_STATE>(m_stateID));
}
inline void StateGfDestroy::onLeave(void* owner, ai::State* next) {}
inline void StateGfDestroy::onStep(void* owner, const void* arg) {}

inline const char* StateControl::getName() const {
    return "StateControl";
}
inline void StateControl::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 1;
    GfGameUtil::execDevelopLevelUp();
    GfEvent::callGameState(static_cast<GF_STATE>(prev->m_stateID), static_cast<GF_STATE>(m_stateID));
}
inline void StateControl::onLeave(void* owner, ai::State* next) {}
inline void StateControl::onStep(void* owner, const void* arg) {
    GfComTransform* transform = GfGameParty::getLeaderTransform();
    if (transform != nullptr) {
        GfGameEnv::sendPlayerPositionToRender(transform->getPosition());
    }
}

inline const char* StateMapjump::getName() const {
    return "StateMapjump";
}
inline void StateMapjump::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 4;
}
inline void StateMapjump::onLeave(void* owner, ai::State* next) {}
inline void StateMapjump::onStep(void* owner, const void* arg) {}

inline const char* StatePlayerDead::getName() const {
    return "StatePlayerDead";
}
inline void StatePlayerDead::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0;
}
inline void StatePlayerDead::onLeave(void* owner, ai::State* next) {
    GfGameState::get()->m_stateFlags = 0;
}
inline void StatePlayerDead::onStep(void* owner, const void* arg) {}

inline const char* StateMenu::getName() const {
    return "StateMenu";
}
inline void StateMenu::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 9;
}
inline void StateMenu::onLeave(void* owner, ai::State* next) {}
inline void StateMenu::onStep(void* owner, const void* arg) {}

inline const char* StateWaitEvent::getName() const {
    return "StateWaitEvent";
}
inline void StateWaitEvent::onEnter(void* owner, ai::State* prev) {}
inline void StateWaitEvent::onLeave(void* owner, ai::State* next) {}
inline void StateWaitEvent::onStep(void* owner, const void* arg) {}

inline const char* StateSalvage::getName() const {
    return "StateSalvage";
}
inline void StateSalvage::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0;
}
inline void StateSalvage::onLeave(void* owner, ai::State* next) {}
inline void StateSalvage::onStep(void* owner, const void* arg) {}

inline const char* StateCollect::getName() const {
    return "StateCollect";
}
inline void StateCollect::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x41;
}
inline void StateCollect::onLeave(void* owner, ai::State* next) {}
inline void StateCollect::onStep(void* owner, const void* arg) {}

inline const char* StateFieldTbox::getName() const {
    return "StateFieldTbox";
}
inline void StateFieldTbox::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x81;
}
inline void StateFieldTbox::onLeave(void* owner, ai::State* next) {}
inline void StateFieldTbox::onStep(void* owner, const void* arg) {}

inline const char* StateMapGimmick::getName() const {
    return "StateMapGimmick";
}
inline void StateMapGimmick::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x201;
}
inline void StateMapGimmick::onLeave(void* owner, ai::State* next) {}
inline void StateMapGimmick::onStep(void* owner, const void* arg) {}

inline const char* StateGrave::getName() const {
    return "StateGrave";
}
inline void StateGrave::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x201;
}
inline void StateGrave::onLeave(void* owner, ai::State* next) {}
inline void StateGrave::onStep(void* owner, const void* arg) {}

inline const char* StateJump::getName() const {
    return "StateJump";
}
inline void StateJump::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x401;
}
inline void StateJump::onLeave(void* owner, ai::State* next) {}
inline void StateJump::onStep(void* owner, const void* arg) {}

inline const char* StateWarp::getName() const {
    return "StateWarp";
}
inline void StateWarp::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x801;
}
inline void StateWarp::onLeave(void* owner, ai::State* next) {}
inline void StateWarp::onStep(void* owner, const void* arg) {}

inline const char* StateGmkTutorial::getName() const {
    return "StateGmkTutorial";
}
inline void StateGmkTutorial::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x2001;
}
inline void StateGmkTutorial::onLeave(void* owner, ai::State* next) {}
inline void StateGmkTutorial::onStep(void* owner, const void* arg) {}

inline const char* StateGmkCamera::getName() const {
    return "StateGmkCamera";
}
inline void StateGmkCamera::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x4001;
}
inline void StateGmkCamera::onLeave(void* owner, ai::State* next) {}
inline void StateGmkCamera::onStep(void* owner, const void* arg) {}

inline const char* StateEvent::getName() const {
    return "StateEvent";
}
inline void StateEvent::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 2;
    GfEvent::callGameState(static_cast<GF_STATE>(prev->m_stateID), static_cast<GF_STATE>(m_stateID));
}
inline void StateEvent::onLeave(void* owner, ai::State* next) {}
inline void StateEvent::onStep(void* owner, const void* arg) {}

inline const char* StateTalk::getName() const {
    return "StateTalk";
}
inline void StateTalk::onEnter(void* owner, ai::State* prev) {
    GfGameState::get()->m_stateFlags = 0x21;
    GfEvent::callGameState(static_cast<GF_STATE>(prev->m_stateID), static_cast<GF_STATE>(m_stateID));
}
inline void StateTalk::onLeave(void* owner, ai::State* next) {}
inline void StateTalk::onStep(void* owner, const void* arg) {}

inline const char* StateGimmickTask::getName() const {
    return "StateGimmickTask";
}
inline void StateGimmickTask::onEnter(void* owner, ai::State* prev) {
    GfGameManager::enterBattle(false);
}
inline void StateGimmickTask::onLeave(void* owner, ai::State* next) {}
inline void StateGimmickTask::onStep(void* owner, const void* arg) {}

inline const char* StateChainAttack::getName() const {
    return "StateChainAttack";
}
inline void StateChainAttack::onEnter(void* owner, ai::State* prev) {}
inline void StateChainAttack::onLeave(void* owner, ai::State* next) {}
inline void StateChainAttack::onStep(void* owner, const void* arg) {}

inline const char* StateArtsMovie::getName() const {
    return "StateArtsMovie";
}
inline void StateArtsMovie::onEnter(void* owner, ai::State* prev) {}
inline void StateArtsMovie::onLeave(void* owner, ai::State* next) {}
inline void StateArtsMovie::onStep(void* owner, const void* arg) {}

inline const char* StateResetBlade::getName() const {
    return "StateResetBlade";
}
inline void StateResetBlade::onEnter(void* owner, ai::State* prev) {}
inline void StateResetBlade::onLeave(void* owner, ai::State* next) {}
inline void StateResetBlade::onStep(void* owner, const void* arg) {}

}  // namespace gf
