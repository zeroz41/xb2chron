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
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/fw/SoundManager.h"
#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gmk/GmkForm.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/TGmkFormPc.h"
#include "classes/gmk/TGmkFormPcnpc.h"
#include "classes/gf/GfDataBdat.h"
#include "mm/Mat44.h"
#include "gf/GfDataUtil.h"

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
template <unsigned long N>
inline const char* getName(const char* (&table)[N], int index) {
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

// whether a salvage point within 1 of this one has a treasure box locator (its data's kind 2) whose box is out and
// not yet opened
bool GfGameSalvage::isTboxExist() const {
    const mm::Vec3* pos = gmk::getBindedGmkInst(get()->m_pHandle)->m_pos;
    bool exist = false;
    auto check = [&](const gmk::AGmkBase& gmk) {
        const gmk::GmkSalvage& salvage = static_cast<const gmk::GmkSalvage&>(gmk);
        float dx = salvage.m_pos->x - pos->x;
        float dy = salvage.m_pos->y - pos->y;
        float dz = salvage.m_pos->z - pos->z;
        if (dx * dx + dy * dy + dz * dz > 1.0f) {
            return;
        }
        unsigned int num = salvage.m_tboxLocators.size();
        for (unsigned int i = 0; i < num; i++) {
            const gmk::GmkSalvageLocator* locator = salvage.m_tboxLocators[i];
            if (locator != nullptr && locator->m_createInfo.m_data[0] == 2 &&
                locator->m_gob != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && !locator->m_isAccessed) {
                exist = true;
                break;
            }
        }
    };
    mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GmkSalvage::TYPE, check);
    return exist;
}

unsigned char* GfGameSalvage::getBindedBdatFp() const {
    return gmk::getBindedGmkInst(get()->m_pHandle)->getBindedBdatFp();
}

unsigned int GfGameSalvage::getBindedBdatId() const {
    return gmk::getBindedGmkInst(get()->m_pHandle)->m_createInfo.m_bdatId;
}

bool GfGameSalvage::getEventOrigin(mm::Mat44& mtx) const {
    const gmk::GmkSalvage* salvage = static_cast<const gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle));
    if (salvage->m_eventLocator != nullptr) {
        salvage->m_eventLocator->getMatrix(mtx, true);
        return true;
    }
    return false;
}

bool GfGameSalvage::getEventTbox(mm::Mat44& mtx) const {
    const gmk::GmkSalvage* salvage = static_cast<const gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle));
    const gmk::GmkSalvageLocator* locator = salvage->m_tboxLocators[0];
    if (locator != nullptr) {
        locator->getMatrix(mtx, true);
        return true;
    }
    return false;
}

bool GfGameSalvage::applyPartyForm() const {
    typedef gmk::TGmkFormPcnpc<gmk::GmkType(25)> FormPcnpc;
    typedef gmk::TGmkFormPc<gmk::GmkType(24), FormPcnpc> FormPc;
    const gmk::AGmkBase* formPc =
        static_cast<gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle))->getGmkFormPc();
    if (formPc == nullptr) {
        return false;
    }
    gmk::GmkForm form(nullptr);
    bool applied;
    if (form.create<FormPc, FormPcnpc>(*static_cast<const FormPc*>(formPc))) {
        form.apply(4.0f);
        applied = true;
    } else {
        applied = false;
    }
    form.dispose();
    return applied;
}

// draws the dive's treasures, then disposes the treasure box objects (data kind 2) of every salvage point within 1
// of this one, marking them not accessed
void GfGameSalvage::execRaffle(const RaffleInfo& info) {
    gmk::GmkSalvage* salvage = static_cast<gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle));
    gmk::GmkSalvage::RaffleInfo raffle;
    raffle.m_grade = info.m_grade;
    raffle.m_point = info.m_point;
    raffle.m_skillLevel = info.m_skillLevel;
    salvage->createRaffle(raffle);
    const mm::Vec3* pos = salvage->m_pos;
    auto dispose = [&](const gmk::AGmkBase& gmk) {
        const gmk::GmkSalvage& other = static_cast<const gmk::GmkSalvage&>(gmk);
        float dx = other.m_pos->x - pos->x;
        float dy = other.m_pos->y - pos->y;
        float dz = other.m_pos->z - pos->z;
        if (dx * dx + dy * dy + dz * dz > 1.0f) {
            return;
        }
        unsigned int num = other.m_tboxLocators.size();
        for (unsigned int i = 0; i < num; i++) {
            gmk::GmkSalvageLocator* locator = other.m_tboxLocators[i];
            if (locator != nullptr && locator->m_createInfo.m_data[0] == 2) {
                locator->m_isAccessed = false;
                locator->disposeGobInst(true);
            }
        }
    };
    mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GmkSalvage::TYPE, dispose);
}

void GfGameSalvage::execPop() {
    static_cast<gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle))->popByRaffleResult();
}

bool GfGameSalvage::getRaffleResult(RaffleRet& ret) const {
    const gmk::GmkSalvage* salvage = static_cast<const gmk::GmkSalvage*>(gmk::getBindedGmkInst(get()->m_pHandle));
    const gmk::GmkSalvage::RaffleResult& result = salvage->m_raffleResult;
    ret.m_tboxNum = result.m_tboxDrawn.count();
    ret.m_enemyDrawn = result.m_enemyDrawn.any();
    ret.m_powerfulEnemy = result.isPowerfullEnemyExist();
    unsigned char* fp = GfDataBdat::getFP(0x77);
    ret.m_rank = 0;
    for (int i = 0; i < 3; i++) {
        if (result.m_tboxIds[i] > 0) {
            unsigned int rank = Bdat::getValCheckU16(fp, "RSC_ID", result.m_tboxIds[i]);
            if (ret.m_rank < rank) {
                ret.m_rank = rank;
            }
        }
    }
    return true;
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




// the button challenges' columns in the salvage point's sheet (the name is not the original's)
static const char* s_buttonChallengeColumns[3] = {"BtnChallenge0", "BtnChallenge1", "BtnChallenge2"};

int GfGameSalvage::getButtonChallengeId(int index) {
    unsigned char* fp = getBindedBdatFp();
    unsigned int id = getBindedBdatId();
    return Bdat::getValCheckU16(fp, _gfgs::getName(s_buttonChallengeColumns, index), id);
}

void GfGameSalvage::setPartyDisp(bool disp) {
    int num = GfGameParty::getHierarchyMax();
    for (int i = 0; i < num; i++) {
        GfObjAcc acc(GfGameParty::getHandleByHierarchy(i + 1));
        acc.setAlphaEvent(disp ? 1.0f : 0.0f);
    }
}

void GfGameSalvage::setPartyNpcMove(bool flag) {
    GF_OBJ_HANDLE* mover = GfGameManager::getControlMover();
    bool stop = !flag;
    for (unsigned int i = 0; i < 3; i++) {
        GfObjAcc driver(GfGameParty::getHandleDriver(i, 0));
        GfObjAcc blade(GfGameParty::getHandleBlade(i, -1));
        if (i == 0 && driver.getDriverId() == 2 && blade.getBladeId() == 1004) {
            continue;
        }
        if (driver.getHandle() != mover) {
            GfGameUtil::changeStopLayer(driver.getHandle(), stop);
            GfGameUtil::changeStopLayer(blade.getHandle(), stop);
        }
    }
    GfGameSpeed::setLayerSpeed(1, flag ? 1.0f : 0.0f);
}

void GfGameSalvage::playVoice(VoiceType type) {
    if (m_pModel == nullptr) {
        return;
    }
    GF_OBJ_HANDLE* handle = m_pModel->m_handle;
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    int random = static_cast<int>(ml::mtRand()) % 2;
    int voice;
    switch (type) {
    case 0:
        voice = random;
        break;
    case 1:
        voice = random + 2;
        break;
    case 2:
        voice = random + 4;
        break;
    case 3:
        voice = random + 6;
        break;
    case 4:
        voice = 8;
        break;
    case 5:
        voice = 9;
        break;
    case 6:
        voice = random + 10;
        break;
    default:
        voice = 0;
        break;
    }
    m_pVoice = SCOM_SALVAGE_VOICE::create(handle, CV_SALVAGE(voice));
}

bool GfGameSalvage::isVoiceEnd() {
    if (m_pVoice != nullptr) {
        return SCOM_SALVAGE_VOICE::isPlayEnd(m_pVoice);
    }
    return true;
}

namespace _gfgs {
// how many entries of a row of calcClimb's tables come before its first -1 (the row goes to the helper by reference:
// the tables stay writable data, as the original's are; the name is not the original's)
template <unsigned long N>
inline unsigned long getNum(const int (&row)[N]) {
    unsigned long num = 0;
    for (int v : row) {
        if (v == -1) {
            break;
        }
        num++;
    }
    return num;
}
// an entry of a row of calcClimb's tables (the name is not the original's)
template <unsigned long N>
inline int getAt(const int (&row)[N], unsigned long index) {
    return row[index];
}
}  // namespace _gfgs

namespace _gfgs {
// calcClimb's tables, one object (lbl_7100B575D0; the type and field names are not the original's): the climb's kind
// (1-9) by the raffle's rank (RSC_ID 4-6, else row 0) and enemy (none, an enemy, a powerful one), then for each kind
// the climb animations (AnimationType), the vibrations and the result voices (CV_SALVAGE_RESULT) to draw from
struct ClimbTable {
    int m_types[4][3];
    int m_animations[9][3];
    int m_vibrations[9][4];
    int m_results[9][5];
};
}  // namespace _gfgs

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B575D0)
static _gfgs::ClimbTable s_climbTable = {
    {{1, 5, 9}, {2, 6, 9}, {3, 7, 9}, {4, 8, 9}},
    {{5, 6, 7}, {5, 6, 7}, {7, 8, 9}, {8, 9, -1}, {5, 6, 7}, {5, 6, 7}, {7, 8, 9}, {8, 9, -1}, {10, -1, -1}},
    {{4, -1, -1, -1}, {4, 5, -1, -1}, {4, 18, -1, -1}, {4, 19, -1, -1}, {20, 4, -1, -1}, {20, 5, -1, -1},
     {20, 18, -1, -1}, {20, 19, -1, -1}, {6, 18, 19, 5}},
    {{0, 1, 10, -1, -1}, {3, 4, 10, -1, -1}, {2, 3, 9, 10, -1}, {4, 5, 9, -1, -1}, {0, 1, 6, 10, -1},
     {3, 4, 6, 10, -1}, {2, 3, 6, 9, 10}, {4, 5, 6, 9, -1}, {7, 8, -1, -1, -1}},
};

void GfGameSalvage::calcClimb() {
    RaffleRet ret;
    getRaffleResult(ret);
    unsigned long rank;
    switch (ret.m_rank) {
    case 4:
        rank = 1;
        break;
    case 5:
        rank = 2;
        break;
    case 6:
        rank = 3;
        break;
    default:
        rank = 0;
        break;
    }
    unsigned long enemy;
    if (ret.m_powerfulEnemy) {
        enemy = 2;
    } else {
        enemy = ret.m_enemyDrawn;
    }
    unsigned int type = _gfgs::getAt(s_climbTable.m_types[rank], enemy) - 1;
    unsigned long num = _gfgs::getNum(s_climbTable.m_animations[type]);
    unsigned int index = static_cast<int>(ml::mtRand()) % num;
    m_climbAnimType = AnimationType(_gfgs::getAt(s_climbTable.m_animations[type], index));
    num = _gfgs::getNum(s_climbTable.m_results[type]);
    index = static_cast<int>(ml::mtRand()) % num;
    m_climbResult = _gfgs::getAt(s_climbTable.m_results[type], index);
    // the original draws the vibration's entry by the vibrations' count but reads it from the result voices' row
    num = _gfgs::getNum(s_climbTable.m_vibrations[type]);
    index = static_cast<int>(ml::mtRand()) % num;
    m_vibration = _gfgs::getAt(s_climbTable.m_results[type], index);
}

void GfGameSalvage::playDiveVibration() {
    if (m_vibration != 0) {
        fw::PadManager::playVibration(ml::PadVibrationInfo(m_vibration));
    }
}

void GfGameSalvage::playClimbReady() {
    if (m_pModel == nullptr || m_pModel->m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    playAnimation(m_climbAnimType);
    GfGameSpeed::setSalvageCharacterSpeed(0.01f);
}

void GfGameSalvage::playClimb() {
    if (m_pModel == nullptr) {
        return;
    }
    GF_OBJ_HANDLE* handle = m_pModel->m_handle;
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfGameSpeed::setSalvageCharacterSpeed(1.0f);
    SCOM_SALVAGE_VOICE::createResult(handle, CV_SALVAGE_RESULT(m_climbResult));
    playSE(SEID(m_climbAnimType + 600));
}

void GfGameSalvage::playSE(SEID id) {
    fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get();
    if (sound == nullptr) {
        return;
    }
    GfFieldSound* fieldSound = mm::mtl::PtrSingleton<GfFieldSound>::get();
    if (fieldSound == nullptr) {
        return;
    }
    sound->playSe(id, fieldSound->getCommonPack(), 1.0f, fw::SoundCategory(0));
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

void GfGameSalvage::addSalvagerPoint(unsigned int point) {
    if (point == 0) {
        return;
    }
    unsigned int value = GfGameFlag::getLocal(8, 0x854);
    if (value < 0xFF) {
        value += point;
        GfGameFlag::setLocal(8, 0x854, value > 0xFF ? 0xFF : value);
    }
}

// whether Kiku's chase runs in Supervia: map 10 with GfDataUtil::getScenarioFlag()'s value in 0xFBD..0xFC9 (the name is the
// original's)
bool GfGameSalvage::isChaseKikuInSupervia() {
    if (GfGameManager::getMapID() == 10) {
        unsigned short scenario = GfDataUtil::getScenarioFlag();
        if (scenario >= 0xFBD && scenario <= 0xFC9) {
            return true;
        }
    }
    return false;
}

unsigned int GfGameSalvage::getTBoxNum() {
    RaffleRet ret;
    getRaffleResult(ret);
    return ret.m_tboxNum;
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
