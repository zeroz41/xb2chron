#include "classes/apps/FrameworkLauncher.h"
#include "classes/apps/LauncherApp.h"
#include "classes/fw/Applet.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/Framework.h"
#include "classes/fw/ResourceManager.h"
#include "classes/ml/DevKeyboard.h"
#include "classes/ml/MicroThread.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/WinProc.h"
#include "classes/ml/WinView.h"
#include "classes/ml/WorkCpu.h"
#include "fw/Allocator.h"
#include "fw/UpdateState.h"
#include "ml/WorkRootState.h"
#include "ml/WorkUtil.h"

namespace apps {

FrameworkLauncher::FrameworkLauncher(const char* name, ml::WorkObj* parent)
    : WorkObj(name, parent, 1), m_request(0), m_procWid(-1), m_updateGroup(reinterpret_cast<ml::MLTHG*>(-1)),
      m_tailGroup(reinterpret_cast<ml::MLTHG*>(-1)),
      m_threads{reinterpret_cast<ml::MLTH*>(-1), reinterpret_cast<ml::MLTH*>(-1), reinterpret_cast<ml::MLTH*>(-1),
                reinterpret_cast<ml::MLTH*>(-1)},
      m_onTerminated(nullptr), m_scn(nullptr), m_view(nullptr),
      m_homeMenu(false), m_debugPauseStepOk(false), m_debugPause(false) {
    m_updateGroup = ml::MicroThread::sys()->createGroup();
    m_tailGroup = ml::MicroThread::sys()->createGroup();
    wkSetEvent(EVT(4));
    m_flags |= 0x800;
    ml::WorkCpu::addBackgroundListener(this);
}

FrameworkLauncher::~FrameworkLauncher() {
    ml::WorkCpu::removeBackgroundListener(this);
    if (m_updateGroup != reinterpret_cast<ml::MLTHG*>(-1)) {
        ml::MicroThread::sys()->releaseGroup(m_updateGroup);
        m_updateGroup = reinterpret_cast<ml::MLTHG*>(-1);
    }
    if (m_tailGroup != reinterpret_cast<ml::MLTHG*>(-1)) {
        ml::MicroThread::sys()->releaseGroup(m_tailGroup);
        m_tailGroup = reinterpret_cast<ml::MLTHG*>(-1);
    }
    fw::Allocator::setSysMemHandle(mtl::ALLOC_HANDLE());
    fw::Allocator::setDebMemHandle(mtl::ALLOC_HANDLE());
    fw::Allocator::setProcMemHandle(mtl::ALLOC_HANDLE());
    if (m_request & 0x40000000) {
        const AppletCreateParam& param = m_appletParam;
        LauncherApp* app = static_cast<LauncherApp*>(m_parent);
        bool stopped = (app->m_flags & 1) | app->m_updateStop;
        if (!stopped && !app->m_appletPending) {
            app->m_appletParam = param;
            app->m_appletPending = true;
            app->wkSetEvent(EVT(0));
        }
    }
}

bool FrameworkLauncher::createBuildThread(ml::WinProc* proc, SceneBuildInfo& info, const fw::FrameworkConfig& config,
                                          void (*onBuilt)(), void (*onTerminated)()) {
    FrameworkLauncher* launcher = sys();
    if (launcher == nullptr) {
        launcher = ml::WorkUtil::createWork<FrameworkLauncher>("FrameworkLauncher", proc, false);
        launcher->m_procWid = proc->m_wid;
        launcher->m_config = config;
        launcher->m_buildInfo = info;
        launcher->m_onBuilt = onBuilt;
        launcher->m_onTerminated = onTerminated;
    } else if (launcher->m_procWid != proc->m_wid) {
        return false;
    }
    if (!(launcher->m_request & 1)) {
        launcher->m_request |= 1;
        launcher->m_threads[1] = ml::MicroThread::sys()->createThread(launcher->m_updateGroup, mlthFnBuild, launcher);
    }
    return (launcher->m_request >> 1) & 1;
}

ml::Scn* FrameworkLauncher::getScn() {
    if (sys() == nullptr) {
        return nullptr;
    }
    return sys()->m_scn;
}

ml::WinView* FrameworkLauncher::getView() {
    if (sys() == nullptr) {
        return nullptr;
    }
    return sys()->m_view;
}

bool FrameworkLauncher::destroy() {
    FrameworkLauncher* launcher = sys();
    if (launcher == nullptr) {
        return true;
    }
    if (launcher->m_threads[0] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[1] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[2] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[3] == reinterpret_cast<ml::MLTH*>(-1) && !(launcher->m_request & 0x10)) {
        launcher->m_request |= 0x20000000;
        launcher->m_threads[0] =
            ml::MicroThread::sys()->createThread(launcher->m_tailGroup, mlthFnTermUpdate, launcher);
    }
    if (launcher->m_request & 0x10) {
        ml::DevKeyboard::clearKey();
        return true;
    }
    return false;
}

bool FrameworkLauncher::createWaitLoadResourceThread() {
    FrameworkLauncher* launcher = sys();
    if (launcher == nullptr) {
        return true;
    }
    if (launcher->m_threads[3] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[2] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[1] == reinterpret_cast<ml::MLTH*>(-1) && !(launcher->m_request & 0x800)) {
        launcher->m_threads[3] =
            ml::MicroThread::sys()->createThread(launcher->m_updateGroup, mlthFnLoadResource, launcher);
    }
    return (launcher->m_request >> 11) & 1;
}

nn::os::FiberType* FrameworkLauncher::mlthFnLoadResource(void*) {
    FrameworkLauncher* launcher = sys();
    if (fw::Framework::sys() != nullptr) {
        fw::Applet* applet = fw::Framework::sys()->getApplet();
        fw::Framework* framework = fw::Framework::sys();
        if (applet != nullptr && framework != nullptr) {
            applet->initializeResource(*framework);
        }
    }
    fw::ResourceManager* resource = fw::ResourceManager::sys();
    if (resource != nullptr) {
        while (!resource->isLoaded()) {
            ml::MicroThread::sys()->sleep(0, true);
        }
    }
    launcher->m_request |= 0x800;
    launcher->m_threads[3] = reinterpret_cast<ml::MLTH*>(-1);
    ml::MicroThread::sys()->exit();
    return nullptr;
}

bool FrameworkLauncher::createAppletInitializeThread() {
    FrameworkLauncher* launcher = sys();
    if (launcher == nullptr) {
        return true;
    }
    if (launcher->m_threads[2] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[3] == reinterpret_cast<ml::MLTH*>(-1) &&
        launcher->m_threads[1] == reinterpret_cast<ml::MLTH*>(-1) && !(launcher->m_request & 0x400)) {
        launcher->m_threads[2] =
            ml::MicroThread::sys()->createThread(launcher->m_updateGroup, mlthFnAppletInitialize, launcher);
    }
    return (launcher->m_request >> 10) & 1;
}

nn::os::FiberType* FrameworkLauncher::mlthFnAppletInitialize(void*) {
    FrameworkLauncher* launcher = sys();
    if (fw::Framework::sys() != nullptr) {
        fw::Applet* applet = fw::Framework::sys()->getApplet();
        fw::Framework* framework = fw::Framework::sys();
        if (applet != nullptr && framework != nullptr) {
            applet->initialize(*framework);
            while (!fw::Framework::sys()->getApplet()->isInitialized()) {
                ml::MicroThread::sys()->sleep(0, true);
            }
            fw::Framework::sys()->getApplet()->enter();
            fw::Framework::sys()->prepareEnter();
        }
    }
    launcher->m_request |= 0x400;
    launcher->m_threads[2] = reinterpret_cast<ml::MLTH*>(-1);
    ml::MicroThread::sys()->exit();
    return nullptr;
}

void FrameworkLauncher::wkUpdate() {
    if (m_homeMenu) {
        return;
    }
    update();
    ml::MicroThread::sys()->update(m_updateGroup);
}

void FrameworkLauncher::wkTail() {
    if (m_homeMenu) {
        return;
    }
    fw::UpdateState state;
    state.m_pause = m_debugPause;
    if (fw::Framework::sys() != nullptr && !(m_request & 0x90)) {
        fw::Framework::sys()->tail(state);
    }
    if (ml::Scn* scn = getScn()) {
        scn->tail();
    }
    ml::MicroThread::sys()->update(m_tailGroup);
}

void FrameworkLauncher::cbRenderAfter(ml::Scn*, ml::SCNPRIO_CB prio) {
    ml::WinView* view = ml::WinView::getView(true);
    ml::WinView* launcherView = getView();
    if (prio != ml::SCNPRIO_CB(0x13) && view == launcherView && fw::Framework::sys() != nullptr) {
        fw::Framework::sys()->render();
    }
}

void FrameworkLauncher::drawTask() {
    if (sys() == nullptr) {
        return;
    }
    if (ml::WinView::getView(true) == getView()) {
        if (ml::Scn* scn = getScn()) {
            scn->draw();
        }
    }
}

bool FrameworkLauncher::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool FrameworkLauncher::wkStandbyLogout() {
    if (m_child.size() != 0) {
        return false;
    }
    if (destroy() && (m_request & 0x10)) {
        return WorkObj::wkStandbyLogout();
    }
    return false;
}

void FrameworkLauncher::rdkReaded(const char*, void*, int) {}

void FrameworkLauncher::bkgHomeMenu(bool on) {
    if (m_homeMenu != on) {
        m_homeMenu = on;
        setDebugPause(on);
    }
    if (fw::Framework* framework = fw::Framework::sys()) {
        if (on) {
            framework->deactivate();
        } else {
            framework->activate();
        }
    }
}

void FrameworkLauncher::setDebugPause(bool pause) {
    if (ml::Scn* scn = mm::mtl::PtrSingleton<ml::Scn>::sys()) {
        if (scn->m_renderDrSys != nullptr) {
            scn->m_renderDrSys->setMdlDblPause(pause);
        }
    }
    fw::EffectManager::sys()->setMasterPause(pause);
}

bool FrameworkLauncher::isDebugPause() const { return m_debugPause; }

void FrameworkLauncher::stepDebugPause() {
    if (m_debugPauseStepOk) {
        m_request |= 0x200000;
    }
}

bool FrameworkLauncher::resetApp() {
    if (m_request & 0x70000000) {
        return false;
    }
    m_request |= 0x50000000;
    return true;
}

}  // namespace apps
