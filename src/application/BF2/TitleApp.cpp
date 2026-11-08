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
#include "classes/apps/FrameworkLauncher.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/ml/Scn.h"
#include "classes/mm/mtl/IAllocator.h"
#include "layer/LayerBase.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/layer/LayerManager.h"
#include "classes/ml/WorkCpu.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccMemObj.h"
#include <math.h>

namespace tl {

const char* TitleApp::m_szTitle = "Title";

namespace {
// wkStandbyLogin sets the views' initial colour to black once (lbl_7100C232D8; the name is not the original's)
bool s_backColSet;
// wkStandbyLogin hands it to the framework's config (FrameworkConfig::m_flag); TitleApp::execute clears it,
// TitleAppIra::execute sets it (lbl_7100C232D9; the name is not the original's)
bool s_frameworkFlag;
}  // namespace

// 2.0.0's symbols name it
bool TitleApplet::s_bGameTypeIra;

namespace {
// drops what now_loading made: the scene's model texture 0, the memory layer and its buffer (the name is not the
// original's)
inline void releaseLoading(TitleApp* app) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
    acc.resetModelTexture(0);
    if (app->m_loadLayer != nullptr) {
        app->m_loadLayer->release();
    }
    app->m_loadLayer = nullptr;
    fw::FrameworkMemory::getAllocator(5)->deallocate(app->m_loadBuffer);
    app->m_loadBuffer = nullptr;
}
}  // namespace

bool TitleApp::wkStandbyLogin() {
    if (!s_backColSet) {
        ml::WinView::setInitialBackCol(mm::Col4::black);
        s_backColSet = true;
    }
    now_loading(false);
    apps::SceneBuildInfo info;
    info.m_flags = 0x78;
    fw::FrameworkConfig config;
    config.m_lang = m_language;
    config.m_flag = s_frameworkFlag;
    if (!apps::FrameworkLauncher::create<TitleApplet>(this, info, config, nullptr, nullptr)) {
        return false;
    }
    releaseLoading(this);
    ml::WinView::setInitialBackCol(mm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
    s_backColSet = false;
    return ml::WinProc::wkStandbyLogin();
}

bool TitleApp::wkStandbyLogout() {
    if (!LauncherApp::wkStandbyLogout()) {
        return false;
    }
    ml::WinView::setInitialBackCol(mm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
    return true;
}

namespace {
// TitleApp::execute's body: the title application under the desktop, on the desktop's view (the name is not the
// original's)
inline void createTitleApp(const char* name) {
    TitleApp* app = ml::WorkUtil::createWork<TitleApp>(name, mm::mtl::PtrSingleton<ml::ProcDesktop>::get(), false);
    ml::WinView* view = mm::mtl::PtrSingleton<ml::ProcDesktop>::get()->pssGetApplicationView() != nullptr
                            ? mm::mtl::PtrSingleton<ml::ProcDesktop>::get()->pssGetApplicationView()
                            : ml::ProcDesktop::getView();
    app->m_viewWid = view->m_wid;
    s_frameworkFlag = false;
    TitleApplet::s_bGameTypeIra = false;
}
}  // namespace

void TitleApp::execute() {
    if (mm::mtl::PtrSingleton<TitleApp>::get() == nullptr) {
        createTitleApp(m_szTitle);
    }
}

void TitleAppIra::execute() {
    TitleApp::execute();
    s_frameworkFlag = true;
    TitleApplet::s_bGameTypeIra = true;
}

const char* TitleAppEN::m_szTitle = "Title_english";
const char* TitleAppCN::m_szTitle = "Title_cn_simple";
const char* TitleAppTW::m_szTitle = "Title_cn_original";
// lbl_7100B3FE88 (the name is not the original's)
const char* g_szTitleKorean = "Title_korean";

void TitleAppEN::execute() {
    if (mm::mtl::PtrSingleton<TitleApp>::get() == nullptr) {
        createTitleApp(m_szTitle);
        mm::mtl::PtrSingleton<TitleApp>::get()->m_language = 12;
    }
}

void TitleAppCN::execute() {
    if (mm::mtl::PtrSingleton<TitleApp>::get() == nullptr) {
        createTitleApp(m_szTitle);
        mm::mtl::PtrSingleton<TitleApp>::get()->m_language = 6;
    }
}

void TitleAppTW::execute() {
    if (mm::mtl::PtrSingleton<TitleApp>::get() == nullptr) {
        createTitleApp(m_szTitle);
        mm::mtl::PtrSingleton<TitleApp>::get()->m_language = 11;
    }
}

TitleApp::~TitleApp() {}

}  // namespace tl

void fn_710014E2B0() {
    if (mm::mtl::PtrSingleton<tl::TitleApp>::get() == nullptr) {
        tl::createTitleApp(tl::g_szTitleKorean);
        mm::mtl::PtrSingleton<tl::TitleApp>::get()->m_language = 7;
    }
}
