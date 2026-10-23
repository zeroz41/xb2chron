#include "classes/gf/GfGameSalvage.h"
#include "classes/gf/StateSalvageWait.h"
#include "classes/gf/StateSalvageTBoxCheck.h"
#include "classes/gf/StateSalvageErrorMessage.h"
#include "classes/gf/StateSalvageItemSelect.h"
#include "classes/gf/StateSalvageSetupFadeOut.h"
#include "classes/gf/StateSalvageLoad.h"
#include "classes/gf/StateSalvageSetupFadeIn.h"
#include "classes/gf/StateSalvageSkillCheck.h"
#include "classes/gf/StateSalvageStartVoice.h"
#include "classes/gf/StateSalvageDiveStart.h"
#include "classes/gf/StateSalvageDiveWait.h"
#include "classes/gf/StateSalvageDiveEnd.h"
#include "classes/gf/StateSalvageDiveFadeOut.h"
#include "classes/gf/StateSalvageDiveFadeWait.h"
#include "classes/gf/StateSalvageDiveFadeIn.h"
#include "classes/gf/StateSalvageClimbStart.h"
#include "classes/gf/StateSalvageResult.h"
#include "classes/gf/StateSalvageResultUi.h"
#include "classes/gf/StateSalvagePartyFormDelay.h"
#include "classes/gf/StateSalvageCamWait.h"
#include "classes/gf/StateSalvageFinish.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfGameManager.h"

namespace gf {

void GfGameSalvage::initialize(const GfSetupParam& param) {
    m_fsm.beginSetup(this, 21);
    m_fsm.registerState<StateSalvageWait>(0);
    m_fsm.registerState<StateSalvageTBoxCheck>(1);
    m_fsm.registerState<StateSalvageErrorMessage>(2);
    m_fsm.registerState<StateSalvageItemSelect>(3);
    m_fsm.registerState<StateSalvageSetupFadeOut>(4);
    m_fsm.registerState<StateSalvageLoad>(5);
    m_fsm.registerState<StateSalvageSetupFadeIn>(6);
    m_fsm.registerState<StateSalvageSkillCheck>(7);
    m_fsm.registerState<StateSalvageStartVoice>(8);
    m_fsm.registerState<StateSalvageDiveStart>(9);
    m_fsm.registerState<StateSalvageDiveWait>(10);
    m_fsm.registerState<StateSalvageDiveEnd>(11);
    m_fsm.registerState<StateSalvageDiveFadeOut>(12);
    m_fsm.registerState<StateSalvageDiveFadeWait>(13);
    m_fsm.registerState<StateSalvageDiveFadeIn>(14);
    m_fsm.registerState<StateSalvageClimbStart>(15);
    m_fsm.registerState<StateSalvageResult>(16);
    m_fsm.registerState<StateSalvageResultUi>(17);
    m_fsm.registerState<StateSalvagePartyFormDelay>(18);
    m_fsm.registerState<StateSalvageCamWait>(19);
    m_fsm.registerState<StateSalvageFinish>(20);
    m_fsm.endSetup();
    m_fsm.setState(0);
    m_initialized = true;
}

void GfGameSalvage::destroy() {
    GfGameSalvage* salvage = get();
    salvage->finalize();
    delete salvage;
}

void GfGameSalvage::update(const fw::UpdateInfo& info) {
    GfGameSalvage* salvage = get();
    if (salvage != nullptr) {
        salvage->m_fsm.update(&info);
    }
}

void GfGameSalvage::startSalvage(GF_OBJ_HANDLE* handle) {
    get()->m_pHandle = handle;
    if (GfGameManager::getState() == static_cast<GF_STATE>(11) && !GfGameManager::isBattle() && isStateWait()) {
        get()->m_fsm.setState(1);
    }
}

bool GfGameSalvage::isStateWait() {
    return get()->m_fsm.m_pState->m_stateID == 0;
}

void GfGameSalvage::cancelSalvage() {}

// the salvage states' slots: inline (their tables have no key function; initialize's registrations make the states,
// so their tables and slots are emitted here), handing the game and the update to the state's own functions in
// StateSalvageDiveStart's unit
inline const char* StateSalvageWait::getName() const {
    return "StateSalvageWait";
}
inline void StateSalvageWait::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageWait::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageWait::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageTBoxCheck::getName() const {
    return "StateSalvageTBoxCheck";
}
inline void StateSalvageTBoxCheck::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageTBoxCheck::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageTBoxCheck::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageErrorMessage::getName() const {
    return "StateSalvageErrorMessage";
}
inline void StateSalvageErrorMessage::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageErrorMessage::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageErrorMessage::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageItemSelect::getName() const {
    return "StateSalvageItemSelect";
}
inline void StateSalvageItemSelect::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageItemSelect::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageItemSelect::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageSetupFadeOut::getName() const {
    return "StateSalvageSetupFadeOut";
}
inline void StateSalvageSetupFadeOut::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageSetupFadeOut::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageSetupFadeOut::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageLoad::getName() const {
    return "StateSalvageLoad";
}
inline void StateSalvageLoad::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageLoad::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageLoad::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageSetupFadeIn::getName() const {
    return "StateSalvageSetupFadeIn";
}
inline void StateSalvageSetupFadeIn::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageSetupFadeIn::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageSetupFadeIn::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageSkillCheck::getName() const {
    return "StateSalvageSkillCheck";
}
inline void StateSalvageSkillCheck::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageSkillCheck::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageSkillCheck::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageStartVoice::getName() const {
    return "StateSalvageStartVoice";
}
inline void StateSalvageStartVoice::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageStartVoice::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageStartVoice::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageDiveStart::getName() const {
    return "StateSalvageDiveStart";
}
inline void StateSalvageDiveStart::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageDiveStart::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageDiveStart::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageDiveWait::getName() const {
    return "StateSalvageDiveWait";
}
inline void StateSalvageDiveWait::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageDiveWait::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageDiveWait::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageDiveEnd::getName() const {
    return "StateSalvageDiveEnd";
}
inline void StateSalvageDiveEnd::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageDiveEnd::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageDiveEnd::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageDiveFadeOut::getName() const {
    return "StateSalvageDiveFadeOut";
}
inline void StateSalvageDiveFadeOut::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageDiveFadeOut::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageDiveFadeOut::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageDiveFadeWait::getName() const {
    return "StateSalvageDiveFadeWait";
}
inline void StateSalvageDiveFadeWait::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageDiveFadeWait::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageDiveFadeWait::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageDiveFadeIn::getName() const {
    return "StateSalvageDiveFadeIn";
}
inline void StateSalvageDiveFadeIn::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageDiveFadeIn::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageDiveFadeIn::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageClimbStart::getName() const {
    return "StateSalvageClimbStart";
}
inline void StateSalvageClimbStart::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageClimbStart::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageClimbStart::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageResult::getName() const {
    return "StateSalvageResult";
}
inline void StateSalvageResult::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageResult::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageResult::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageResultUi::getName() const {
    return "StateSalvageResultUi";
}
inline void StateSalvageResultUi::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageResultUi::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageResultUi::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvagePartyFormDelay::getName() const {
    return "StateSalvagePartyFormDelay";
}
inline void StateSalvagePartyFormDelay::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvagePartyFormDelay::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvagePartyFormDelay::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageCamWait::getName() const {
    return "StateSalvageCamWait";
}
inline void StateSalvageCamWait::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageCamWait::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageCamWait::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateSalvageFinish::getName() const {
    return "StateSalvageFinish";
}
inline void StateSalvageFinish::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfGameSalvage*>(owner), prev);
}
inline void StateSalvageFinish::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfGameSalvage*>(owner), next);
}
inline void StateSalvageFinish::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameSalvage*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
}  // namespace gf
