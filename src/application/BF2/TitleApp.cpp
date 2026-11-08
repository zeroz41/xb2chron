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

// the loading spinner on a 1280x720 memory layer: false makes it (or draws its next frame), true drops it
void TitleApp::now_loading(bool release) {
    if (!release) {
        if (m_loadLayer != nullptr) {
            unsigned char* trail = static_cast<unsigned char*>(m_loadBuffer);
            for (int i = 0; i < 0x1000; i++) {
                int value = trail[i] - 16;
                trail[i] = value < 0 ? 0 : value;
            }
            float time = (static_cast<unsigned int>(ml::WorkCpu::getFrameCount()) & 0xffff) * 0.05f;
            int count = (static_cast<int>(time / 3.1415927f) & 3) + 5;
            if (count == 8) {
                count = 6;
            }
            for (int i = 0; i < count; i++) {
                float angle = i * 6.2831855f / count + time * 0.7f;
                float radius = sinf(time) * 31.0f;
                int x = static_cast<int>(cosf(angle) * radius);
                int y = static_cast<int>(radius * sinf(angle));
                trail[x + y * 64 + 0x820] = 0xff;
            }
            layer::LayerAccMemObj memObj(m_loadLayer);
            const unsigned char* src = static_cast<unsigned char*>(m_loadBuffer);
            unsigned char* dst = static_cast<unsigned char*>(memObj.getMemBufer());
            unsigned int width = memObj.getMemWidth();
            unsigned int height = memObj.getMemHeight();
            memset(dst, 0, width * 3 * height);
            dst += (width * 624 + 1184) * 3;
            for (int y = 0; y < 64; y++) {
                unsigned char* row = dst;
                for (int x = 0; x < 64; x++) {
                    unsigned int blue = *src * 4;
                    row[0] = *src;
                    row[1] = *src;
                    row[2] = blue > 0xff ? 0xff : blue;
                    row += 3;
                    src++;
                }
                dst += width * 3;
            }
            memObj.updateMemBufer();
        } else if (mm::mtl::PtrSingleton<ml::Scn>::get() != nullptr &&
               mm::mtl::PtrSingleton<layer::LayerManager>::get() != nullptr) {
            layer::LayerAccManager manager;
            m_loadLayer = manager.createMemObj(1280, 720, static_cast<layer::LayerMemType>(1));
            layer::LayerAccMemObj memObj(m_loadLayer);
            grlib::CGLibTextureBuffer* texture = memObj.getTexture();
            ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
            ml::ScnRenderDrMdlTexture modelTexture = {texture, 0, true};
            acc.setModelTexture(modelTexture);
            m_loadBuffer = fw::FrameworkMemory::getAllocator(5)->allocate(0x1000, 4);
            memset(m_loadBuffer, 0, 0x1000);
        }
    } else {
        ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
        acc.resetModelTexture(0);
        if (m_loadLayer != nullptr) {
            m_loadLayer->release();
        }
        m_loadLayer = nullptr;
        fw::FrameworkMemory::getAllocator(5)->deallocate(m_loadBuffer);
        m_loadBuffer = nullptr;
    }
}

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
