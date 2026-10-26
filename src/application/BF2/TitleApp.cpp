#include "classes/ml/WinProc.h"
#include "classes/ml/WinView.h"
#include "classes/ml/ProcDesktop.h"
#include "classes/apps/LauncherApp.h"
#include "ml/WorkUtil.h"
#include "classes/tl/TitleApp.h"
#include "mm/Col4.h"
#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "classes/tl/TitleApplet.h"
#include "gf/GfSetupParam.h"
#include "classes/gf/GfManager.h"
#include "classes/tl/TitleMain.h"

namespace tl {

const char* TitleApp::m_szTitle = "Title";
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100C232DA)
bool TitleApp::m_dlcCameraParam;

bool TitleApp::wkStandbyLogout() {
    if (!LauncherApp::wkStandbyLogout()) {
        return false;
    }
    ml::WinView::setInitialBackCol(mm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
    return true;
}

TitleApp::~TitleApp() {}

}  // namespace tl

// TitleApplet: its own file in the original (application/BF2/TitleApplet.cpp, see the 1.0.0 splits); kept here
// until the split puts 0x710014E4C8..0x710014E74C in its own unit
namespace tl {

TitleApplet::TitleApplet() {}

TitleApplet::~TitleApplet() {}

void TitleApplet::initialize(const fw::Framework& framework) {
    gf::GfSetupParam param;
    param.m_scn = m_env.m_scn;
    param.m_view = m_env.m_view;
    param.pad_10 = m_env.pad_0;
    param.m_execState = static_cast<gf::EXEC_STATE>(2);  // EXEC_STATE has no known enumerator names
    param.m_view->m_backCol = mm::Col4::black;
    param.m_dlcCameraParam = TitleApp::m_dlcCameraParam;
    gf::GfManager::build(param);
    TitleMain::create();
}

void TitleApplet::finalize(const fw::Framework& framework) {
    TitleMain::destroy();
    gf::GfManager::destroy();
}

void TitleApplet::update(const fw::UpdateInfo& info) {
    gf::GfManager::update(info);
    TitleMain::update(info);
}

void TitleApplet::fn_710014E704(const fw::UpdateInfo& info) {
    gf::GfManager::fn_710032A958(info);
}

void TitleApplet::postUpdate(const fw::UpdateInfo& info) {
    gf::GfManager::postUpdate(info);
}

}  // namespace tl
