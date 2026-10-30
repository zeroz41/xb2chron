#include "classes/apps/FrameworkLauncher.h"
#include "classes/apps/LauncherApp.h"
#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "classes/ml/ProcDesktop.h"
#include "classes/ml/WinView.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ai/AiData.h"
#include "btl/Utility.h"
#include "classes/gf/GfGameParty.h"
#include "classes/btl/BattleGlobal.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "fw/Transform.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "mm/mtl/RTTI.h"

namespace apps {

LauncherApp::LauncherApp(const char* name, ml::WorkObj* parent, int childCapacity)
    : WinProc(name, parent, childCapacity), m_debugInfo(true), m_appletPending(false) {
    ml::WorkCpu::registErrorCB(this);
    m_flags |= 0x800;
}

LauncherApp::~LauncherApp() {
    destroyMenu();
    destroyDebugDraw();
    ml::WorkCpu::unregistErrorCB(this);
    if (m_appletPending) {
        m_appletPending = false;
        ml::ProcDesktop::executeSelectApp();
    }
}

void LauncherApp::wkUpdate() {}

void LauncherApp::wkRender() {
    if (ml::WinView::getView(true) != FrameworkLauncher::getView()) {
        return;
    }
    FrameworkLauncher::drawTask();
    if (m_debugInfo) {
        for (DebugDraw** it = m_debugDraws.begin(); it != m_debugDraws.end(); ++it) {
            (*it)->draw(this, FrameworkLauncher::getScn(), FrameworkLauncher::getView());
        }
    }
}

void LauncherApp::wkTail() {}

bool LauncherApp::wkStandbyLogout() {
    if (!FrameworkLauncher::destroy() || m_child.size() != 0) {
        return false;
    }
    return WinProc::wkStandbyLogout();
}

bool LauncherApp::OnMouseButtonDown(ml::EventView*) { return false; }

bool LauncherApp::OnFMenuSelect(ml::EventFloatingMenu*) { return false; }

bool LauncherApp::OnKeyDown(ml::EventView*) { return false; }

bool LauncherApp::OnCButtonSelect(ml::EventButton*) { return false; }

bool LauncherApp::OnFileEvent(ml::EventFileTh* event) {
    if (event == nullptr) {
        return false;
    }
    // the applet first, then each menu until one handles it
    bool handled = false;
    if (fw::Framework::sys() != nullptr) {
        if (fw::Applet* applet = fw::Framework::sys()->getApplet()) {
            handled = applet->OnFileEvent(event);
        }
    }
    if (!handled && !m_menus.empty()) {
        for (ml::IWorkEvent** it = m_menus.begin(); !handled && it != m_menus.end(); ++it) {
            handled = (*it)->OnFileEvent(event);
        }
    }
    return handled;
}

void LauncherApp::OnPauseTrigger(bool pause, const char* name) {
    if (fw::Framework::sys() != nullptr) {
        if (fw::Applet* applet = fw::Framework::sys()->getApplet()) {
            applet->OnPauseTrigger(pause, name);
        }
    }
}

void LauncherApp::OnSystemPause(unsigned int pause) {
    if (fw::Framework::sys() != nullptr) {
        if (fw::Applet* applet = fw::Framework::sys()->getApplet()) {
            applet->OnSystemPause(pause);
        }
    }
}

void LauncherApp::OnShutdownForce() {
    if (fw::Framework::sys() != nullptr) {
        if (fw::Applet* applet = fw::Framework::sys()->getApplet()) {
            applet->OnShutdownForce();
        }
    }
}

void LauncherApp::OnViewResize(ml::EventView* event) {
    if (fw::Framework::sys() != nullptr) {
        if (fw::Applet* applet = fw::Framework::sys()->getApplet()) {
            applet->OnViewResize(event);
        }
    }
}

void LauncherApp::errcbCallback(ml::CPUID, unsigned long) {}

}  // namespace apps
namespace ai {

static gf::GF_OBJ_HANDLE* const INVALID_HANDLE = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);

AiData::AiData() : m_handle(INVALID_HANDLE), m_id(-1), m_invalid(false), m_frameCount(0.0f) {
    for (int i = 0; i < 16; i++) {
        m_params[i] = 0;
    }
}

AiData::~AiData() {}

void AiData::init() {}

void AiData::update(const fw::UpdateInfo&) {
    if (m_frameCount > 0.0f && m_handle != INVALID_HANDLE &&
        !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(1), 0)) {
        m_frameCount = m_frameCount - 1.0f;
    }
}

gf::GF_OBJ_HANDLE* AiData::getHandle() const { return m_handle; }

void AiData::setHandle(gf::GF_OBJ_HANDLE* handle) { m_handle = handle; }

gf::GF_OBJ_HANDLE* AiData::getHandleTarget() const {
    if (m_handle == INVALID_HANDLE) {
        return INVALID_HANDLE;
    }
    return btl::Utility::AI_GetCharacterHandle(btl::Utility::AI_GetTargetCharacterID(m_handle));
}

int AiData::getId() const { return m_id; }

void AiData::setId(int id) { m_id = id; }

bool AiData::isValid() const {
    if (m_invalid || m_handle == INVALID_HANDLE) {
        return false;
    }
    if (!btl::BattleGlobal::sys()->fn_710000A6CC() && gf::GfGameParty::isLeaderDriver(m_handle)) {
        return false;
    }
    gf::GfObjAcc acc(m_handle);
    if (!acc.isBattle()) {
        return false;
    }
    return !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(1), 0) &&
           !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(3), 0) &&
           !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(4), 0) &&
           !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(5), 0) &&
           !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(7), 0) &&
           !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(8), 0) &&
           !btl::Utility::AI_CheckState(m_handle, static_cast<btl::Utility::CHECK_STATE>(9), 0);
}

int AiData::getParam(int index) const { return m_params[index]; }

void AiData::setParam(int index, int value) { m_params[index] = value; }

void AiData::setFrameCount(float count) { m_frameCount = count; }

bool AiData::isFrameCountEnd() const { return m_frameCount <= 0.0f; }

float AiData::getRadius() const { return getRadius(m_handle); }

float AiData::getRadius(gf::GF_OBJ_HANDLE* handle) const {
    if (m_handle == INVALID_HANDLE) {
        return 0.0f;
    }
    gf::GfObjAcc acc(handle);
    float radius = 0.0f;
    if (acc.m_obj != nullptr) {
        switch (acc.getType()) {
        case 3:
            radius = 0.5f;
            break;
        case 5: {
            gf::DataParamAcc param(handle);
            const gf::SDataEnemy* enemy = param.getSDataEnemy();
            if (enemy != nullptr && gf::GfBdatRsc::sys() != nullptr) {
                radius = gf::GfBdatRsc::sys()->getRscEnEnRadius(enemy->m_rscId);
                gf::GFOBJ_INFO* info = gf::GfObjManager::getObjInfo(handle);
                if (info != nullptr) {
                    gf::GfObjSetup* setup = info->m_setup;
                    // scaled by an enemy setup's initial scale
                    if (setup != nullptr && setup->m_type == info->m_obj->m_type && info->m_obj->m_type == 5 &&
                        setup->getRTTI()->isKindOf(&gf::GfObjSetupEnemy::m_rtti)) {
                        radius = radius * setup->m_initialScale.x;
                    }
                }
            }
            break;
        }
        }
    }
    return radius;
}

float AiData::getRadiusTarget() const { return getRadius(getHandleTarget()); }

mm::Vec3 AiData::getPosition() const { return getPosition(m_handle); }

mm::Vec3 AiData::getPosition(gf::GF_OBJ_HANDLE* handle) const {
    if (m_handle != INVALID_HANDLE) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            return acc.getWorldTransform().position;
        }
    }
    return mm::Vec3::zero;
}

mm::Vec3 AiData::getPositionTarget() const { return getPosition(getHandleTarget()); }

}  // namespace ai
namespace mm {
namespace mtl {

bool RTTI::isKindOf(const RTTI* rtti) const {
    if (this == rtti) {
        return true;
    }
    for (int i = 0; i < 2; i++) {
        if (m_bases[i] != nullptr && m_bases[i]->isKindOf(rtti)) {
            return true;
        }
    }
    return false;
}

}  // namespace mtl
}  // namespace mm
