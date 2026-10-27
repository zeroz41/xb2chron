#include "classes/gf/GfGameSalvage.h"
#include "classes/gf/GimmickCamera.h"
#include "classes/gmk/GmkSalvage.h"
#include "classes/gf/GfGameEvent.h"
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
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfEvtModelSalvage.h"
#include "classes/gf/SCOM_SALVAGE_VOICE.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComBehaviorSalvage.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/GfGameUtil.h"
#include "classes/fw/PadManager.h"
#include "plugin/Bdat.h"
#include "ml/MTRand.h"
#include "ml/PadVibrationInfo.h"
#include "gf/GfDataBlade.h"

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

GfGameSalvage::~GfGameSalvage() {}

void GfGameSalvage::build(const GfSetupParam& param) {
#line 160
    GfGameSalvage* salvage = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameSalvage();
    salvage->initialize(param);
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

namespace _gfgs {
// a name from one of the file's name tables (the tables stay writable data, as the original's are; the name is not
// the original's)
template <unsigned long N>
inline const char* getName(const char* (&table)[N], unsigned int index) {
    return table[index];
}
}  // namespace _gfgs

// the gimmick cameras' file entries by AnimationType (the name is not the original's)
static const char* s_cameraNames[11] = {
    nullptr,           "salvage_dive_start", "salvage_dive_success", "salvage_dive_great_success",
    "salvage_dive_failure", "salvage_climb00", "salvage_climb01", "salvage_climb02", "salvage_climb03",
    "salvage_climb04", "salvage_climb05",
};

void GfGameSalvage::createCameraDiveStart(const mm::Vec3& pos, float rotY) {
    fw::CameraManager* manager = fw::CameraManager::get();
    m_camDiveStart = GimmickCamera::create(_gfgs::getName(s_cameraNames, 1), pos, rotY);
    static_cast<GimmickCamera*>(m_camDiveStart.get())->setAuto(false);
    manager->m_layers[0].push(m_camDiveStart, 0.0f);
}

void GfGameSalvage::createCameraDive(AnimationType type, const mm::Vec3& pos, float rotY) {
    fw::CameraManager* manager = fw::CameraManager::get();
    m_camDive = GimmickCamera::create(_gfgs::getName(s_cameraNames, type), pos, rotY);
    static_cast<GimmickCamera*>(m_camDive.get())->setAuto(false);
    manager->m_layers[0].push(m_camDive, 0.0f);
}

void GfGameSalvage::createCameraClimb(AnimationType type, const mm::Vec3& pos, float rotY) {
    fw::CameraManager* manager = fw::CameraManager::get();
    m_camClimb = GimmickCamera::create(_gfgs::getName(s_cameraNames, type), pos, rotY);
    static_cast<GimmickCamera*>(m_camClimb.get())->setAuto(false);
    manager->m_layers[0].push(m_camClimb, 0.0f);
}

void GfGameSalvage::createCameraCut01(const mm::Vec3& pos, float rotY) {
    m_camCut01 = GimmickCamera::create("salvage_cut01", pos, rotY);
    static_cast<GimmickCamera*>(m_camCut01.get())->setAuto(false);
}

void GfGameSalvage::destroyCameraDiveStart() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (m_camDiveStart && m_camDiveStart->m_pushed) {
        manager->m_layers[0].pop(m_camDiveStart, 0.0f);
    }
    m_camDiveStart = nullptr;
}

void GfGameSalvage::destroyCameraDive() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (m_camDive && m_camDive->m_pushed) {
        manager->m_layers[0].pop(m_camDive, 0.0f);
    }
    m_camDive = nullptr;
}

void GfGameSalvage::destroyCameraClimb() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (m_camClimb && m_camClimb->m_pushed) {
        manager->m_layers[0].pop(m_camClimb, 0.0f);
    }
    m_camClimb = nullptr;
}

void GfGameSalvage::destroyCameraCut01() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (m_camCut01 && m_camCut01->m_pushed) {
        manager->m_layers[0].pop(m_camCut01, 1.0f);
    }
    m_camCut01 = nullptr;
}

void GfGameSalvage::playCameraDiveStart() {
    if (m_camDiveStart && m_camDiveStart->m_pushed) {
        static_cast<GimmickCamera*>(m_camDiveStart.get())->play();
    }
}

void GfGameSalvage::playCameraDive() {
    if (m_camDive && m_camDive->m_pushed) {
        static_cast<GimmickCamera*>(m_camDive.get())->play();
    }
}

void GfGameSalvage::playCameraClimb() {
    if (m_camClimb && m_camClimb->m_pushed) {
        static_cast<GimmickCamera*>(m_camClimb.get())->play();
    }
}

void GfGameSalvage::playCameraCut01() {
    if (m_camCut01 && !m_camCut01->m_pushed) {
        fw::CameraManager::get()->m_layers[0].push(m_camCut01, 0.0f);
        if (m_camCut01) {
            static_cast<GimmickCamera*>(m_camCut01.get())->play();
        }
    }
}

bool GfGameSalvage::isCameraClimbEnd() {
    if (m_camClimb && m_camClimb->m_pushed) {
        return static_cast<GimmickCamera*>(m_camClimb.get())->isPlayEnd();
    }
    return true;
}

bool GfGameSalvage::isCameraCut01End() {
    if (m_camCut01 && m_camCut01->m_pushed) {
        return static_cast<GimmickCamera*>(m_camCut01.get())->isPlayEnd();
    }
    return true;
}

bool GfGameSalvage::isCameraDive() {
    if (m_camDive && m_camDive->m_pushed) {
        return static_cast<GimmickCamera*>(m_camDive.get())->isLoaded();
    }
    return true;
}

unsigned char* GfGameSalvage::getBindedBdatFp() const {
    return gmk::getBindedGmkInst(get()->m_pHandle)->getBindedBdatFp();
}

unsigned int GfGameSalvage::getBindedBdatId() const {
    return gmk::getBindedGmkInst(get()->m_pHandle)->m_createInfo.m_bdatId;
}

void GfGameSalvage::execPop() {
    static_cast<gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle))->popByRaffleResult();
}

void GfGameSalvage::createModel() {
    if (m_pModel == nullptr) {
        m_pModel = GfGameEvent::createSalvage();
    }
}

void GfGameSalvage::destroyModel() {
    if (m_pModel != nullptr) {
        m_pModel->release();
        m_pModel = nullptr;
    }
}

bool GfGameSalvage::isValidModel() {
    if (m_pModel != nullptr) {
        return m_pModel->isValid();
    }
    return false;
}

// the salvager's animations by AnimationType: an "S..." name is a state, the others commands (the name is not the
// original's)
static const char* s_animationNames[11] = {
    "S_idle", "C_salvage", "C_success", "C_greatsuccess", "C_failure", "C_result_00",
    "C_result_01", "C_result_02", "C_result_03", "C_result_04", "C_result_05",
};

void GfGameSalvage::playAnimation(AnimationType type) {
    if (m_pModel == nullptr) {
        return;
    }
    GfObjAcc acc(m_pModel->m_handle);
    if (acc.m_obj == nullptr) {
        return;
    }
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    GfComAsm* comAsm = obj->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return;
    }
    const char* name = _gfgs::getName(s_animationNames, type);
    if (name[0] == 'S') {
        comAsm->setState(name, AnimLayer(0));
    } else {
        comAsm->execCmd(name, AnimLayer(0));
    }
}

bool GfGameSalvage::isAnimationEnd() const {
    if (m_pModel == nullptr) {
        return true;
    }
    GfObjAcc acc(m_pModel->m_handle);
    if (acc.m_obj == nullptr) {
        return true;
    }
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return true;
    }
    GfComAsm* comAsm = obj->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return true;
    }
    return comAsm->isEnd(AnimLayer(0));
}

void GfGameSalvage::setModelTransform(const mm::Vec3& pos, float rotY) {
    if (m_pModel != nullptr) {
        m_pModel->setTransform(pos, rotY);
    }
}

GfComBehaviorSalvage* GfGameSalvage::getGfComBehaviorSalvage() const {
    if (m_pModel == nullptr) {
        return nullptr;
    }
    GfObjAcc acc(m_pModel->m_handle);
    if (acc.m_obj == nullptr) {
        return nullptr;
    }
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return nullptr;
    }
    return obj->getComponent<GfComBehaviorSalvage>(6);
}




bool GfGameSalvage::isVoiceEnd() {
    if (m_pVoice != nullptr) {
        return SCOM_SALVAGE_VOICE::isPlayEnd(m_pVoice);
    }
    return true;
}

void GfGameSalvage::playDiveVibration() {
    if (m_vibration != 0) {
        fw::PadManager::playVibration(ml::PadVibrationInfo(m_vibration));
    }
}

bool GfGameSalvage::isClimbEnd() {
    if (m_pModel == nullptr) {
        return true;
    }
    GfObjAcc acc(m_pModel->m_handle);
    if (acc.m_obj == nullptr) {
        return true;
    }
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return true;
    }
    GfComAsm* comAsm = obj->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return true;
    }
    return comAsm->isEnd(AnimLayer(0));
}

GfGameSalvage::AnimationType GfGameSalvage::getClimbAnimationType() const {
    return m_climbAnimType;
}

void GfGameSalvage::playWireStart(float time, float param1, float param2) {
    if (m_pModel != nullptr) {
        GfGameUtil::startWireWithClose(m_pModel->m_handle, m_pHandle, time, param1, param2);
    }
}

// whether Kiku's chase runs in Supervia: map 10 with GfDataBlade::fn_7100231884()'s value in 0xFBD..0xFC9 (the name is the
// original's)
bool GfGameSalvage::isChaseKikuInSupervia() {
    if (GfGameManager::getMapID() == 10) {
        unsigned short scenario = GfDataBlade::fn_7100231884();
        if (scenario >= 0xFBD && scenario <= 0xFC9) {
            return true;
        }
    }
    return false;
}

unsigned int GfGameSalvage::getTBoxNum() {
    RaffleRet ret;
    getRaffleResult(ret);
    return ret.m_unk0;
}

void GfGameSalvage::createLog() {}
void GfGameSalvage::setLogSkill(bool success, unsigned int level) {}
void GfGameSalvage::clearLogSkill() {}
void GfGameSalvage::setLogButtonChallenge(int id, int result) {}
void GfGameSalvage::clearLogButtonChallenge() {}
void GfGameSalvage::setLogButtonChallengeResult(int result) {}
void GfGameSalvage::setLogLapsedTime(int time) {}

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
