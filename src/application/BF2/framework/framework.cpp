#include "fw/FrameworkConfig.h"
#include "classes/fw/Framework.h"
#include "classes/fw/TransformManager.h"
#include "classes/fw/SoundLayerManager.h"
#include "classes/ml/DevSettingNx.h"
#include "classes/ml/DevFileTh.h"
#include "mm/mtl/Map.h"
#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/ColiManager.h"
#include "classes/fw/PadManager.h"
#include "classes/fw/LightManager.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include "fw/Reflection.h"
#include "classes/fw/BdatManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/LayerSetManager.h"
#include "classes/fw/NaviManager.h"
#include "classes/fw/ResourceManager.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/UpdatableObjectManager.h"
#include "fw/UpdateState.h"
#include "classes/fw/Framework.h"
#include "classes/fw/IPauseTrigger.h"
#include "classes/ml/WorkCpu.h"
#include "classes/fw/Framework.h"
#include "classes/fw/IPauseTrigger.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ManagerRegister.h"
#include "classes/fw/TransformManager.h"
#include "classes/ml/Thread.h"
#include "classes/ml/WorkCpu.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/AssetManager.h"
#include "classes/fw/DyanmicsManager.h"
#include "classes/fw/MessageManager.h"
#include "classes/fw/ModelManager.h"
#include "classes/fw/MovieManager.h"
#include "classes/fw/ScriptManager.h"
#include "classes/fw/SensorManager.h"
#include "classes/fw/WindManager.h"
#include "classes/ml/DevClock.h"
#include "classes/ml/DevSetting.h"
#include "fw/LangUtil.h"
#include "fw/ObjectEvent.h"
#include "fw/RenderParam.h"
#include "ml/MTRand.h"
#include "ml/MlMem.h"
#include "classes/ml/Scn.h"
#include "math.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw {

Framework::Framework()
    : m_applet(nullptr), pad_50(0), m_scn(nullptr), pad_60(0), m_memHandle(), pad_70(0), m_state(0), pad_88(false),
      pad_89(false), m_updated(false), m_updateSpeed(1.0f) {}

Framework::~Framework() {
    m_postUpdateThread.m_threadExit = true;
    m_postUpdateThread.m_threadEvent.setSignal(true);
    while (!m_postUpdateThread.m_thread->isTerminated()) {
    }
    if (m_postUpdateThread.m_thread != nullptr) {
        m_postUpdateThread.m_thread->release();
        m_postUpdateThread.m_thread = nullptr;
    }
    destroyManager();
}


void Framework::createMemorySection() {
    MemorySectionInfo info;
    info.m_kind = 6;
    info.m_parent = ml::MlMem::getProductMem();
    info.m_size = 0x2600000;
    info.m_alignment = 0x1000;
    info.m_flag = true;
    info.m_name = "fw::SoundCommon";
    info.m_type = mtl::AllocatorType(1);
    FrameworkMemory::getPtr()->createSection(info);
    info.m_kind = 8;
    info.m_parent = ml::MlMem::getProductMem();
    info.m_size = 0x2800000;
    info.m_alignment = 0x1000;
    info.m_flag = true;
    info.m_name = "fw::SoundPool";
    info.m_type = mtl::AllocatorType(1);
    FrameworkMemory::getPtr()->createSection(info);
    info.m_kind = 7;
    info.m_parent = ml::MlMem::getProductMem();
    info.m_size = 0x4900000;
    info.m_alignment = 0x20;
    info.m_flag = true;
    info.m_name = "fw::SoundProc";
    info.m_type = mtl::AllocatorType(1);
    FrameworkMemory::getPtr()->createSection(info);
    info.m_kind = 9;
    info.m_parent = ml::MlMem::getProductMem();
    info.m_size = 0x4400000;
    info.m_alignment = 0x1000;
    info.m_flag = false;
    info.m_name = "fw::Movie";
    info.m_type = mtl::AllocatorType(1);
    FrameworkMemory::getPtr()->createSection(info);
}

void Framework::destroyManager() {
    delete SensorManager::get();
    delete SoundLayerManager::get();
    delete WindManager::get();
    delete ParamManager::get();
    delete MovieManager::get();
    delete EffectManager::get();
    delete ScriptManager::get();
    delete UpdatableObjectManager::get();
    delete MessageManager::get();
    delete ResourceManager::get();
    delete mm::mtl::PtrSingleton<ColiManager>::get();
    delete LayerSetManager::get();
    delete LightManager::get();
    delete DyanmicsManager::get();
    delete AnimationManager::get();
    delete ModelManager::get();
    delete NaviManager::get();
    delete CameraManager::get();
    delete AssetManager::get();
    delete TransformManager::get();
    delete PadManager::get();
    delete BdatManager::get();
    delete SoundManager::get();
    RenderParam::finalize();
    delete ManagerRegister::get();
    get()->m_scn->renderStop();
}

CameraManager::CameraManager(ml::Scn* scn) : m_pViewer(nullptr), m_listener(this) {
    for (unsigned int i = 0; i < 4; i++) {
        m_layers[i].setup(scn, i);
    }
}
bool Framework::initializeManager() {
    UpdateInfo info = UpdateInfo();
    BdatManager::get()->update(info);
    ResourceManager::get()->update(info);
    if (!ManagerRegister::get()->initialize()) {
        return false;
    }
    if (!BdatManager::isEnableBdat(0)) {
        return false;
    }
    if (BdatManager::isEnableBdat(1) && EffectManager::get()->isCommonLoaded() &&
        SoundManager::get()->isCommonLoaded() && SoundManager::get()->isBattleLoaded()) {
        PadManager::initVibData();
        m_state = 2;
        return true;
    }
    return false;
}

bool Framework::finalizeManager() {
    bool finalized = ManagerRegister::get()->finalize();
    m_state = finalized ? 5 : 4;
    return finalized;
}

mm::mtl::IAllocator* Framework::getAllocator() {
    Framework* framework = get();
    return framework == nullptr ? nullptr : &framework->m_allocator;
}

void Framework::prepareEnter() {
    m_state = 3;
}

void Framework::prepareExit() {}

void Framework::activate() {
    for (IPauseTrigger* trigger : m_pauseTriggers) {
        trigger->activate();
    }
}

void Framework::deactivate() {
    for (IPauseTrigger* trigger : m_pauseTriggers) {
        trigger->deactivate();
    }
}

void Framework::beginFrame(const UpdateState& state) {
    if (!state.m_pause) {
        float updateSpeed = m_updateSpeed;
        float speed = m_updateInfo.m_speed;
        if (::fabsf(updateSpeed - speed) > 1e-6f) {
            speed = updateSpeed;
            m_updateInfo.m_frameTime = 1.0f / m_config.m_frameRate;
            m_updateInfo.m_speed = speed;
            m_updateInfo.m_deltaTime = speed * m_updateInfo.m_frameTime;
        }
        for (unsigned int i = 0; i < 32; i++) {
            Layer& layer = m_layers[i];
            layer.m_speed = layer.m_speedRequest;
            layer.m_deltaTime = layer.m_speedRequest * m_updateInfo.m_speed;
            layer.m_pause = layer.m_pauseRequest;
        }
    } else {
        m_updateInfo.m_frameTime = 1.0f / m_config.m_frameRate;
        m_updateInfo.m_speed = 0.0f;
        for (int i = 0; i < 32; i++) {
            m_layers[i].m_deltaTime = 0.0f;
        }
        m_updateInfo.m_deltaTime = m_updateInfo.m_frameTime * m_updateInfo.m_speed;
    }
    if (m_state - 2u < 3) {
        if (SoundManager* sound = SoundManager::get()) {
            sound->update(m_updateInfo);
        }
    }
}

void Framework::endFrame(const UpdateState& state) {}

void Framework::preUpdate() {
    if (m_state - 2u < 3 && m_applet != nullptr) {
        m_applet->preUpdate(m_updateInfo);
    }
}

void Framework::postUpdate() {
    if (m_state - 2u >= 3) {
        return;
    }
    if (m_applet != nullptr) {
        m_applet->postUpdate(m_updateInfo);
    }
    if (!m_postUpdateThread.m_threadFlag) {
        if (ColiManager* coli = mm::mtl::PtrSingleton<ColiManager>::get()) {
            coli->postUpdate();
        }
    }
    PadManager::get()->debugDraw(0x80, 0x80);
}

void Framework::fn_710018369C(const fw::UpdateInfo& info) {
    m_postUpdateThread.m_threadEvent.setSignal(true);
}

void Framework::fn_71001836A8() {
    while (m_postUpdateThread.m_threadEvent.isSignal()) {
    }
}

void Framework::fn_71001836D0(bool flag) {
    m_postUpdateThread.m_threadFlag = flag;
}

void Framework::tail(const UpdateState& state) {
    if (m_state - 2u >= 3) {
        return;
    }
    if (m_applet != nullptr) {
        Framework* framework = get();
        if (framework != nullptr && framework->m_state == 3 && !state.m_pause) {
            m_applet->tail(m_updateInfo);
        }
    }
    if (UpdatableObjectManager* updatable = UpdatableObjectManager::get()) {
        if (!state.m_pause) {
            updatable->tail(m_updateInfo);
        }
    }
    if (ColiManager* coli = mm::mtl::PtrSingleton<ColiManager>::get()) {
        coli->tail();
    }
    if (NaviManager* navi = NaviManager::get()) {
        navi->tail();
    }
    if (LayerSetManager* layerSet = LayerSetManager::get()) {
        layerSet->tail();
    }
    if (EffectManager* effect = EffectManager::get()) {
        effect->tail(m_updateInfo, state.m_pause);
    }
}

void Framework::render() {}

Applet* Framework::getApplet() const {
    return m_applet;
}

bool Framework::isAppletClosed() {
    if (m_applet != nullptr) {
        return m_applet->m_closed;
    }
    return false;
}

void Framework::destroyApplet() {
    if (m_applet != nullptr) {
        m_applet->finalize(*this);
        if (m_applet != nullptr) {
            delete m_applet;
            m_applet = nullptr;
        }
    }
}

void Framework::enterFinalizeApplet() {
    ManagerRegister::get()->enterFinalizeApplet();
}

mtl::ALLOC_HANDLE Framework::getMemHandle() {
    Framework* framework = get();
    if (framework == nullptr) {
        return mtl::ALLOC_HANDLE();
    }
    if (framework->m_memHandle.m_handle == 0) {
        return FrameworkMemory::getMem(5);
    }
    return framework->m_memHandle;
}

void Framework::setUpdateSpeed(float speed) {
    Framework* framework = get();
    if (framework != nullptr) {
        framework->m_updateSpeed = speed;
    }
}

void Framework::setLayerUpdateSpeed(unsigned int layer, float speed) {
    Framework* framework = get();
    if (framework != nullptr) {
        framework->m_layers[layer].m_speedRequest = speed;
    }
}

float Framework::getLayerUpdateSpeed(unsigned int layer) {
    Framework* framework = get();
    if (framework != nullptr) {
        return framework->m_layers[layer].m_speed;
    }
    return 1.0f;
}

void Framework::setLayerPause(unsigned int layer, bool pause) {
    Framework* framework = get();
    if (framework != nullptr) {
        framework->m_layers[layer].m_pauseRequest = pause;
    }
}

bool Framework::isLayerPause(unsigned int layer) {
    Framework* framework = get();
    if (framework != nullptr) {
        return framework->m_layers[layer].m_pause;
    }
    return false;
}

unsigned int Framework::getFrameCount() {
    return ml::WorkCpu::getFrameCount();
}

// the pause triggers' search (the original's find over the vector, as its loop shows)
static inline IPauseTrigger** findPauseTrigger(mm::mtl::FixedVector<IPauseTrigger*, 32>& triggers,
                                               IPauseTrigger* trigger) {
    IPauseTrigger** it = triggers.begin();
    IPauseTrigger** end = triggers.end();
    for (; it != end; ++it) {
        if (*it == trigger) {
            break;
        }
    }
    return it;
}

void Framework::addPauseCallback(IPauseTrigger* trigger) {
    Framework* framework;
    if (trigger != nullptr && (framework = get()) != nullptr) {
        if (findPauseTrigger(framework->m_pauseTriggers, trigger) == framework->m_pauseTriggers.end()) {
            framework->m_pauseTriggers.push_back(trigger);
        }
    }
}

void Framework::removePauseCallback(IPauseTrigger* trigger) {
    Framework* framework = get();
    if (framework != nullptr) {
        IPauseTrigger** it = findPauseTrigger(framework->m_pauseTriggers, trigger);
        if (it != framework->m_pauseTriggers.end()) {
            framework->m_pauseTriggers.erase(it);
        }
    }
}

IPauseTrigger::IPauseTrigger() {
    Framework::addPauseCallback(this);
}

IPauseTrigger::~IPauseTrigger() {
    Framework::removePauseCallback(this);
}

CameraManager::~CameraManager() {
    for (int i = 0; i < 4; i++) {
        m_layers[i].cleanup();
    }
}

void CameraManager::update(const UpdateInfo& info) {
    if (m_target) {
        m_target->update(info);
    }
    for (int i = 0; i < 4; i++) {
        m_layers[i].update(info);
    }
}

void CameraManager::Listener::onWkStandbyLogout() {
    m_owner->m_pViewer = nullptr;
}
}  // namespace fw

template mm::mtl::PtrSingleton<fw::ModelManager>::~PtrSingleton();

template mm::mtl::PtrSingleton<fw::MovieManager>::~PtrSingleton();

namespace fw {

TransformManager::~TransformManager() {}

LightManager::~LightManager() {}

ParamManager::~ParamManager() {}

}  // namespace fw
