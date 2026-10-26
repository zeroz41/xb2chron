#include "classes/apps/FrameworkLauncher.h"
#include "classes/apps/LauncherApp.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/Framework.h"
#include "classes/ml/DevKeyboard.h"
#include "classes/ml/MicroThread.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/WinView.h"
#include "classes/ml/WorkCpu.h"
#include "fw/Allocator.h"
#include "fw/UpdateState.h"

namespace apps {

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
